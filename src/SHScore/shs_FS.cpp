#include "SHSfs.h"

// ----------------------------------------
// Constructors
// ----------------------------------------

shs::FS::FS(shs::fs::FS_basic_t* fs) : fsb(fs) {}

// ----------------------------------------
// Added methods
// ----------------------------------------

bool shs::FS::copy(const char* from, const char* to)
{
    if (!fsb) return false;
    shs::File source = open(from, shs::fs::File_Read);
    shs::File drain = open(to, shs::fs::File_Write, true);
    return (!source || !drain);

    for (auto i = 0; i < source.size(); i++) drain.write(source.read());
    return true;
}

// ----------------------------------------
// Overridden methods
// ----------------------------------------

shs::fs::File_basic_t* shs::FS::open(const char* path, const char* mode, const bool create)
{
#ifdef ARDUINO
    return new shs::fs::File_basic_t(fsb->open(path, mode, create));
#else
    return new shs::fs::File_basic_t(path, shs::fs::createOpenMode(mode, create));
#endif
}

bool shs::FS::exists(const char* path)
{
#ifdef ARDUINO
    return fsb->exists(path);
#else
    return std::filesystem::exists(path);
#endif
}

bool shs::FS::rename(const char* pathFrom, const char* pathTo)
{
#ifdef ARDUINO
    return fsb->rename(pathFrom, pathTo);
#else
    std::error_code e;
    std::filesystem::rename(pathFrom, pathTo, e);
    return static_cast<bool>(e);
#endif
}

bool shs::FS::remove(const char* path)
{
#ifdef ARDUINO
    return fsb->remove(path);
#else
    return std::filesystem::remove(path);
#endif
}

bool shs::FS::mkdir(const char* path)
{
#ifdef ARDUINO
    return fsb->mkdir(path);
#else
    return std::filesystem::create_directory(path);
#endif
}

bool shs::FS::rmdir(const char* path)
{
#ifdef ARDUINO
    return fsb->rmdir(path);
#else
    std::error_code e;
    std::filesystem::remove_all(path, e);
    return static_cast<bool>(e);
#endif
}
