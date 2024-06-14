#pragma once

/*
  Last update: v1.2.0
  Versions:
    v1.2.0 — created.
    v2.0.0 — integrated shs_types.h.
*/

#include <stddef.h>
#include <stdint.h>

#include "shs_types.h"

#ifdef SHS_SF_ARDUINO
#include <Arduino.h>
#include <FS.h>
#else
#include <ios>
#include <fstream>
#endif

namespace shs
{
    namespace fs
    {
        enum SeekMode : uint8_t;

#ifdef SHS_SF_ARDUINO
        using File_basic_t = File;
#else
        using File_basic_t = std::fstream;
        // Helper methods for non-Arduino platforms
        static std::ios::seekdir createSeekMode(shs::fs::SeekMode mode);
#endif 
    }

    class FileAbstract;
};

enum shs::fs::SeekMode : uint8_t
{
    Seek_Set = 0,
    Seek_Cur = 1,
    Seek_End = 2
};

class shs::FileAbstract
{
public:
    virtual ~FileAbstract() = default;


    virtual size_t write(const uint8_t* buf, size_t size) = 0;
    virtual size_t read(uint8_t* buf, size_t size) = 0;
    virtual void flush() = 0;
    virtual bool seek(uint32_t pos, shs::fs::SeekMode mode = shs::fs::Seek_Set) = 0;
    virtual size_t position() const = 0;
    virtual size_t size() = 0;
    virtual void close() = 0;
    virtual time_t getLastWrite() = 0;
    virtual shs::t::shs_string_t path() const = 0;
    virtual shs::t::shs_string_t name() const = 0;
    virtual bool isDirectory(void) = 0;
    virtual bool seekDir(long position) = 0;
    virtual shs::t::shs_string_t getNextFileName(void) = 0;
    virtual shs::t::shs_string_t getNextFileName(bool* isDir) = 0;
    virtual void rewindDirectory(void) = 0;
    virtual operator bool() = 0;
};

#ifdef SHS_SF_ARDUINO

#else
std::ios::seekdir shs::fs::createSeekMode(shs::fs::SeekMode mode)
{
    std::ios::seekdir cpp_mode{};
    switch (mode)
    {
    [[unlikely]] default: [[fallthrough]];
    [[likely]] case shs::fs::Seek_Set: cpp_mode = std::ios::beg; break;
    case            shs::fs::Seek_Cur: cpp_mode = std::ios::cur; break;
    case            shs::fs::Seek_End: cpp_mode = std::ios::end; break;
    }
    return cpp_mode;
}
#endif
