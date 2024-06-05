#include "SHSshsf.h"


// --------------------------------------------------------------------------
// TYPES
// --------------------------------------------------------------------------
enum shs::SHSF::Type : uint8_t
{
    unknown,
    structs_collector,
    data_sequences,
    text,
};

struct shs::SHSF::HEADER
{
    static constexpr uint8_t size = 7;
    static constexpr uint8_t header_shsf[4]{ 's', 'h', 's', 'f' };
    uint8_t version = CURRENT_SHSF_VERSION;
    shs::SHSF::Type type{};
    uint8_t CRCdegree{};
};

struct shs::SHSF::INDEX
{
    static constexpr uint8_t posINFObeg = 0x0B;
    static constexpr uint8_t posDATAbeg = 0x0D;
};

// --------------------------------------------------------------------------
// CONSTRUCTORS 
// --------------------------------------------------------------------------
shs::SHSF::SHSF(shs::fs::File_basic_t* file) : ::shs::File(file)
{
    readHeader();
}

shs::SHSF& shs::SHSF::operator=(shs::fs::File_basic_t* file)
{
    if (fb) { fb->close(); delete fb; }
    fb = file;
    readHeader();
    return *this;
}

// --------------------------------------------------------------------------
// HEADER
// --------------------------------------------------------------------------
shs::SHSF& shs::SHSF::writeHeader()
{
    seek(0);
    write(header_data.header_shsf, 4);
    write(&header_data, 3);

    m_crc.clear();
    m_crc.crcBuf(header_data.header_shsf, 4);
    m_crc.crcBuf(&header_data.version, 3);
    write((uint8_t*) &m_crc.crc, sizeof(m_crc.crc));

    return *this;
}

shs::SHSF& shs::SHSF::readHeader()
{
    seek(4);
    read((uint8_t*) &header_data, 3);

    return *this;
}

bool shs::SHSF::checkHeader()
{
    uint32_t crc_from_file{};

    seek(header_data.size);
    read((uint8_t*) &crc_from_file, 4);
    m_crc.clear();
    m_crc.crcBuf(header_data.header_shsf, 4);
    m_crc.crcBuf(&header_data.version, 3);

    return m_crc.crc == crc_from_file;
}


// --------------------------------------------------------------------------
// INFO
// --------------------------------------------------------------------------

uint16_t shs::SHSF::writeInfoSize()
{
    uint16_t info_size = 10;
    seek(incrPos(shs::SHSF::INDEX::posINFObeg, 2 + 8));
    uint16_t comment_size{};
    get((uint8_t*) &comment_size, 2);
    info_size += comment_size;

    /*
    if (header_data.type == shs::fs::structs_collector)
    {
        seek(value + 1, shs::fs::Seek_Cur);
        uint8_t number_of_members = read();
        while (number_of_members--)
        {
            get((uint8_t*) &value, 1);
            info_size += value;
            seekData(value + position());
        }
    }
    */

    seek(shs::SHSF::INDEX::posINFObeg);
    add((uint8_t*) &info_size, 2);

    return info_size;
}

uint16_t shs::SHSF::readInfoSize()
{
    uint16_t info_size{};

    seek(shs::SHSF::INDEX::posINFObeg);
    get((uint8_t*) &info_size, 2);

    return info_size;
}

shs::SHSF& shs::SHSF::writeInfoComment(const char* buf, uint16_t size)
{
    seekData(shs::SHSF::INDEX::posINFObeg + 2 + 8);
    add((uint8_t*) &size, 2);
    add((uint8_t*) buf, size);

    return *this;
}

uint16_t shs::SHSF::readInfoCommentSize()
{
    uint16_t comment_size{};
    seekData(shs::SHSF::INDEX::posINFObeg + 2 + 8);
    get((uint8_t*) &comment_size, 2);

    return comment_size;
}

uint16_t shs::SHSF::readInfoComment(char* buf, const uint16_t comment_size)
{
    seekData(0x0F + 2 + 8 + 2);
    return get((uint8_t*) buf, comment_size);
}

uint16_t shs::SHSF::readInfoComment(char*& buf)
{
    uint16_t comment_size = readInfoCommentSize();
    if (buf) delete [] buf;
    buf = new char[comment_size];
    return readInfoComment(buf, comment_size);
}

// shs::SHSF& shs::SHSF::addInfoMember(shs::fs::SHSF_INFO_member& stc)
// {
//     uint8_t name_size = strlen(stc.m_name);
//     uint8_t note_size = strlen(stc.m_note);
//     uint8_t com_size = 2 + name_size + note_size;

//     add((uint8_t*) &com_size, 1);
//     add((uint8_t*) &stc.member_size, 1);
//     add((uint8_t*) &stc.member_type, 1);

//     if (!stc.m_name) add('\0');
//     else write((uint8_t*) stc.m_name, name_size);

//     if (!stc.m_note) write('\0');
//     else write((uint8_t*) stc.m_note, note_size);

//     return *this;
// }

// bool shs::SHSF::getInfoMember(shs::fs::SHSF_INFO_member& stc)
// {
//     size_t pos{};
//     uint8_t com_size = read();
//     uint8_t str_size{};

//     stc.member_size = read();
//     stc.member_type = static_cast<shs::fs::SHSF_INFO_member_type>(read());

//     pos = position();
//     while (read() != '\0') str_size++;
//     str_size++;
//     seek(pos);
//     if (stc.m_name)  delete [] stc.m_name;
//     stc.m_name = new char(str_size);
//     read((uint8_t*) stc.m_name, str_size);

//     pos = position();
//     str_size = 0;
//     while (read() != '\0') str_size++;
//     str_size++;
//     read((uint8_t*) stc.m_note, str_size);

// // !!!!!!!!!!!!!!!!!!!!!
//     return true;
// }

