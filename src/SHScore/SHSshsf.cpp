#include "SHSshsf.h"

//

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

// ----------------------------------------
// CONSTRUCTORS 
// ----------------------------------------
shs::SHSF::SHSF(shs::fs::File_basic_t* file) : ::shs::File(file) {}

shs::SHSF& shs::SHSF::operator=(shs::fs::File_basic_t* file)
{
    if (fb) { fb->close(); delete fb; }
    fb = file;
    return *this;
}


// ----------------------------------------
// Bools
// ----------------------------------------

bool shs::SHSF::hasData()
{
    if (size() < shs::fs::SHSF_HEADER::size) return false;

    return true;
}

// ----------------------------------------
// HEADER
// ----------------------------------------
shs::SHSF& shs::SHSF::writeHeader()
{
    seek(0);
    write((uint8_t*) &header_data, sizeof(header_data));
    m_crc.clear();
    m_crc.crcBuf((uint8_t*) &header_data, sizeof(header_data));
    write((uint8_t*) &m_crc.crc, sizeof(m_crc.crc));

    return *this;
}

shs::SHSF& shs::SHSF::readHeader()
{
    seek(0);
    read((uint8_t*) &header_data, sizeof(header_data));

    return *this;
}

bool shs::SHSF::checkHeader()
{
    uint32_t crc_from_file{};

    seek(sizeof(header_data));
    read((uint8_t*) &crc_from_file, 4);
    m_crc.clear();
    m_crc.crcBuf((uint8_t*) &header_data, sizeof(header_data));
    return m_crc.crc == crc_from_file;
}

// ----------------------------------------
// INFO
// ----------------------------------------

uint16_t shs::SHSF::writeInfoSize()
{
    uint16_t info_size{};
    seek(sizeof(header_data) + 4 + 2 + 8);
    info_size = 10;
    uint16_t value{};
    read((uint8_t*) &value, 2);
    info_size += value;

    if (header_data.type == shs::fs::structs_collector)
    {
        seek(value + 1, shs::fs::Seek_Cur);
        uint8_t number_of_members = read();
        while (number_of_members-- > 0)
        {
            value = read();
            info_size += value;
            seek(value, shs::fs::Seek_Cur);
        }
    }
    seek(sizeof(header_data) + 4);
    write((uint8_t*) &info_size, 2);

    return info_size;
}

uint16_t shs::SHSF::readInfoSize()
{
    seek(sizeof(header_data) + 4);
    uint16_t info_size{};
    read((uint8_t*) &info_size, 2);

    return info_size;
}

shs::SHSF& shs::SHSF::writeInfoComment(const char* buf, uint16_t size)
{
    seek(sizeof(header_data) + 4 + 2 + 8);
    write((uint8_t*) &size, 2);
    write((uint8_t*) buf, size);

    return *this;
}

uint16_t shs::SHSF::readInfoCommentSize()
{
    uint16_t comment_size{};
    seek(sizeof(header_data) + 4 + 2 + 8);
    read((uint8_t*) &comment_size, 2);

    return comment_size;
}

uint16_t shs::SHSF::readInfoComment(char* buf, const uint16_t comment_size)
{
    seek(sizeof(header_data) + 4 + 2 + 8 + 2);
    return read((uint8_t*) buf, comment_size);
}

uint16_t shs::SHSF::readInfoComment(char*& buf)
{
    uint16_t comment_size = readInfoCommentSize();
    if (buf) delete [] buf;
    buf = new char[comment_size];
    return readInfoComment(buf, comment_size);
}

shs::SHSF& shs::SHSF::addInfoMember(shs::fs::SHSF_INFO_member& stc)
{
    uint8_t name_size = strlen(stc.m_name);
    uint8_t note_size = strlen(stc.m_note);
    uint8_t com_size = 2 + name_size + note_size;

    write(com_size);
    write(stc.member_size);
    write(stc.member_type);

    if (!stc.m_name) write('\0');
    else write((uint8_t*) stc.m_name, name_size);

    if (!stc.m_note) write('\0');
    else write((uint8_t*) stc.m_note, note_size);

    return *this;
}

bool shs::SHSF::getInfoMember(shs::fs::SHSF_INFO_member& stc)
{
    size_t pos{};
    uint8_t com_size = read();
    uint8_t str_size{};

    stc.member_size = read();
    stc.member_type = static_cast<shs::fs::SHSF_INFO_member_type>(read());

    pos = position();
    while (read() != '\0') str_size++;
    str_size++;
    seek(pos);
    if (stc.m_name)  delete [] stc.m_name;
    stc.m_name = new char(str_size);
    read((uint8_t*) stc.m_name, str_size);

    pos = position();
    str_size = 0;
    while (read() != '\0') str_size++;
    str_size++;
    read((uint8_t*) stc.m_note, str_size);

// !!!!!!!!!!!!!!!!!!!!!
    return true;
}

// ----------------------------------------
//
// ----------------------------------------

uint16_t shs::SHSF::seekToBeginning()
{
    uint16_t value{};
    seek(sizeof(header_data) + 4);
    read((uint8_t*) &value, 2);
    value += sizeof(header_data) + 4 + 2;
    seek(value);
    return value;
}

size_t shs::SHSF::add(const uint8_t* buf, const size_t size)
{
    if (!header_data.CRCdegree)
        return write(buf, size);

    int32_t free{};
    size_t written_size{};
    for (size_t i = 0; i < size;)
    {
        free = getFree();
        if (free <= 0) seek(posNextBlock());

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
    if (!header_data.CRCdegree)
        return read(buf, size);

    size_t free{};
    size_t read_size{};

    for (size_t i = 0; i < size;)
    {
        free = getFree();
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

uint8_t shs::SHSF::checkBlock()
{
    return 0;
    seek(position() - (((uint32_t) 1 << header_data.CRCdegree) - 1) + getFree());

}

// ( int( (1 << n) - (p & ((1 << n) - 1)) ) - 4 - 2)
int32_t shs::SHSF::getFree() { return ((((int32_t) 1 << header_data.CRCdegree) - (position() & (((int32_t) 1 << header_data.CRCdegree) - 1))) - sizeof(m_crc.crc) - 2); }

uint32_t shs::SHSF::calculateCRC(const size_t from, const size_t size)
{
    seek(from);
    m_crc.clear();

    for (size_t i = 0; i < size; i++)
        m_crc.add(read());
    return m_crc.crc;
}

// shs::File::operator bool()
// {
//     return fb != nullptr && fb->operator bool();
// }
#ifdef ARDUINO
shs::SHSF& shs::SHSF::operator=(shs::SHSF& other)
{
    if (this == &other)
        return *this;
    if (fb)
        fb->close();

    fb = other.fb;




    return *this;
}
#else

// shs::SHSF& shs::SHSF::operator=(const shs::FileCreateData& data)
// {
//     if (fstr) fstr.close();
//     fstr.open(data.path, m_createOpenMode(data.mode, data.create));
//     fb = &fstr;
//     return *this;
// }
#endif


// ----------------------------------------
// SHSFmanager
// Constructor
// ----------------------------------------

shs::SHSFmanager::SHSFmanager(shs::SHSF* ptr) : file(ptr), newFile(!ptr->hasData())
{
    file->readHeader();
}

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
