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
  The file consists of two main blocks: Header (HEADER) and Information (INFO).
  Next are the data-blocks (BLOCK). Their size: 2^CRCdegree.

  1. Header (HEADER)
    - 0x00 - 4B (prefix): 'shsf' - Number identifying the file format.
    - 0x04 - 1B (version): '001' - File format version.
    - 0x05 - 1B (type): File type, defined as enum shs::SHSF::type.
    - 0x06 - 1B (CRCdegree): Power of 2 that determines the block size for CRC.
    - 0x07 - 4B (CRC): Header CRC checksum.

  2. Index (INDEX)
    - 0x0B - 2B - INFO_begin
    - 0x0D - 2B - INFO_comment_begin
    - 0xxx - 2B - DATA_begin

  2. Metadata (METADATA)
    - 0x0B - 2B (size): Size of the information block.
    - 0x0D - 8B (reserved): Reserved.
    - 0x15 - 2B (comment size): Size of the comment.
    - 0x17 - ... (comment): Comment.
      - If type == structs_collector:
        - 1B (struct size): Size of the structure.
        - 1B (number of members): Number of members in the structure.
          - For each member:
            - 1B (member description size): Size of the member description.
            - 1B (member size): Size of the member.
            - 1B (member type): Type of the member.
            - nB (member name): Name of the member.
            - xB (member note): Note about the member.

  3. Data-block (BLOCK)
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
  namespace fs
  {
    enum SHSF_type : uint8_t;
    struct SHSF_HEADER;
    enum SHSF_INFO_member_type : uint8_t;
    struct SHSF_INFO_member;
  }
  class SHSF;
  class SHSFmanager;
}

enum shs::fs::SHSF_type : uint8_t
{
  unknown,
  structs_collector,
  data_sequences,
  text,
};

enum shs::fs::SHSF_INFO_member_type : uint8_t
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

struct shs::fs::SHSF_HEADER
{
  static constexpr uint8_t size = 7;
  static constexpr uint8_t header_shsf[4]{ 's', 'h', 's', 'f' };
  uint8_t version = CURRENT_SHSF_VERSION;
  shs::fs::SHSF_type type{};
  uint8_t CRCdegree{};
};

struct shs::fs::SHSF_INFO_member
{
  ~SHSF_INFO_member();

  shs::fs::SHSF_INFO_member& setName(const char* name, uint8_t size);
  shs::fs::SHSF_INFO_member& setNote(const char* note, uint8_t size);
  shs::fs::SHSF_INFO_member& setType(shs::fs::SHSF_INFO_member_type type) { member_type = type; return *this; }

  const char* getName() const { return m_name; }
  const char* getNote() const { return m_note; }

  shs::fs::SHSF_INFO_member& clear();

  uint8_t member_size{};
  shs::fs::SHSF_INFO_member_type member_type{};
private:
  char* m_name;
  char* m_note;
  friend class shs::SHSF;
};



class shs::SHSF : public shs::File
{
public:
  int32_t file_status{};
  static constexpr uint8_t block_constant = 0xBA;
  shs::fs::SHSF_HEADER header_data;

public:
  SHSF(shs::fs::File_basic_t* file = nullptr);
  shs::SHSF& operator=(shs::fs::File_basic_t* file) override;

  ~SHSF() = default;

  // utils
  [[nodiscard]] bool hasData();
  [[nodiscard]] int32_t getFree();
  [[nodiscard]] size_t posBlockBeg() const;
  [[nodiscard]] size_t posBlockCRC();
  [[nodiscard]] size_t posPrevBlock() const;
  [[nodiscard]] size_t posNextBlock() const;

  [[nodiscard]] size_t blockNumber();

  uint8_t checkBlock();
  uint8_t checkFile();

  uint32_t calculateCRC(const size_t from, const size_t size);
  uint32_t updateCRC(const size_t from, const size_t size);
  uint32_t writeBlockCRC();
  uint32_t calculateBlockCRC();


  // header
  shs::SHSF& writeHeader();
  shs::SHSF& readHeader();
  bool checkHeader();

  // info
  uint16_t writeInfoSize();
  uint16_t readInfoSize();
  shs::SHSF& writeInfoComment(const char* buf, uint16_t size);
  uint16_t readInfoCommentSize();
  uint16_t readInfoComment(char* buf, const uint16_t comment_size);
  uint16_t readInfoComment(char*& buf);
  shs::SHSF& addInfoMember(shs::fs::SHSF_INFO_member& stc);
  bool getInfoMember(shs::fs::SHSF_INFO_member& stc);

  uint16_t seekToBeginning();

  size_t add(const uint8_t* buf, const size_t size);
  size_t get(uint8_t* buf, const size_t size);




protected:
  shs::CRC32 m_crc;

  using File::read;
  using File::write;
  using File::available;
  using File::insert;
  using File::shiftLeft;
  using File::shiftRight;
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
  shs::SHSFmanager& h_setHeader(const shs::fs::SHSF_HEADER& header_data);
  shs::SHSFmanager& h_setVersion(const uint8_t version = CURRENT_SHSF_VERSION);
  shs::SHSFmanager& h_setType(const shs::fs::SHSF_type type);
  shs::SHSFmanager& h_setCRC(const uint8_t degree);

  shs::SHSFmanager& h_getHeader(shs::fs::SHSF_HEADER& header_data);
  const uint8_t            h_getVersion();
  const shs::fs::SHSF_type h_getType();
  const uint8_t            h_getCRC();



};
