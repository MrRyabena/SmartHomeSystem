#include "SHSByteCollectorTest.h"
#include <iostream>

int shs::tests::ByteCollector_test::write_read_test()
{
    out.sep();
    out.pmln("Starting the test ByteCollector_test::read_write_test.");
    out.pn("quantity: ");
    out.pnln(quantity);

    shs::ByteCollector<uint8_t, uint16_t> bc;
    shs::Random<uint16_t> random;

    random.autoSeed();
    random.setRange(10, 100);


    uint16_t size = random.get();
    uint16_t *buf_w = new uint16_t[size]{};
    uint16_t *buf_r = new uint16_t[size]{};

    for (auto i = 0; i < size; i++) buf_w[i] = random.get();

    // bc.reserve(size * sizeof(buf_w[0]));

    bc.write((uint8_t *) buf_w, sizeof(buf_w[0]) * size);
    bc.read((uint8_t *) buf_r, sizeof(buf_w[0]) * size);

    assert(bc.size() == sizeof(buf_w[0]) * size);
    for (auto i = 0; i < size; i++)
    {
        assert(buf_r[i] == buf_w[i]);
    }

    delete [] buf_w;
    delete [] buf_r;

    out.pmln("The test ByteCollector_test::write_read_test is compleated with code 0.");
    out.sep();
    return 0;
}

int shs::tests::ByteCollector_test::push_get_test()
{
    out.sep();
    out.pmln("Starting the test ByteCollector_test::push_get_test.");
    out.pn("quantity: ");
    out.pnln(quantity);

    shs::ByteCollector<uint8_t, uint16_t> bc;
    shs::Random<uint16_t> random;

    random.autoSeed();
    random.setRange(10, 100);

    uint16_t size = random.get();
    uint16_t *buf_push_back = new uint16_t[size];
    uint16_t *buf_push_front = new uint16_t[size];

    for (auto i = 0; i < size; i++)
    {
        buf_push_back[i] = random.get();
        bc += buf_push_back[i];
    }
    for (auto i = 0; i < size; i++)
    {
        buf_push_front[i] = random.get();
        bc.push_front(buf_push_front[i]);
    }


    uint16_t value{};
    for (auto i = 0; i < size; i++)
    {
        bc.get(value);
        assert(buf_push_front[size - i - 1] == value);
    }
    for (auto i = 0; i < size; i++)
    {
        bc.get(value);
        assert(buf_push_back[i] == value);
    }

    delete [] buf_push_back;
    delete [] buf_push_front;

    out.pmln("The test ByteCollector_test::push_get_test is compleated with code 0.");
    out.sep();

    return 0;
}

int shs::tests::ByteCollector_test::reserve_test()
{
    out.sep();
    out.pmln("Starting the test ByteCollector_test::reserve_test.");

    shs::ByteCollector<uint8_t, uint16_t> bc;

    shs::Random<uint16_t> random;

    random.autoSeed();
    random.setRange(10, 10000);

    uint16_t size = random.get();
    uint16_t *buf_push_back = new uint16_t[size]{};
    uint16_t *buf_push_front = new uint16_t[size]{};

    bc.reserve(size * sizeof(buf_push_back[0]));
    assert(bc.capacity_back() == size * sizeof(buf_push_back[0]));
    assert(bc.capacity_front() == 0);
    assert(bc.getPositionBack() == 0);
    assert(bc.getPostitionFront() == 0);

    for (auto i = 0; i < size; i++)
    {
        buf_push_back[i] = random.get();
        bc += buf_push_back[i];
    }

    bc.reserve_front(size * sizeof(buf_push_front[0]));
    assert(bc.capacity_back() == 0);
    assert(bc.capacity_front() == size * sizeof(buf_push_front[0]));
    assert(bc.getPositionBack() == size * sizeof(buf_push_back[0]) * 2);
    assert(bc.getPostitionFront() == size * sizeof(buf_push_back[0]));
    for (auto i = 0; i < size; i++)
    {
        buf_push_front[i] = random.get();
        bc.push_front(buf_push_front[i]);
    }
    uint16_t value{};
    for (auto i = 0; i < size; i++)
    {
        bc.get(value);
        assert(buf_push_front[size - 1 - i] == value);
    }
    for (auto i = 0; i < size; i++)
    {
        bc.get(value);
        assert(buf_push_back[i] == value);
    }

    delete [] buf_push_back;
    delete [] buf_push_front;

    out.pmln("The test ByteCollector_test::reserve_test is compleated with code 0.");
    out.sep();

    return 0;
}

int shs::tests::ByteCollector_test::insert_test()
{
    out.sep();
    out.pmln("Starting the test ByteCollector_test::insert_test.");

    shs::ByteCollector<uint8_t, uint16_t> bc;
    shs::Random<uint8_t> random;
    random.autoSeed();
    uint8_t buf[200]{};
    uint8_t buf_ins[10]{};


    bc.reserve(200);
    for (auto i = 0; i < 200; i++)
    {
        buf[i] = random.get();
        bc += buf[i];
    }

    for (auto i = 0; i < 10; i++) buf_ins[i] = random.get();

    bc.insert(buf_ins, 10, 100);

    assert(bc.size() == 210);

    uint8_t value{};
    for (auto i = 0; i < 100; i++)
    {
        bc.get(value);
        assert(value == buf[i]);
    }
    for (auto i = 0; i < 10; i++)
    {
        bc.get(value);
        assert(value == buf_ins[i]);
    }
    for (auto i = 100; i < 200; i++)
    {
        bc.get(value);
        assert(value == buf[i]);
    }

    out.pmln("The test ByteCollector_test::insert_test is compleated with code 0.");
    out.sep();

    return 0;
}

