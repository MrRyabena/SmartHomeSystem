#pragma once
/*
  Smart Home System File (.shsf)
*/

/*
  Last update: v1.2.0
  Versions:
    v1.2.0 — created.

  File format versions:
    001 — first version.
*/

/*
  Overall File Structure:
  The file consists of three main blocks:
  Header (HEADER), Index (INDEX) and Information (INFO).
  Next are the data-blocks (BLOCK). Their size: 2^CRCdegree.

  1. Header (HEADER)
    - 0x00 - 4B (prefix): 'shsf' - Number identifying the file format.
    - 0x04 - 1B (version): '001' - File format version.
    - 0x05 - 1B (type): File type, defined as enum shs::SHSF::type.
    - 0x06 - 1B (CRCdegree): Power of 2 that determines the block size for CRC.
    - 0x07 - 4B (CRC): Header CRC checksum.

  2. Index (INDEX)
    - 0x0B - 2B - INFObeg
    - 0x0D - 2B - DATAbeg

  3. Information (INFO)
    -      - 2B (size): Size of the information block.
    -      - 4B (creator's ID): ID of file creator.
    -      - 4B (API): API for decoding file.
    -      - 8B (reserved): Reserved.
    -      - 2B (comment size): Size of the comment.
    -      - ... (comment): Comment.
      - If type == structs_collector:
        - 1B (struct size): Size of the structure.
        - 1B (number of members): Number of members in the structure.
          - For each member:
            - 1B (member description size): Size of the member description.
            - 1B (member size): Size of the member.
            - 1B (member type): Type of the member.
            - nB (member name): Name of the member.
            - xB (member note): Note about the member.

  4. Data-block (BLOCK)
    - 0x00 - ... (data): Data.
    - i* (block_constant): Block constant, 0xBA.
    - i+01 - 4B (CRC): Block CRC checksum.
    - i+05 - 1B (block_constant): Block constant, 0xBA.

  * i = 2^CRCdegree - sizeof(crc) - 2

*/

#include "SHSFile.h"
#include "SHSCRC.h"

#if __has_include(<Arduino.h>)
#include <Arduino.h>
#include <FS.h>
#else 

#endif


#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define CURRENT_SHSF_VERSION 1

namespace shs
{
  class SHSF;
  class SHSFmanager;
}

class shs::SHSF : public shs::File
{
public:
  int32_t file_status{};
  static constexpr uint8_t block_constant = 0xBA;

  enum Type : uint8_t;


  SHSF(shs::fs::File_basic_t* file = nullptr);
  shs::SHSF& operator=(shs::fs::File_basic_t* file) override;
  ~SHSF() = default;


  size_t add(const uint8_t* buf, const size_t size);
  size_t get(uint8_t* buf, const size_t size);
  bool seekData(const size_t pos) \
  { return seek((pos / (((uint32_t) 1 << header_data.CRCdegree) - 6)) * 6 + pos); }
  void readRAW(uint8_t* buf, size_t size) { read(buf, size); }

  size_t incrPos(const size_t pos, const size_t incr);

    // HEADER
private:
  shs::SHSF& writeHeader();
  shs::SHSF& readHeader();
public:
  struct HEADER;
  bool checkHeader();


  // INDEX
  struct INDEX;
  uint16_t setIndex_begINFO() { seek(shs::SHSF::INDEX::posINFObeg); write(0x0F); return 0x0F; };
  void setIndex_begDATA(uint16_t ind) { seek(0x0D); write((uint8_t*) &ind, 2); }
  uint16_t setIndex_begData() \
  { seek(shs::SHSF::INDEX::posINFObeg); uint16_t size{}; read((uint8_t*) &size, 2); size = incrSize(size, shs::SHSF::INDEX::posINFObeg); \
    seek(shs::SHSF::INDEX::posDATAbeg); write((uint8_t*) &size, 2); return size; }


  // INFO
private:
  uint16_t writeInfoSize();
  shs::SHSF& writeInfoComment(const char* buf, uint16_t size);

  // uint32_t -> shs::ID in future
  shs::SHSF& writeCreator(uint32_t id) \
  { seek(0x11); write((uint8_t*) &id, 4); return *this; };

  // uint32_t -> shs::API in future
  shs::SHSF& writeAPI(uint32_t api) \
  { seek(0x15); write((uint8_t*) &api, 4); return *this; };

public:
  uint16_t readInfoSize();

  uint16_t readInfoCommentSize();
  uint16_t readInfoComment(char* buf, const uint16_t comment_size);
  uint16_t readInfoComment(char*& buf);
  // shs::SHSF& addInfoMember(shs::fs::SHSF_INFO_member& stc);
  // bool getInfoMember(shs::fs::SHSF_INFO_member& stc);

