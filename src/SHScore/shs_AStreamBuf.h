#pragma once

#include <streambuf>
#include <iostream>


#include <Stream.h>
#include <Arduino.h>


namespace shs
{
    template <class, class>
    class Basic_AStreamBuf;

    using AStreamBuf = Basic_AStreamBuf<char, std::char_traits<char>>;

    extern AStreamBuf serial_ASreamBuf;

    /**
     * @brief Redirects standard C++ input/output streams to Arduino Serial.
     *
     * This function configures std::cin, std::cout and std::cerr to work with Arduino Serial,
     * allowing the use of standard C++ input/output streams in Arduino projects.
     * After calling this function, all std::cout operations will be sent through Serial,
     * and std::cin will read data from Serial.
     *
     * @note Should be called after Serial.begin() initialization
     * @note Uses global serial_ASreamBuf object for stream redirection
     */
    extern void rd_cio_to_ASerial();
}


/**
 * @brief Stream buffer wrapper for Arduino Stream class.
 *
 * This class provides a bridge between Arduino's Stream class and C++ standard
 * stream interfaces. It allows using Arduino Stream objects with standard C++
 * stream operations like std::istream and std::ostream.
 *
 * The wrapper implements the std::basic_streambuf interface, enabling
 * seamless integration with C++ stream libraries while maintaining
 * compatibility with Arduino Stream functionality.
 *
 * @tparam CharT Character type (default: char)
 * @tparam Traits Character traits type (default: std::char_traits<CharT>)
 */
template <class CharT, class Traits = std::char_traits<CharT>>
class shs::Basic_AStreamBuf : public std::basic_streambuf<CharT, Traits>
{
public:
    /**
     * @brief Constructs a stream buffer wrapper for Arduino Stream.
     *
     * @param astream Reference to the Arduino Stream object to wrap
     */
    Basic_AStreamBuf(Stream& astream) : m_astream(astream)//, m_buffer(0)
    {
        //this->setg(nullptr, nullptr, nullptr);
    }

    /**
     * @brief Virtual destructor.
     */
    ~Basic_AStreamBuf() override = default;

protected:
    /**
     * @brief Writes a character to the Arduino Stream.
     *
     * @param c Character to write
     * @return int_type The written character or traits_type::eof() on failure
     */
    typename Traits::int_type overflow(typename Traits::int_type c) override
    {
        if (c == Traits::eof()) return Traits::eof();

        m_astream.write(static_cast<CharT>(c));
        return c;
    }

    /**
     * @brief Returns the number of characters available for reading without blocking.
     *
     * @return std::streamsize Number of available characters, 0 if none, -1 on error
     */
    std::streamsize showmanyc() override
    {
        return m_astream.available();
    }

    /**
     * @brief Reads a character from the Arduino Stream.
     *
     * @return int_type The read character or traits_type::eof() if no data available
     */
    typename Traits::int_type underflow() override
    {
        // if (this->gptr() < this->egptr())
         //{
          //   return Traits::to_int_type(*this->gptr());
         //}
        // Serial.println("underflow");

        while (m_astream.available() == 0) delay(1);
        //if (m_astream.available() == 0) return Traits::eof();

        auto c = m_astream.peek();
        if (c == -1)
        {
            return Traits::eof();
        }

        // this->setg(&m_buffer, &m_buffer, &m_buffer + 1);
         //m_buffer = static_cast<typename Traits::char_type>(c);

        return Traits::to_int_type(c);
    }

    /**
     * @brief Reads a character and advances the get pointer.
     *
     * @return int_type The read character or traits_type::eof() if no data available
     */
    typename Traits::int_type uflow() override
    {
        while (m_astream.available() == 0) delay(1);
        //if (m_astream.available() == 0) return Traits::eof();

        // Serial.println("uflow");

        typename Traits::int_type c = m_astream.read(); //underflow();


        if (c != Traits::eof())
        {
            this->gbump(1);
        }
        return c;
    }

    /**
     * @brief Synchronizes the stream buffer with the underlying Arduino Stream.
     *
     * @return int_type traits_type::eof() on failure, 0 on success
     */
    int sync() override
    {
        m_astream.flush();
        return 0;
    }

    /**
     * @brief Writes multiple characters to the Arduino Stream.
     *
     * @param s Pointer to the character array to write
     * @param n Number of characters to write
     * @return std::streamsize Number of characters successfully written
     */
    std::streamsize xsputn(const typename Traits::char_type* s, std::streamsize n) override
    {
       // Serial.println("xsputn");
        return m_astream.write(reinterpret_cast<const uint8_t*>(s), n);
    }

    /**
     * @brief Reads multiple characters from the Arduino Stream.
     *
     * @param s Pointer to the character array to store read data
     * @param n Number of characters to read
     * @return std::streamsize Number of characters successfully read
     */
    std::streamsize xsgetn(typename Traits::char_type* s, std::streamsize n) override
    {
        std::streamsize total_read = 0;
        std::streamsize available = m_astream.available();

        if (available > 0)
        {
            std::streamsize to_read = (n < available) ? n : available;
            total_read = m_astream.readBytes(reinterpret_cast<uint8_t*>(s), to_read);
        }
        //Serial.println("xsgetn");

        return total_read;
    }

    // /**
    //  * @brief Puts back a character to the stream buffer.
    //  *
    //  * Note: Arduino Stream doesn't support putback, so this always fails.
    //  *
    //  * @param c Character to put back
    //  * @return int_type traits_type::eof() on failure, c on success
    //  */
    // typename Traits::int_type pbackfail(typename Traits::int_type c = Traits::eof()) override
    // {
    //     // Arduino Stream doesn't support putback
    //     return Traits::eof();
    // }

    // /**
    //  * @brief Seeks to a position in the stream.
    //  *
    //  * Note: Arduino Stream doesn't support seeking, so this always fails.
    //  *
    //  * @param off Offset to seek to
    //  * @param way Seek direction
    //  * @param which Which buffer to seek in
    //  * @return pos_type Current position (always -1 for failure)
    //  */
    // typename Traits::pos_type seekoff(typename Traits::off_type off, std::ios_base::seekdir way,
    //     std::ios_base::openmode which = std::ios_base::in | std::ios_base::out) override
    // {
    //     // Arduino Stream doesn't support seeking
    //     return typename Traits::pos_type(typename Traits::off_type(-1));
    // }

    // /**
    //  * @brief Seeks to a position in the stream.
    //  *
    //  * Note: Arduino Stream doesn't support seeking, so this always fails.
    //  *
    //  * @param sp Position to seek to
    //  * @param which Which buffer to seek in
    //  * @return pos_type Current position (always -1 for failure)
    //  */
    // typename Traits::pos_type seekpos(typename Traits::pos_type sp,
    //     std::ios_base::openmode which = std::ios_base::in | std::ios_base::out) override
    // {
    //     // Arduino Stream doesn't support seeking
    //     return typename Traits::pos_type(typename Traits::off_type(-1));
    // }

    // /**
    //  * @brief Sets the buffer area.
    //  *
    //  * Note: This is a no-op for Arduino Stream wrapper.
    //  *
    //  * @param s Pointer to buffer area
    //  * @param n Size of buffer area
    //  * @return char_type* Pointer to the buffer area
    //  */
    //  // typename Traits::char_type* setbuf(typename Traits::char_type* s, std::streamsize n) override
    //  // {
    //  //     // Arduino Stream manages its own buffer, so we ignore this
    //  //     return nullptr;
    //  // }

private:
    Stream& m_astream;
    //typename Traits::char_type m_buffer; // Buffer for uflow()

};

