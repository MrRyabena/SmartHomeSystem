#pragma once


#include <stdint.h>

#include "shs_settings_private.h"

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

    constexpr IP& operator=(const char* ipAddress) { m_IP = ipFromStr(ipAddress); return *this; }
    constexpr IP& operator=(const uint32_t ipAddress) { m_IP = ipAddress; return *this; }

    IP(const IP& other) : m_IP(other.m_IP) {}
    IP(IP&& other) : m_IP(other.m_IP) { other.m_IP = 0; }

    IP& operator=(const IP& other) { m_IP = other.m_IP; return *this; }
    IP& operator=(IP&& other) { m_IP = other.m_IP; other.m_IP = 0; return *this; }


    static constexpr uint32_t ipFromStr(const char* m_IP);

    operator uint32_t() const { return m_IP; }

#if (defined(SHS_SF_ESP8266) || defined(SHS_SF_ESP32))
    operator IPAddress() const { return IPAddress(m_IP); }
#endif

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
