#include "SHSFile.h"

// ----------------------------------------
// Constructors
// ----------------------------------------
shs::File::File(shs::fs::File_basic_t* file) : bufsize(32)
{
    if (fb) { fb->close(); delete fb; }
    fb = file;
}

shs::File& shs::File::operator=(shs::fs::File_basic_t* file)
{
    if (fb) { fb->close(); delete fb; }
    fb = file;
    return *this;
}

shs::File::~File()
{
    if (fb) { fb->close(); delete fb; }
}

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
// Overridden methods
// ----------------------------------------
size_t shs::File::write(const uint8_t* buf, size_t size)
{
    if (!fb) return 0;
#ifdef ARDUINO
    return fb->write(buf, size);
#else
    fb->write(reinterpret_cast<const char*>(buf), size);
    return fb->gcount();
#endif
}

size_t shs::File::read(uint8_t* buf, size_t size)
{
    if (!fb) return 0;
#ifdef ARDUINO
    return fb->read(buf, size);
#else
    fb->read(reinterpret_cast<char*>(buf), size);
    return fb->gcount();
#endif
}

void shs::File::flush()
{
    if (!fb) return;
    fb->flush();
}

bool shs::File::seek(uint32_t pos, shs::fs::SeekMode mode)
{
    if (!fb) return false;
#ifdef ARDUINO
    return fb->seek(pos, mode);
#else
    fb->seekg(pos, createSeekMode(mode));
    return true;
#endif
}

size_t shs::File::position() const
{
    if (!fb) return 0;
#ifdef ARDUINO
    return fb->position();
#else
    return fb->tellg();
#endif
}

size_t shs::File::size()
{
    if (!fb) return 0;
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
    if (!fb) return;

    fb->close();
    delete fb;
    fb = nullptr;
}

shs::settings::shs_string_t shs::File::path() const
{
    if (!fb) return "";
#ifdef ARDUINO
    return fb->path();
#else
    return "";
#endif
}

shs::settings::shs_string_t shs::File::name() const
{
    if (!fb) return "";
#ifdef ARDUINO
    return fb->name();
#else
    return "";
#endif
}

bool shs::File::isDirectory(void)
{
    if (!fb) return false;
#ifdef ARDUINO
    return fb->isDirectiry();
#else
    return false;
#endif
}

shs::settings::shs_string_t shs::File::getNextFileName()
{
    if (!fb) return "";
#ifdef ARDUINO
    return fb->getNextFileName();
#else
    return "";
#endif
}

shs::settings::shs_string_t shs::File::getNextFileName(bool* isDir)
{
    if (!fb) return "";
#ifdef ARDUINO
    return fb->getNextFileName();
#else
    return "";
#endif
}

time_t shs::File::getLastWrite()
{
    if (!fb) return -1;
#ifdef ARDUINO
    return fb->getLastWrite();
#else
    return -1;
#endif
}

bool shs::File::seekDir(long position)
{
    if (!fb) return false;
#ifdef ARDUINO
    return fb->seekDir(position);
#else
    fb->seekg(position, std::ios_base::beg);
    return true;
#endif
}

void shs::File::rewindDirectory()
{
    if (!fb) return;
#ifdef ARDUINO
    fb->rewindDirectory();
#else

#endif
}

shs::File::operator bool()
{
    return (fb != nullptr && bool(*fb));
}
