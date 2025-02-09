#pragma once


#include <stdint.h>

#include "shs_settings_private.h"
#include "shs_types.h"

#if defined(SHS_SF_ESP8266) || defined(SHS_SF_ESP32)
#include <IPAddress.h>
#endif

namespace shs
{
    struct IP;
}


struct shs::IP
{
    constexpr IP(const char* ipAddress) : m_IP(ipFromStr(ipAddress)) {}
    constexpr IP(const uint32_t ipAddress = 0) : m_IP(ipAddress) {}

#ifdef SHS_SF_ESP
    IP(const IPAddress& ipAddress) : m_IP(reverse_bytes(static_cast<uint32_t>(ipAddress))) {}
    IP& operator=(const IPAddress& ipAddress) { m_IP = reverse_bytes(static_cast<uint32_t>(ipAddress)); return *this; }
#endif

    constexpr IP& operator=(const char* ipAddress) { m_IP = ipFromStr(ipAddress); return *this; }
    constexpr IP& operator=(const uint32_t ipAddress) { m_IP = ipAddress; return *this; }

    IP(const IP& other) : m_IP(other.m_IP) {}
    IP(IP&& other) : m_IP(other.m_IP) { other.m_IP = 0; }

    IP& operator=(const IP& other) { m_IP = other.m_IP; return *this; }
    IP& operator=(IP&& other) { m_IP = other.m_IP; other.m_IP = 0; return *this; }


    static constexpr uint32_t ipFromStr(const char* m_IP);
    // shs::t::shs_string_t toString() { return shs::t::shs_string_t(m_IP >> 24) + '.' + (m_IP >> 16) & 0xff + '.' + (m_IP >> 8) & 0xff + '.' + m_IP & 0xff; }

    operator uint32_t() const { return m_IP; }

#ifdef SHS_SF_ESP
    operator IPAddress() const { return reverse_bytes(m_IP); }
#endif

    static constexpr uint32_t reverse_bytes(const uint32_t ip) { return ((ip >> 24) & 0xFF) | ((ip << 8) & 0xFF0000) | ((ip >> 8) & 0xFF00) | ((ip << 24) & 0xFF000000); }

private:
    uint32_t m_IP;

    static constexpr uint32_t m_parseOctet(const char* str, size_t& index);
    static constexpr uint32_t m_ipToUInt32(const char* str, size_t index = 0);
};


constexpr uint32_t shs::IP::ipFromStr(const char* ip)
{
    size_t index = 0;
    return m_ipToUInt32(ip, index);
}


constexpr uint32_t shs::IP::m_parseOctet(const char* str, size_t& index)
{
    uint32_t value = 0;

    while (str[index] >= '0' && str[index] <= '9')
    {
        value = value * 10 + (str[index] - '0');
        ++index;
    }
    return value;
}


constexpr uint32_t shs::IP::m_ipToUInt32(const char* str, size_t index)
{
    uint32_t result = 0;

    for (int i = 0; i < 4; ++i)
    {
        result <<= 8;
        result |= m_parseOctet(str, index);
        if (str[index] == '.') ++index;
    }

    return result;
}
