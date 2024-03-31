#include "SHSByteCollectorTest.h"

int shs::tests::ByteCollectorTest::multiplatform()
{
    out.sep();
    out.pmln("Starting the test ByteCollectorTest::multiplatform.");
    out.pn("quantity: ");
    out.pnln(quantity);

    uint16_t flags{};

    shs::tests::MultiData md;
    shs::tests::MultiDataTools tools;

    shs::ByteCollector bc(10);
    // bc.reserveBefore(2);
    // bc.reserve(2);

    tools.randomFill(md);

    bc.add(md.u8v);
    bc.addBefore(md.i8v);
    bc.add(md.u16v, 2);
    bc.addBefore(md.i16v, 2);
    bc.add(md.u32v);
    bc.addBefore(md.i32v);
    bc.add(md.u64v);
    bc.addBefore(md.i64v);
    bc.add(md.fv, 2);
    bc.addBefore(md.dv, 4);
    // bc.add(md.cstr);

    shs::tests::MultiData md_n;
    bc.get(md_n.dv, 4);
    bc.get(md_n.i64v);
    bc.get(md_n.i32v);
    bc.get(md_n.i16v, 2);
    bc.get(md_n.i8v);
    
    bc.get(md_n.u8v);
    bc.get(md_n.u16v, 2);
    bc.get(md_n.u32v);
    bc.get(md_n.u64v);
    bc.get(md_n.fv, 4);

    if (md.u8v != md_n.u8v)
    {
        out.pmln("ERROR! u8v != target.");
        flags ^= 0b0000000000000001;
    }
    if (md.i8v != md_n.i8v)
    {
        out.pmln("ERROR! i8v != target.");
        flags ^= 0b0000000000000010;
    }
    if (md.u32v != md_n.u32v)
    {
        out.pmln("ERROR! u32v != target.");
        flags ^= 0b0000000000000100;
    }
    if (md.i32v != md_n.i32v)
    {
        out.pmln("ERROR! i32v != target.");
        flags ^= 0b0000000000001000;
    }
    if (md.u64v != md_n.u64v)
    {
        out.pmln("ERROR! u64v != target.");
        flags ^= 0b0000000000010000;
    }
    if (md.i64v != md_n.i64v)
    {
        out.pmln("ERROR! i64v != target.");
        flags ^= 0b0000000000010000;
    }

    out.pvln("fv: target, real");
    out.pvln(md.fv);
    out.pvln(md_n.fv);

    out.pvln("dv: target, real");
    out.pvln(md.dv);
    out.pvln(md_n.dv);
    
    out.pm("The test ByteCollectorTest::multiplatform is completed with code: ");
    out.pmln(flags);
    out.sep();

    return flags;
}


int shs::tests::ByteCollectorTest::sequence()
{
    out.sep();
    out.pmln("Starting the test ByteCollectorTest::sequence.");
    out.pn("quantity: ");
    out.pnln(quantity);

    if (quantity > 255)
    {
        out.pnln("NOTE: quantity > 255!\nnew quantity = 10");
        quantity = 10;
    }

    shs::ByteCollector bc;

    int r = quantity / 2;
    int l = r + 1;
    for (auto i = 0; i < quantity / 2; i++)
    {
        bc.addBefore(r--, 1);
        bc.add(l++, 1);
    }

    if (bc.readPtr != bc.buf) out.pmln("ERROR! bc.readPtr != bc.buf");
   
    unsigned int value{};
    for (auto i = 0; i < bc.size(); i++)
    {
       bc.get(value, 1);
       out.pvln(value);    
        //doutln((int)bc.buf[i]);
    }
    out.pvln("");
    out.pmln("The test ByteCollectorTest::sequence is completed with code: ");
    out.sep();
    return 0;
}
