#pragma once

/*
  The main file class designed for convenient operation on different systems.
*/

/*
  Last update: v1.2.0
  Versions:
    v1.2.0 — created.
*/

#include "shs_settings_private.h"
#include "shs_FileAbstract.h"

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
    class File;
}

// ----------------------------------------

class shs::File : public shs::FileAbstract
{

public:
    File(shs::fs::File_basic_t* file = nullptr);
    virtual File& operator=(shs::fs::File_basic_t* file);

    ~File() override;

    shs::fs::File_basic_t* fb{};
    uint8_t bufsize;  // default: 32

public:
    // Added methods
    virtual size_t available() { return size() - position(); }
    virtual size_t shiftRight(const size_t from, const size_t indent);
    virtual size_t shiftLeft(const size_t from, const size_t indent);
    virtual size_t insert(const uint8_t* buf, const size_t size, const size_t from, const size_t before);

    void write(uint8_t value) { write(&value, 1); };
    uint8_t read() { uint8_t value{}; read(&value, 1); return value; };
    uint8_t read(uint8_t& value) { read(&value, 1); return value; }


    // Overridden methods 
    size_t write(const uint8_t* buf, size_t size) override;
    size_t read(uint8_t* buf, size_t size) override;
    void flush() override;
    bool seek(uint32_t pos, shs::fs::SeekMode mode = shs::fs::Seek_Set) override;
    size_t position() const override;
    size_t size() override;
    void close() override;
    time_t getLastWrite() override;
    shs::settings::shs_string_t path() const override;
    shs::settings::shs_string_t name() const override;
    bool isDirectory(void) override;
    bool seekDir(long position) override;
    shs::settings::shs_string_t getNextFileName(void) override;
    shs::settings::shs_string_t getNextFileName(bool* isDir) override;
    void rewindDirectory(void) override;
    operator bool() override;

}; // class shs::File : public shs::FileAbstract