int shs::tests::ByteCollector_test::shrink_to_fit_test()
{
    out.sep();
    out.pmln("Starting the test ByteCollector_test::shrink_to_fit_test.");

    shs::ByteCollector<uint8_t, uint16_t> bc;

    shs::Random<uint8_t> random;
    uint8_t buf[100];

    bc.reserve(200);
    bc.reserve_front(200);

    random.autoSeed();
    for (auto i = 0; i < 100; i++)
    {
        buf[i] = random.get();
        bc += buf[i];
    }

    assert(bc.capacity_back() == 100);
    assert(bc.capacity_front() == 200);

    bc.shrink_to_fit();

    assert(bc.capacity_back() == 0);
    assert(bc.capacity_front() == 0);

    for (auto i = 0; i < bc.size(); i++) assert(bc.begin()[i] == buf[i]);

    out.pmln("The test ByteCollector_test::shrink_to_fit_test is compleated with code 0.");
    out.sep();

    return 0;
}


int shs::tests::ByteCollector_test::move_test()
{
    out.sep();
    out.pmln("Starting the test ByteCollector_test::move_test.");

    shs::ByteCollector bc;
    bc.push_back("Hello, World!");

    auto new_bc = std::move(bc);

    assert(bc.size() == 0);
    assert(bc.begin() == nullptr);
    assert(new_bc.size() == 14);

    std::string str = (char *) &new_bc.begin();
    assert(str == "Hello, World!");

    out.pmln("The test ByteCollector_test::move_test is compleated with code 0.");
    out.sep();
    return 0;
}


int shs::tests::ByteCollector_test::iterator_test()
{
    out.sep();
    out.pmln("Starting the test ByteCollector_test::iterator_test.");

    shs::ByteCollector bc;
    constexpr char str [] = "Hello, World!";
    bc.push_back(str, 14);


    for (auto i = 0; auto x : bc) assert(x == str[i++]);

    out.pmln("The test ByteCollector_test::iterator_test is compleated with code 0.");
    out.sep();

    return 0;
}



int shs::tests::ByteCollector_test::multiplatform()
{
    out.sep();
    out.pmln("Starting the test ByteCollector_test::multiplatform.");
    out.pn("quantity: ");
    out.pnln(quantity);

    uint16_t flags{};

    shs::tests::MultiData md;
    shs::tests::MultiDataTools tools;

    shs::ByteCollector<> bc(10);

    tools.randomFill(md);

    bc.push_back(md.u8v);
    bc.push_front(md.i8v);
    bc.push_back(md.u16v, 2);
    bc.push_front(md.i16v, 2);
    bc.push_back(md.u32v);
    bc.push_front(md.i32v);
    bc.push_back(md.u64v);
    bc.push_front(md.i64v);
    bc.push_back(md.fv);
    bc.push_front(md.dv);
    // bc.push_back(md.cstr);

    shs::tests::MultiData md_n;
    bc.get(md_n.dv);
    bc.get(md_n.i64v);
    bc.get(md_n.i32v);
    bc.get(md_n.i16v, 2);
    bc.get(md_n.i8v);

    bc.get(md_n.u8v);
    bc.get(md_n.u16v, 2);
    bc.get(md_n.u32v);
    bc.get(md_n.u64v);
    bc.get(md_n.fv);

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

    out.pm("The test ByteCollector_test::multiplatform is completed with code: ");
    out.pmln(flags);


    //std::cout << std::hex;
    //uint8_t *ptr = (uint8_t *) &md;
    //for (auto i = 0; i < sizeof(md); i++) std::cout << (int) (*ptr++) << ' ';
    //std::cout << std::endl;

    //ptr = bc.begin();
    //for (auto i = 0; i < bc.size(); i++)std::cout << (int) (*ptr++) << ' ';
    //std::cout << std::endl;
    out.sep();



    return flags;
}


int shs::tests::ByteCollector_test::sequence()
{
    out.sep();
    out.pmln("Starting the test ByteCollector_test::sequence.");
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
        bc.push_front(r--, 1);
        bc.push_back(l++, 1);
    }

    // if (bc.begin() + bc.getPositionRead() != bc.begin()) out.pmln("ERROR! bc.readPtr != bc.begin()");

    unsigned int value{};
    for (auto i = 0; i < bc.size(); i++)
    {
        bc.get(value, 1);
        out.pvln(value);
         //doutln((int)bc.begin()[i]);
    }
    out.pvln("");
    out.pmln("The test ByteCollector_test::sequence is completed with code: ");
    out.sep();
    return 0;
}


void shs::tests::ByteCollector_test::myTest()
{
    shs::ByteCollector bc;

    uint8_t u8 = 10;
    uint16_t u16 = 10;
    uint32_t u32 = 1111;
    int64_t i64 = -1023;

    std::cout << (int) u8 << ' ' << u16 << ' ' << u32 << ' ' << i64 << std::endl;

    bc.push_back(u8);
    bc.push_back(u16, 1);
    bc.push_front(u32, 2);
    bc.push_back(i64, 2);
    bc += 100;

    bc.get(u32, 2);
    bc.get(u8);
    bc.get(u16, 1);
    bc.get(i64, 2);

    int hundred{};
    bc.get(hundred);

    std::cout << (int) u8 << ' ' << u16 << ' ' << u32 << ' ' << i64 << ' ' << hundred << std::endl;
}
