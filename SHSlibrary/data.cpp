#include "data.h"

// SHSDataTransfer::SHSDataTransfer(Stream* stream, uint8_t ID) {
//     _ID = ID;
//     _stream = stream;
// }

// template
// void SHSDataTransfer::tick(T data) {
//     if (stream.abailable()) {
//         uint8_t* ptr = (uint8_t*)&data;
//         while (stream.available()) {
//             *ptr++ = stream.read();
//         }
//     }
// }

// void SHSDataTransfer::attach(void(*attached)) {
//     _attached = *attached;
// }





// CRC
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


float getAnalogAverage(uint8_t pin, const uint8_t samples) {
    uint16_t aver = 0;
    //for (uint8_t i = 0; i < samples; i++) aver += analogRead(pin);
    return ((float)aver / samples);
}
