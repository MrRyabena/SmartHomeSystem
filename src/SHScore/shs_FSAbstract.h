#pragma once

/*
  Last update: v1.2.0
  Versions:
    v1.2.0 — created.
*/

#include "shs_FileAbstract.h"
#include "shs_File.h"

#include <stddef.h>
#include <stdint.h>

#ifdef SHS_SF_ARDUINO
#include <FS.h>
#else
#include <ios>
#include <fstream>
#endif

namespace shs
{
    namespace fs
    {
        static constexpr char File_Read [] = "r";
        static constexpr char File_Write [] = "w";
        static constexpr char File_Append [] = "a";

#ifdef SHS_SF_ARDUINO
        using FS_basic_t = FS;
#else
        using FS_basic_t = void;
        // Helper methods for non-Arduino platforms
        static std::ios::openmode createOpenMode(const char* mode, bool create);
#endif
    }

    class FSAbstract;
}


class shs::FSAbstract
{
public:
    virtual ~FSAbstract() = default;

    virtual shs::fs::File_basic_t* open(const char* path, const char* mode = shs::fs::File_Write, const bool create = false) = 0;
    virtual void close(shs::FileAbstract& file) = 0;

    virtual bool exists(const char* path) = 0;
    virtual bool rename(const char* pathFrom, const char* pathTo) = 0;
    virtual bool remove(const char* path) = 0;
    virtual bool mkdir(const char* path) = 0;
    virtual bool rmdir(const char* path) = 0;
};


#ifndef SHS_SF_ARDUINO
std::ios::openmode shs::fs::createOpenMode(const char* mode, bool create)
{
    std::ios::openmode cpp_mode{};

    if (create) cpp_mode |= std::ios::trunc;
    switch (mode[0])
    {
    [[unlikely]] default: [[fallthrough]];
    case 'w': cpp_mode = std::ios::in | std::ios::out | std::ios::binary;  break;
    case 'r': cpp_mode = std::ios::in | std::ios::binary;                  break;
    case 'a': cpp_mode = std::ios::app | std::ios::binary;                 break;
    }

    return cpp_mode;
}
#endif
