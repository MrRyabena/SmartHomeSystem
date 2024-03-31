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
    out.sep();
    out.pn("u8v:  ");
    out.pvln(static_cast<int>(data.u8v));

    out.pn("i8v:  ");
    out.pvln(static_cast<int>(data.i8v));

    out.pn("u16v: ");
    out.pvln(data.u16v);

    out.pn("i16v: ");
    out.pvln(data.i16v);

    out.pn("u32v: ");
    out.pvln(data.u32v);

    out.pn("i32v: ");
    out.pvln(data.i32v);

    out.pn("u64v: ");
    out.pvln(data.u64v);

    out.pn("i64v: ");
    out.pvln(data.i64v);

    out.pn("fv:   ");
    out.pvln(data.fv);

    out.pn("dv:   ");
    out.pvln(data.dv);

    out.pn("cstr: ");
    for (auto i = 0; i < 12; i++)
    {
        out.pv(static_cast<int>(data.cstr[i]));
        out.pv(' ');
    }
    out.pvln("");
    out.sep();
}

void shs::tests::MultiDataTools::printBytesArray(shs::tests::MultiData &data)
{
    out.pn("size: ");
    out.pnln(sizeof(data));
    out.psln("{ ");
    uint8_t *ptr = (uint8_t*)(&data);
    for (auto i = 0; i < sizeof(data); i++)
    {
        out.pv((int)*(ptr++));
        out.pvln(',');
    }
    out.psln("};");
}
