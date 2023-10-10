#pragma once
#include <Arduino.h>
//#include <File.h>



// class SHSDataTransfer {
// public:
//     SHSDataTransfer(Stream* stream, uint8_t ID);

//     void attach(void(*_attached));


//     template <typename T>
//         void tick(T data);



// private:
//     uint8_t _ID;
//     Stream* _stream;
//     <template T>
//         void (*attached)(T& data);

// };





float getAnalogAverage(uint8_t pin, const uint8_t samples = 20);
// CRC
template <typename T>
uint8_t getCRC(T& data);
void crc_update(uint8_t& crc, uint8_t data);
uint8_t crc_bytes(uint8_t* buffer, uint8_t size);





//  Pack/unpack bytes
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



// Read/write files

// template <typename T>
// uint16_t readBytes(File* file, T& data) {
//     uint8_t* ptr = (uint8_t*)&data;
//     for (uint16_t i = 0; i < sizeof(T); i++) *ptr++ = file->read();
//     return (file->position());
// }


// template <typename T>
// uint16_t readBytes(File* file, T& data, uint16_t from) {
//     file->seek(from);
//     return readBytes(file, data);
// }


// template <typename T>
// void writeBytes(File* file, T& data) {
//     uint8_t* ptr = (uint8_t*)&data;
//     for (uint16_t i = 0; i < sizeof(T); i++) file->write(*ptr++);
// }





