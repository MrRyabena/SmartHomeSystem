#pragma once


#include <streambuf>
#include <fstream>
#include <ios>

#include <FS.h>

#include "shs_AFStream.h"
#include "shs_types.h"

namespace shs
{
    template <class, class>
    class Basic_AFStream;

    using AFStream = Basic_AFStream<char, std::char_traits<char>>;
}

/**
 * @brief C++ fstream-like wrapper for Arduino FS File class.
 *
 *
 */
template <class CharT, class Traits = std::char_traits<CharT>>
class shs::Basic_AFStream : public std::basic_iostream<CharT, Traits>
{
public:
    static fs::FS* default_fs_ptr{};


    explicit Basic_AFStream() : std::basic_iostream<CharT, Traits>(nullptr), m_afs_buf(m_file) {}

    explicit Basic_AFStream(const char* filename,
        std::ios_base::openmode mode
        = std::ios_base::in | std::ios_base::out,
       fs::FS* fs = nullptr)
        : std::basic_iostream<CharT, Traits>(nullptr), m_afs_buf(m_file)
    {
        open(path, mode, fs);
    }

    explicit Basic_AFStream(const shs::t::shs_string_t& filename, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out, fs::FS* fs = nullptr)
        : std::basic_iostream<CharT, Traits>(nullptr), m_afs_buf(m_file)
    {
        open(path, mode, fs);
    }

    explicit Basic_AFStream(const basic_fstream& rhs) = delete;

    ~Basic_AFStream() override
    {
        close();
    }


    static constexpr const char* convert_openmode(std::ios_base::openmode mode)
    {
        using m = std::ios_base::openmode;
        if (mode & m::app) return "a";
        if ((mode & m::out) && (mode & m::trunc)) return "w";
        if ((mode & m::out) && !(mode & m::in)) return "w";
        if ((mode & m::in) && !(mode & m::out)) return "r";
        if ((mode & m::in) && (mode & m::out)) return "w";

        return "w";
    }


    bool is_open() const
    {
        return m_file;
    }


    void open(const char* filename, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out)
    {
        close();

        if (fs) m_file = fs->open(path, convert_openmode(mode));
        else if (default_fs_ptr) m_file = default_fs_ptr->open(path, convert_openmode(mode));

        this->rdbuf(is_open() ? &m_buf : nullptr);
    }

    
    void open(const shs::t::shs_string_t& filename, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out)
    {
        open(filename.c_str(), mode);
    }


    void open(const char* path, const char* mode = "r", fs::FS* fs = nullptr)
    {
        close();

        if (fs) m_file = fs->open(path, mode);
        else if (default_fs_ptr) m_file = default_fs_ptr->open(path, mode);

        this->rdbuf(is_open() ? &m_buf : nullptr);
    }


    void close()
    {
        if (m_file)
        {
            m_file.close();
            this->rdbuf(nullptr);
        }
    }

    shs::Basic_AFStreamBuf<CharT, Traits>* rdbuf()
    {
        return &m_afs_buf;
    }

protected:
    File m_file;
    shs::Basic_AFStreamBuf<CharT, Traits> m_afs_buf;
};
