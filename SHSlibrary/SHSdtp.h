/*
  Smart Home System Data Transmission Protocol
*/

#pragma once
#include "SHSalgoritm.h"
#include "SHSByteCollector.h"
#define DTP_OFFSETbeg 3

namespace shs
{
    struct DTPdata
    {
        uint8_t from{};
        uint8_t to{};
        uint8_t datasize{};
    };
};

namespace shs
{
    enum DTPcommands : uint8_t
    {
        answer = 253,
        request,
    };
};

namespace shs
{
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

        uint8_t packDTP(shs::ByteCollector *bc, uint8_t to)
        {
            return packDTP(bc, to, _myID);
        }

        uint8_t packDTP(shs::ByteCollector *bc, uint8_t to, uint8_t from)
        {
            bc->reserveBefore(3);
            bc->buf[1] = to;
            bc->buf[2] = from;
            bc->buf[0] = bc->size() + 1;
            bc->add(shs::crc_8(bc->buf, bc->size()), 1);
            
            return bc->buf[0];
        }

        uint8_t checkDTP(shs::ByteCollector *bc)
        {
            if (bc->size() < bc->buf[0] - 1)
                return 1;
            if (bc->size() > bc->buf[0])
                return 2;

            uint16_t crc = shs::crc_8(bc->buf, bc->buf[0] - 1);
            if (bc->buf[bc->buf[0] - 1] != crc)
                return 3;
            return 0;
        }

        uint8_t parseDTP(shs::ByteCollector *bc, void (*callback)(shs::DTPdata &, shs::ByteCollector *))
        {
            uint8_t status = checkDTP(bc);
            if (status)
                return status;

            shs::DTPdata data{};
            data.from = bc->buf[2];
            data.to = bc->buf[1];
            data.datasize = bc->size() - DTP_OFFSETbeg - 1;
            bc->readPtr = bc->buf + DTP_OFFSETbeg;
            callback(data, bc);
            return 0;
        }

    private:
        uint8_t _myID{};
    };
};
