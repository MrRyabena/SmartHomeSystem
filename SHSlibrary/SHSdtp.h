/*
  Smart Home System Data Transmission Protocol
*/

#pragma once
#include <Arduino.h>
#include <GBUS.h>


#define DTP_OFFSET 4

class DTP {

public:
    DTP(GBUS* gbus, uint8_t address, uint8_t bufSize) {
        _myAddress = address;
        _gbus = gbus;
        _bufSize = bufSize;
    };

    ~DTP() {

    }


    bool sendBuf(uint8_t to, uint8_t* data, uint8_t dataSize) {
        _txSize = packDTPbuf(_gbus->buffer, _bufSize, data, dataSize, to, _myAddress);
        if (_txSize == 0) {
            return false;
        }
        _gbus->sendRaw(_gbus->buffer, _txSize);
        return true;
    }


    // template <typename T>
    // uint8_t packDTPdata(uint8_t* buffer, uint8_t bufSize, T& data, uint8_t to, uint8_t from) {
    //     buffer[0] = sizeof(T) + DTP_OFFSET;      // размер пакета с учётом служебных
    //     if (buffer[0] > bufSize) return 0;        // если переполним буфер
    //     buffer[1] = to;                           // адрес приёмника
    //     buffer[2] = from;                        // адрес передатчика    
    //     const uint8_t* ptr = (const uint8_t*)&data;                                // указатель
    //     for (uint16_t i = 0; i < sizeof(T); i++) buffer[i + 3] = *ptr++;            // пакуем дату    
    //     if (GBUS_CRC) buffer[sizeof(T) + 3] = GBUS_crc_bytes(buffer, sizeof(T) + 3);// crc    
    //     return buffer[0];
    // }


    uint8_t packDTPbuf(uint8_t* buffer, uint8_t bufSize, uint8_t* data, uint8_t dataSize, uint8_t to, uint8_t from) {
        buffer[0] = dataSize + DTP_OFFSET;      // размер пакета с учётом служебных
        if (buffer[0] > bufSize) return 0;        // если переполним буфер
        buffer[1] = to;                           // адрес приёмника
        buffer[2] = from;                        // адрес передатчика    
        for (uint16_t i = 0; i < dataSize; i++) buffer[i + 3] = *data++;            // пакуем дату    
        if (GBUS_CRC) buffer[dataSize + 3] = crc_bytes(buffer, dataSize + 3);// crc    
        return buffer[0];
    }


    template <typename T>
    bool unpackGBUSdata(uint8_t* buffer, uint8_t bufSize, T& data) {
        if (sizeof(T) + DTP_OFFSET > bufSize) return false;    // если данные больше буфера (+ служебная инфа протокола)
        uint8_t* ptr = (uint8_t*)&data;
        for (uint16_t i = 0; i < sizeof(T); i++) *ptr++ = buffer[i + 3];    // пишем
        return true;
    }

    template <typename T>
    void packBytes(uint8_t* buffer, T& data) {
        uint8_t* ptr = (uint8_t*)&data;
        for (uint16_t i = 0; i < sizeof(T); i++) {
            buffer[i] = *ptr++;
        }
    }

    template <typename T>
    void unpackBytes(uint8_t* buffer, T& data) {
        uint8_t* ptr = (uint8_t*)&data;
        for (uint16_t i = 0; i < sizeof(T); i++) {
            *ptr++ = buffer[i];
        }
    }


    template <typename T>
    uint8_t getCRC(T& data) {
        uint8_t crc = 0;
        uint8_t* ptr = (uint8_t*)&data;

        for (uint16_t i = 0; i < sizeof(T); i++) crc_update(crc, *ptr);
        return crc;
    }


    void crc_update(uint8_t& crc, uint8_t data) {
#if defined (__AVR__)
        // резкий алгоритм для AVR
        uint8_t counter;
        uint8_t buffer;
        asm volatile (
            "EOR %[crc_out], %[data_in] \n\t"
            "LDI %[counter], 8          \n\t"
            "LDI %[buffer], 0x8C        \n\t"
            "_loop_start_%=:            \n\t"
            "LSR %[crc_out]             \n\t"
            "BRCC _loop_end_%=          \n\t"
            "EOR %[crc_out], %[buffer]  \n\t"
            "_loop_end_%=:              \n\t"
            "DEC %[counter]             \n\t"
            "BRNE _loop_start_%="
            : [crc_out] "=r" (crc), [counter]"=d" (counter), [buffer]"=d" (buffer)
            : [crc_in] "0" (crc), [data_in]"r" (data)
            );
#else
        // обычный для всех остальных
        uint8_t i = 8;
        while (i--) {
            crc = ((crc ^ data) & 1) ? (crc >> 1) ^ 0x8C : (crc >> 1);
            data >>= 1;
        }
#endif
    }


    uint8_t crc_bytes(uint8_t* buffer, uint8_t size) {
        uint8_t crc = 0;
        for (uint8_t i = 0; i < size; i++) crc_update(crc, buffer[i]);
        return crc;
    }

private:
    uint8_t _myAddress = 0;
    GBUS* _gbus{};
    uint8_t _bufSize = 0;
    uint8_t _txSize{};


};
