#pragma once

// CRC
// CRC_8
uint8_t crc_8(const uint8_t * ptr, uint16_t size);
void crc_8_update(uint8_t& crc, uint8_t data);
uint16_t crc_16(const uint8_t *ptr, uint16_t size);
uint32_t crc_32(const uint8_t *ptr, uint16_t size);


//
uint8_t crc_8(const uint8_t * ptr, uint16_t size) {
    uint8_t crc = 0;
    for (uint16_t i = 0; i < size; i++) crc_8_update(crc, *ptr);
    return crc;
}

void crc_8_update(uint8_t& crc, uint8_t data) {
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

#define CRC16 0x8005
uint16_t crc_16(const uint8_t *ptr, uint16_t size) {

    uint16_t out = 0;
    uint16_t bit_flag{};
    uint8_t bits_read{};

    while (size > 0) {
      bit_flag = out >> 15;
      out <<= 1;
      out |= (*ptr >> bits_read) & 1;
      bits_read ++;
      if (bits_read > 7) {
        bits_read = 0;
        ptr ++;
        size--;
      }

      if (bit_flag) out ^= CRC16;
      uint16_t i;
      for (i = 0; i < 16; i++) {
        bit_flag = out >> 15;
        out <<= 1;
        if (bit_flag) out ^= CRC16;
      }

      uint16_t crc = 0;
      i = 0x8000;
      uint16_t j = 0x0001;
      for (; i != 0; i >>= 1, j <<= 1) {
        if (i & out) crc |= j;
      }
      return crc;
      

    }
}

uint32_t crc_32(const uint8_t *ptr, uint16_t size) {
    uint32_t crc = 0xFFFFFFFF;
    while (size--) {
        crc ^= *ptr++;
        for (uint8_t bit = 0; bit < 8; bit++) {
            if (crc & 1) crc = (crc >> 1) ^ 0xEDB88320;
            else crc = (crc >> 1);
        }
    }
    return crc ^ 0xFFFFFFFF;
}
