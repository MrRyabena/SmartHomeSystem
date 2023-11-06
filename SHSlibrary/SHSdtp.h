/*
  Smart Home System Data Transmission Protocol
*/

#pragma once

#define DTP_OFFSETbeg 3

class DTP
{

public:
    DTP(uint8_t ID)
    {
        _myID = ID;
    };

    ~DTP()
    {
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

    uint8_t packDTP(shs::ByteCollector *bc, uint8_t to, uint8_t from = _myID)
    {
        bc->reserveBefore(DTP_OFFSET);
        bc->buf[1] = to;
        bc->buf[2] = from;
        bc->add(shs::crc_16(bc->buf, bc->size()));
        bc->buf[0] = bc->size();
    }
 

private:
    uint8_t _myID = 0;
};