  // end INFO





  // UTILS
  // --------------------------------------------------------------------------
  [[nodiscard]]
  bool hasData() \
  { return !(size() < shs::SHSF::HEADER::size); }

  uint16_t posDataBeg(bool go = false);

  [[nodiscard]]
  int32_t getFree() \
  // ( int( (1 << n) - (p & ((1 << n) - 1)) ) - 4 - 2)
  { return ((((int32_t) 1 << header_data.CRCdegree) - (position() & \
    (((int32_t) 1 << header_data.CRCdegree) - 1))) - sizeof(m_crc.crc) - 2); }

  [[nodiscard]]
  size_t posBlockBeg() const \
  { return ((position() >> header_data.CRCdegree) << header_data.CRCdegree); };

  [[nodiscard]]
  size_t posBlockCRC() \
  { return ((posBlockBeg() + ((size_t) 1 << header_data.CRCdegree) - 6) \
   < size() ? (posBlockBeg() + (1 << header_data.CRCdegree) - 6) : size()); }

  [[nodiscard]]
  size_t posPrevBlock() const \
  { return (posBlockBeg() - ((size_t) 1 << header_data.CRCdegree)); }

  [[nodiscard]]
  size_t posNextBlock() const \
  { return (posBlockBeg() + ((size_t) 1 << header_data.CRCdegree)); }

  [[nodiscard]]
  size_t blockNumber() const \
  { return (position() >> header_data.CRCdegree); }

  [[nodiscard]]
  uint16_t blocksCount() \
  { return (size() >> header_data.CRCdegree); }

  [[nodiscard]] int8_t checkBlock();
  [[nodiscard]] int8_t checkFile();


  // CRC
  uint32_t calculateCRC(const size_t from, const size_t size);
  uint32_t writeBlockCRC();
  uint32_t calculateBlockCRC() \
  { return calculateCRC(posBlockBeg(), posBlockCRC() - posBlockBeg()); }

  // --------------------------------------------------------------------------

protected:
  friend class shs::SHSFmanager;

  shs::CRC32 m_crc;
  shs::SHSF::HEADER header_data;

  using File::read;
  using File::write;
  using File::available;
  using File::insert;
  using File::shiftLeft;
  using File::shiftRight;
  using File::seek;
};

class shs::SHSFmanager
{
public:
  shs::SHSF* file;
  uint32_t flags{};
  bool newFile{};

  enum Errors : uint32_t;

  explicit SHSFmanager(shs::SHSF* ptr);

  // header
  shs::SHSFmanager& h_setHeader(const shs::SHSF::HEADER& header_data);
  shs::SHSFmanager& h_setVersion(const uint8_t version = CURRENT_SHSF_VERSION);
  shs::SHSFmanager& h_setType(const shs::SHSF::Type type);
  shs::SHSFmanager& h_setCRCdegree(const uint8_t degree);

  [[nodiscard]] shs::SHSF::HEADER h_getHeader() { return file->header_data; }
  [[nodiscard]] uint8_t           h_getVersion() { return file->header_data.version; }
  [[nodiscard]] shs::SHSF::Type   h_getType() { return file->header_data.type; }
  [[nodiscard]] uint8_t           h_getCRCdegree() { return file->header_data.CRCdegree; }

  shs::SHSFmanager& h_getHeader(shs::fs::SHSF_HEADER& header_data);
  const uint8_t            h_getVersion();
  const shs::fs::SHSF_type h_getType();
  const uint8_t            h_getCRC();



};

/*

  enum shs::fs::shsf::INFO_MemberType : uint8_t
{
  t_int8 = 1,
  t_uint8,
  t_int16,
  t_uint16,
  t_int32,
  t_uint32,
  t_int64,
  t_uint64,

  t_float,
  t_double,
  t_char,
};

struct shs::fs::shsf::INFO_Member
{
  ~INFO_Member();

  shs::fs::shsf::INFO_Member& setName(const char* name, uint8_t size);
  shs::fs::shsf::INFO_Member& setNote(const char* note, uint8_t size);
  shs::fs::shsf::INFO_Member& setType(shs::fs::shsf::INFO_MemberType type) \
  { member_type = type; return *this; }

  const char* getName() const { return m_name; }
  const char* getNote() const { return m_note; }

  shs::fs::shsf::INFO_Member& clear();

  uint8_t member_size{};
  shs::fs::shsf::INFO_MemberType member_type{};
private:
  char* m_name;
  char* m_note;
  friend class shs::SHSF;
};

*/
