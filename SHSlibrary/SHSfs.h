#pragma once
#include <Arduino.h>
#include <FS.h>
#include <SHSalgoritm.h>

namespace shs
{
    class SHSfs;
};

class shs::SHSfs
{
public:
    SHSfs(fs::FS *FS)
    {
        _fs = FS;
    }

    ~SHSfs()
    {
    }

    void open(const char *name, const char *mode = "r")
    {
        if (!o_file)
            o_file.close();
        o_file = _fs->open(name, mode);
        _file = &o_file;
    }

    void close()
    {
        _file->close();
        _file = nullptr;
    }

    template <typename T>
    uint16_t read(T &data)
    {
        uint8_t *ptr = (uint8_t *)&data;
        for (uint16_t i = 0; i < sizeof(data); i++)
            *ptr++ = o_file.read();
        return sizeof(T);
    }

    template <typename T>
    uint16_t read(T &data, fs::File *file)
    {
        uint8_t *ptr = (uint8_t *)&data;
        for (uint16_t i = 0; i < sizeof(data); i++)
            *ptr++ = file->read();
        return sizeof(T);
    }

    template <typename T>
    void write(T &data)
    {
        uint8_t *ptr = (uint8_t *)&data;
        for (uint16_t i = 0; i < sizeof(data); i++)
            o_file.write(*ptr++);
    }

    template <typename T>
    void write(T &data, File *file)
    {
        uint8_t *ptr = (uint8_t *)&data;
        for (uint16_t i = 0; i < sizeof(data); i++)
            file->write(*ptr++);
    }

    String readBefore(char symb)
    {
        return readBefore(symb, _file);
    }

    String readBefore(char symb, File *file)
    {
        String str{};
        while (file->peek() != symb)
            str += (char)file->read();
        return str;
    }

    void copy(File *sourse, File *drain, uint32_t size)
    {
        for (uint32_t i = 0; i < size; i++)
            drain->write(sourse->read());
    }

    template <typename T>
    void edit(const char *fname, uint32_t from, uint32_t before, T &data)
    {
        open(fname);
        File cfile = _fs->open("/cfile.shsf", "w+");
        copy(_file, &cfile, _file->size());
        cfile.seek(0);
        close();
        _fs->remove(fname);
        open(fname);
        copy(_file, &cfile, from);
        uint8_t *ptr = (uint8_t *)&data;
        for (uint16_t i; i < sizeof(data); i++)
            *ptr++ = _file->read();
        cfile.seek(before);
        copy(&cfile, _file, cfile.size());
        _fs->remove("/cfile.shsf");
    }

    uint8_t getFileCRC_8(fs::File *file)
    {
        file->seek(0);
        uint8_t crc = shs::CRC8_beg;
        while (file->position() != file->size() - 1)
        {
            shs::crc_8_update(crc, file->read());
        }
        return crc;
    }

    uint16_t getFileCRC_16(fs::File *file)
    {
        file->seek(0);
        uint16_t crc = shs::CRC16_beg;
        while (file->position() != file->size() - 1)
        {
            shs::crc_16_update(crc, file->read());
        }
        return crc;
    }

    uint32_t getFileCRC_32(fs::File *file)
    {
        file->seek(0);
        uint32_t crc = shs::CRC32_beg;
        while (file->position() != file->size() - 1)
        {
            shs::crc_32_update(crc, file->read());
        }
        return crc;
    }

    fs::File *_file = nullptr;

private:
    fs::FS *_fs = nullptr;
    fs::File o_file;
};
