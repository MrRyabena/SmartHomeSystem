#include "SHSCRCTest.h"


int shs::tests::CRCTest::calculateCollisions()
{
    out.sep();
#ifdef ARDUINO
    out.pmln("The test CRCTest::calculateCollisions not designed for this platform!");
    return 0xffff;
#else
    out.pmln("Starting the test CRCTest::calculateCollisions.");
    out.pn("quanity: ");
    out.pnln(quantity);
    out.psln("");

    shs::CRC8 crc8;
    shs::CRC16 crc16;
    shs::CRC32 crc32;

    std::vector<uint8_t> v8(quantity);
    std::vector<uint16_t> v16(quantity);
    std::vector<uint32_t> v32(quantity);

    out.psln("Starting the part 1:");
    out.psln("data-size: [2; 256)");
    out.psln("");

    shs::Random<uint8_t> rnd1(0, 255);
    rnd1.autoSeed();

    int size{};
    uint8_t value{};
    for (auto i = 0; i < quantity; i++)
    {
        size = rnd1.get();
        for (auto j = 0; j < size; j++)
        {
            value = rnd1.get();
            crc8.add(value);
            crc16.add(value);
            crc32.add(value);
        }

        v8.push_back(crc8.crc);
        v16.push_back(crc16.crc);
        v32.push_back(crc32.crc);

        crc8.clear();
        crc16.clear();
        crc32.clear();
    }

    printMMA(v8);
    out.pvln("");
    printMMA(v16);
    out.pvln("");
    printMMA(v32);

    out.psln("\nThe path 1 is completed.\n\n");


    out.psln("Starting the part 2:");
    out.pnln("data-size: quantity");
    out.pnln("tests: 1000");
    out.pvln("");

    for (auto i = 0; i < 1000; i++)
    {
        for (auto j = 0; j < quantity; j++)
        {
            value = rnd1.get();
            crc8.add(value);
            crc16.add(value);
            crc32.add(value);
        }
        v8.push_back(crc8.crc);
        v16.push_back(crc16.crc);
        v32.push_back(crc32.crc);

        crc8.clear();
        crc16.clear();
        crc32.clear();
    }
    printMMA(v8);
    out.pvln("");
    printMMA(v16);
    out.pvln("");
    printMMA(v32);

    out.psln("\nThe path 2 is completed.\n\n");
    out.pmln("The test CRCTest::calculateCollisions is completed with code: 0.");

#endif
    out.sep();
    return 0;
}

int shs::tests::CRCTest::multiplatform()
{
    out.sep();
    out.pmln("Starting the test CRCTest::multiplatform.");
    out.pn("quanity: ");
    out.pnln(quantity);
    out.pvln("");

    uint8_t flags{};

    shs::CRC8 crc8;
    shs::CRC16 crc16;
    shs::CRC32 crc32;

    out.pvln((int)crc8.crcBuf(shs::tests::data.arr1, shs::tests::data.size));
    out.pvln(crc16.crcBuf(shs::tests::data.arr1, shs::tests::data.size));
    out.pvln(crc32.crcBuf(shs::tests::data.arr1, shs::tests::data.size));
    out.pvln("");

    if (crc8.crc != shs::tests::data.crc8arr1) { flags ^= 0b00000001;  out.pmln("ERROR: crc8arr1"); }
    if (crc16.crc != shs::tests::data.crc16arr1) { flags ^= 0b00000010;  out.pmln("ERROR: crc16arr1"); }
    if (crc32.crc != shs::tests::data.crc32arr1) { flags ^= 0b00000100;  out.pmln("ERROR: crc32arr1"); }
    
    
    crc8.clear();
    crc16.clear();
    crc32.clear();

    out.pvln((int)crc8.crcBuf(shs::tests::data.arr2, sizeof(shs::tests::data.arr2)));
    out.pvln(crc16.crcBuf(shs::tests::data.arr2, sizeof(shs::tests::data.arr2)));
    out.pvln(crc32.crcBuf(shs::tests::data.arr2, sizeof(shs::tests::data.arr2)));

    if (crc8.crc != shs::tests::data.crc8arr2) { flags ^= 0b00010000;  out.pmln("ERROR: crc8arr2"); }
    if (crc16.crc != shs::tests::data.crc16arr2) { flags ^= 0b00100000;  out.pmln("ERROR: crc16arr2"); }
    if (crc32.crc != shs::tests::data.crc32arr2) { flags ^= 0b01000000;  out.pmln("ERROR: crc32arr2"); }

    out.pvln("");
    out.pm("The test CRCTest::multiplatform is completed with code: ");
    out.pmln((int)flags);
    out.sep();

    return flags;
}

