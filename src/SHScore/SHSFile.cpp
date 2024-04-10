#include "SHSFile.h"

// ----------------------------------------
// Constructor
// ----------------------------------------

shs::File::File(shs::File_base_t* file) : fb(file), bufsize(32) {}

#ifndef ARDUINO
shs::File::File(const char* path, const char* mode, bool create) : bufsize(32)
{
    fstr.open(path, m_createOpenMode(mode, create));
    fb = &fstr;
}

shs::File::File(const shs::FileCreateData& data) : File(data.path, data.mode, data.create) {}
#endif

// ----------------------------------------
// Added methods
// ----------------------------------------

size_t shs::File::insert(const uint8_t* buf, const size_t size, const size_t from, const size_t before)
{
    if (!fb) return 0;
    if (before - from) shiftRight(from, before - from);
    seek(from);
    write(buf, size);
    return this->size();
}

size_t shs::File::shiftRight(const size_t from, const size_t indent)
{
    if (!fb) return 0;
    uint8_t* buf = new uint8_t(bufsize);
    uint8_t fullness{};
    size_t data = size() - from;
    size_t readPoint = size();

    for (size_t i = 0; i < data;)
    {
        fullness = bufsize < data - i ? bufsize : data - i;
        readPoint -= fullness;
        seek(readPoint);
        read(buf, fullness);
        seek(readPoint + indent);
        write(buf, fullness);
        i += fullness;
    }
    return size();
}

size_t shs::File::shiftLeft(const size_t from, const size_t indent)
{
    if (!fb) return 0;
    uint8_t* buf = new uint8_t(bufsize);
    uint8_t fullness{};
    size_t data = size() - from;
    size_t readPoint = from;

    for (size_t i = 0; i < data; i++)
    {
        fullness = bufsize < data - i ? bufsize : data - i;
        seek(readPoint);
        read(buf, fullness);
        seek(readPoint - indent);
        write(buf, fullness);
        readPoint += fullness;
        i += fullness;
    }
    return size();
}

// ----------------------------------------
// Overriden methods
// ----------------------------------------
size_t shs::File::write(const uint8_t* buf, size_t size)
{
    if (!fb)
        return 0;
#ifdef ARDUINO
    return fb->write(buf, size);
#else
    //for (size_t i = 0; i < size; i++) (*fb) << buf[i];
    fb->write(reinterpret_cast<const char*>(buf), size);
    return fb->gcount();
#endif
}

size_t shs::File::read(uint8_t* buf, size_t size)
{
    if (!fb)
        return 0;
#ifdef ARDUINO
    return fb->read(buf, size);
#else
    //for (size_t i = 0; i < size; i++) *(fb) >> buf[i];
    fb->read(reinterpret_cast<char*>(buf), size);
    return fb->gcount();
#endif
}

void shs::File::flush()
{
    if (!fb)
        return;
    fb->flush();
}

bool shs::File::seek(uint32_t pos, shs::file::SeekMode mode)
{
    if (!fb)
        return false;
#ifdef ARDUINO
    return fb->seek(pos, mode);
#else
    // fb->seekp(pos, cpp_mode);
    fb->seekg(pos, m_createSeekMode(mode));
    return true;
#endif
}

size_t shs::File::position() const
{
    if (!fb)
        return 0;
#ifdef ARDUINO
    return fb->position();
#else
    return fb->tellg();
#endif
}

size_t shs::File::size()
{
    if (!fb)
        return 0;
#ifdef ARDUINO
    return fb->size();
#else
    std::streampos current = fb->tellg();
    fb->seekg(0, std::ios::end);
    std::streampos end = fb->tellg();
    fb->seekg(current, std::ios::beg);
    return static_cast<size_t>(end);
#endif
}

void shs::File::close()
{
    if (!fb)
        return;
    fb->close();
    fb = nullptr;
}

shs::settings::shs_string_t shs::File::path() const
{
    if (!fb)
        return "";
#ifdef ARDUINO
    return fb->path();
#else
    return "";
    // std::wstring_convert<std::codecvt_utf16<wchar_t>, wchar_t> converter;
    // return std::string(converter.to_bytes(fs::canonical(fs::path(fb->getloc().name())).c_str()));
#endif
}