// ----------------------------------------
//
// ----------------------------------------

uint16_t shs::SHSF::posDataBeg(bool go)
{
    uint16_t value{};
    size_t pos = position();

    seek(0x0B);
    read((uint8_t*) &value, 2);

    seek(go ? value : pos);

    return value;
}

size_t shs::SHSF::incrPos(const size_t pos, const size_t incr)
{
    int32_t free = ((((int32_t) 1 << header_data.CRCdegree) - (pos & \
        (((int32_t) 1 << header_data.CRCdegree) - 1))) - sizeof(m_crc.crc) - 2);
    if (incr > free)
    {
        return pos + free + 6 + \
            ((incr - free) / (((uint32_t) 1 << header_data.CRCdegree) - 6)) * 6 + (incr - free);
    }
    return pos + incr;
}

size_t shs::SHSF::add(const uint8_t* buf, const size_t size)
{
    if (!header_data.CRCdegree)
        return write(buf, size);

    if (position() == SHSF::size()) seek(position() - 6);

    int32_t free{};
    size_t written_size{};
    for (size_t i = 0; i < size;)
    {
        free = getFree();
        if (free < 0) seek(posNextBlock());

        if (free <= size - i)
        {
            written_size += write(&buf[i], free);
            i += free;
            writeBlockCRC();
            continue;
        }
        written_size += write(&buf[i], size - i);
        writeBlockCRC();
        break;
    }

    return written_size;
}

uint32_t shs::SHSF::writeBlockCRC()
{
    seek(posBlockCRC());
    write((uint8_t*) &block_constant, 1);
    calculateBlockCRC();
    write((uint8_t*) &m_crc.crc, sizeof(m_crc.crc));
    write((uint8_t*) &block_constant, 1);

    return m_crc.crc;
}

size_t shs::SHSF::get(uint8_t* buf, const size_t size)
{
    if (!header_data.CRCdegree) return read(buf, size);

    size_t free{};
    size_t read_size{};

    for (size_t i = 0; i < size;)
    {
        free = getFree();
        if (free < 0) seek(posNextBlock());
        if (free <= size - i)
        {
            read_size += read(&buf[i], free);
            i += free;
            seek(sizeof(m_crc.crc) + 2, shs::fs::Seek_Cur);
            continue;
        }
        read_size += read(&buf[i], size - i);
        break;
    }

    return read_size;
}

int8_t shs::SHSF::checkBlock()
{
    uint32_t crc_data = calculateBlockCRC();
    uint32_t crc_read{};

    size_t pos = position();
    seek(posBlockCRC());

    if (read() != block_constant) return -1;
    read((uint8_t*) &crc_read, sizeof(crc_read));
    if (read() != block_constant) return -2;
    if (crc_read != crc_data) return -3;

    seek(pos);

    return 0;
}

int8_t shs::SHSF::checkFile()
{
    if (!checkHeader) return -1;
    posDataBeg(true);

    for (uint8_t i = 0; i < blocksCount(); i++)
    {
        if (!checkBlock()) return -2;
        seek(posNextBlock());
    }

    return 0;
}


uint32_t shs::SHSF::calculateCRC(const size_t from, const size_t size)
{
    seek(from);
    m_crc.clear();

    for (size_t i = 0; i < size; i++)
        m_crc.add(read());
    return m_crc.crc;
}


// ----------------------------------------
// SHSFmanager
// Constructor
// ----------------------------------------

shs::SHSFmanager::SHSFmanager(shs::SHSF* ptr) : file(ptr), newFile(!ptr->hasData()) {}

// ----------------------------------------
// HEADER
// ----------------------------------------

shs::SHSFmanager& shs::SHSFmanager::h_setHeader(const shs::fs::SHSF_HEADER& header_data)
{
    if (header_data.CRCdegree < 5) { flags |= Errors::h_invalid_CRCdegree; return *this; }
    if (!newFile && header_data.CRCdegree != file->header_data.CRCdegree)
    {
        flags |= Errors::h_not_match_CRCdegree;
        return *this;
    }
    if (!newFile && header_data.version != file->header_data.version)
    {
        flags |= Errors::h_not_match_version;
        return *this;
    }

    file->header_data = header_data;
    file->writeHeader();
    return *this;
}

shs::SHSFmanager& h_setVersion(const uint8_t version = CURRENT_SHSF_VERSION);
shs::SHSFmanager& h_setType(const shs::fs::SHSF_type type);
shs::SHSFmanager& h_setCRC(const uint8_t degree);

shs::SHSFmanager& h_getHeader(shs::fs::SHSF_HEADER& header_data);
const uint8_t            h_getVersion();
const shs::fs::SHSF_type h_getType();
const uint8_t            h_getCRC();


enum shs::SHSFmanager::Errors : uint32_t
{
    h_invalid_CRCdegree = 0b1,
    h_not_match_CRCdegree = 0b10,
    h_not_match_version = 0b100,

};


/*
shs::fs::SHSF_INFO_member::~SHSF_INFO_member()
{
    clear();
}

shs::fs::SHSF_INFO_member& shs::fs::SHSF_INFO_member::clear()
{
    if (m_name) delete [] m_name;
    if (m_note) delete [] m_note;

    return *this;
}

shs::fs::SHSF_INFO_member& shs::fs::SHSF_INFO_member::setName(const char* name, uint8_t size)
{
    if (m_name) delete [] m_name;
    m_name = new char(size);
    strcpy(m_name, name);

    return *this;
}

shs::fs::SHSF_INFO_member& shs::fs::SHSF_INFO_member::setNote(const char* note, uint8_t size)
{
    if (m_note) delete [] m_note;
    m_note = new char(size);
    strcpy(m_note, note);

    return *this;
}
*/
