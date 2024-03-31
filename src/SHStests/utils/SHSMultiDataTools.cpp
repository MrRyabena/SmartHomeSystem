#include "SHSMultiDataTools.h"

void shs::tests::MultiDataTools::randomFill(shs::tests::MultiData &data)
{
    shs::Random<uint8_t> rnd(0, 255);
    rnd.autoSeed();

    uint8_t *ptr = (uint8_t *)&data;
    for (auto i = 0; i < sizeof(data); i++)
        *(ptr++) = rnd.get();
}

void shs::tests::MultiDataTools::print(shs::tests::MultiData &data)
{
    dsep();
    dout("u8v:  ");
    doutln(static_cast<int>(data.u8v));

    dout("i8v:  ");
    doutln(static_cast<int>(data.i8v));

    dout("u16v: ");
    doutln(data.u16v);

    dout("i16v: ");
    doutln(data.i16v);

    dout("u32v: ");
    doutln(data.u32v);

    dout("i32v: ");
    doutln(data.i32v);

    dout("u64v: ");
    doutln(data.u64v);

    dout("i64v: ");
    doutln(data.i64v);

    // dout("fv:   ");
    // doutln(data.fv);

    // dout("dv:   ");
    // doutln(data.dv);

    dout("cstr: ");
    for (auto i = 0; i < 12; i++)
    {
        dout(static_cast<int>(data.cstr[i]));
        dout(' ');
    }
    doutln("");
    dsep();
}

void shs::tests::MultiDataTools::printBytesArray(shs::tests::MultiData &data)
{
    dout("size: ");
    doutln(sizeof(data));
    doutln("{ ");
    uint8_t *ptr = (uint8_t*)(&data);
    for (auto i = 0; i < sizeof(data); i++)
    {
        dout((int)*(ptr++));
        doutln(',');
    }
    doutln("};");
}
