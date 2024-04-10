#pragma once

/*
  The main file class designed for convenient operation on different systems.
*/

/*
  Last update: v1.2.0
  Versions:
    v1.2.0 — created.
*/

#include "SHSsettings_private.h"
#include "SHSFileAbstract.h"

#ifdef ARDUINO
#include <Arduino>
#include <FS.h>
#else
#include <fstream>
#endif

#include <stddef.h>
#include <stdint.h>

// ----------------------------------------

namespace shs
{
#ifdef ARDUINO
    using File_base_t = fs::File;
#else
    using File_base_t = std::fstream;
#endif
    struct FileCreateData;
    class File;
}

// ----------------------------------------

struct shs::FileCreateData
{
    const char* path;
    const char* mode;
    bool create;
};

// ----------------------------------------

class shs::File : public shs::FileAbstract
{

public:
    explicit File(shs::File_base_t* file = nullptr);
#ifndef ARDUINO
    // Constructors for non-Arduino platforms
    File(const char* path, const char* mode, bool create = false);
    File(const shs::FileCreateData& data);
    std::fstream fstr;
#endif
    shs::File_base_t* fb{};

public:
    // Added methods
    size_t available() { return size() - position(); }
    size_t shiftRight(const size_t from, const size_t indent);
    size_t shiftLeft(const size_t from, const size_t indent);
    size_t insert(const uint8_t* buf, const size_t size, const size_t from, const size_t before);
    void write(uint8_t value) { write(&value, 1); };
    uint8_t read() { uint8_t value{}; read(&value, 1); return value; };
    uint8_t bufsize;  // 32

    // Overriden methods 
    size_t write(const uint8_t* buf, size_t size) override;
    size_t read(uint8_t* buf, size_t size) override;
    void flush() override;
    bool seek(uint32_t pos, shs::file::SeekMode mode = shs::file::SeekSet) override;
    size_t position() const override;
    size_t size() override;
    void close() override;
    time_t getLastWrite() override;
    shs::settings::shs_string_t path() const override;
    shs::settings::shs_string_t name() const override;
    bool isDirectory(void) override;
    File& openNextFile(const char* mode) override;
    bool seekDir(long position) override;
    shs::settings::shs_string_t getNextFileName(void) override;
    shs::settings::shs_string_t getNextFileName(bool* isDir) override;
    void rewindDirectory(void) override;
    operator bool() override;

#ifdef ARDUINO
    File& operator=(const shs::File& other);
#else
    File& operator=(const shs::FileCreateData& data);
#endif

protected:
#ifndef ARDUINO
    // Helper methods for non-Arduino platforms
    std::ios_base::openmode m_createOpenMode(const char* mode, bool create);
    std::ios_base::seekdir m_createSeekMode(shs::file::SeekMode mode);
#endif
}; // class shs::File : public shs::FileAbstract