shs::settings::shs_string_t shs::File::name() const
{
    if (!fb)
        return "";
#ifdef ARDUINO
    return fb->name();
#else
    return "";
    // std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    // return converter.to_bytes(fs::path(fb->getloc().name()).filename().c_str());
#endif
}

bool shs::File::isDirectory(void)
{
    if (!fb)
        return false;
#ifdef ARDUINO
    return fb->isDirectiry();
#else
    return false;//fs::is_directory(fs::path(fb->getloc().name()));
#endif
}

shs::File& shs::File::openNextFile(const char* mode)
{
    if (!fb)
        return *this;
#ifdef ARDUINO
    fb = fb->openNextFile();
#else
    std::string name = getNextFileName();
    fb->close();
    fb->open(name.c_str(), m_createOpenMode(mode, false));
#endif
    return *this;
}

shs::settings::shs_string_t shs::File::getNextFileName()
{
    if (!fb)
        return "";
#ifdef ARDUINO
    return fb->getNextFileName();
#else
    //static fs::directory_iterator it(fs::path(fb->getloc().name()));
    return "";//it->path().filename().string();
#endif
}

shs::settings::shs_string_t shs::File::getNextFileName(bool* isDir)
{
    if (!fb)
        return "";
#ifdef ARDUINO
    return fb->getNextFileName();
#else
    //static fs::directory_iterator it(fs::path(fb->getloc().name()));
    //*isDir = fs::is_directory(it->path());
    return "";//it->path().filename().string();
#endif
}

time_t shs::File::getLastWrite()
{
    if (!fb)
        return -1;
#ifdef ARDUINO
    return fb->getLastWrite();
#else
    // struct stat result;
    // if (stat(fs::path(fb->getloc().name()).c_str(), &result) == 0)
    //   return result.st_mtime;
    return -1;
#endif
}

bool shs::File::seekDir(long position)
{
    if (!fb)
        return false;
#ifdef ARDUINO
    return fb->seekDir(position);
#else
    fb->seekg(position, std::ios_base::beg);
    return true;
#endif
}

void shs::File::rewindDirectory()
{
    if (!fb)
        return;
#ifdef ARDUINO
    fb->rewindDirectory();
#else
    //fs::directory_iterator it(fs::path(fb->getloc().name()));
   // it = fs::directory_iterator(fs::path(fb->getloc().name()));
#endif
}

shs::File::operator bool()
{
    return fb != nullptr && fb->operator bool();
}
#ifdef ARDUINO
shs::File& shs::File::operator=(shs::File& other)
{
    if (this == &other)
        return *this;
    if (fb)
        fb->close();

    fb = other.fb;




    return *this;
}
#else

shs::File& shs::File::operator=(const shs::FileCreateData& data)
{
    if (fstr) fstr.close();
    fstr.open(data.path, m_createOpenMode(data.mode, data.create));
    fb = &fstr;
    return *this;
}

std::ios_base::openmode shs::File::m_createOpenMode(const char* mode, bool create)
{
    std::ios_base::openmode cpp_mode{};

    switch (mode[0])
    {
    case 'w':
        cpp_mode = std::ios_base::in | std::ios_base::out | std::ios_base::binary;
        if (create) cpp_mode |= std::ios_base::trunc;
        break;
    case 'r':
        cpp_mode = std::ios_base::in | std::ios_base::binary;
        break;
    case 'a':
        cpp_mode = std::ios_base::app | std::ios_base::binary;
        break;
    }
    return cpp_mode;
}

std::ios_base::seekdir shs::File::m_createSeekMode(shs::file::SeekMode mode)
{
    std::ios_base::seekdir cpp_mode{};
    switch (mode)
    {
    default:
        [[fallthrough]];
    [[likely]] case shs::file::SeekSet:
        cpp_mode = std::ios_base::beg;
        break;
    case shs::file::SeekCur:
        cpp_mode = std::ios_base::cur;
        break;
    case shs::file::SeekEnd:
        cpp_mode = std::ios_base::end;
        break;
    }
    return cpp_mode;
}
#endif


