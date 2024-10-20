#include "SHSFSTest.h"
#include <cassert>

int shs::tests::FSTest::simpleFile()
{
    int status{};
    out.sep();
    out.pmln("Starting the test FSTest::simpleFile.");
    out.psln("");

    static constexpr auto len = 36;
    static constexpr auto len2 = 15;
    static constexpr auto len3 = 69;
    static constexpr char str [] = "Testing data for FSTest::simpleFile";
    static constexpr char str2 [] = "\nAppended data";
    static constexpr char str3 [] = "Except \"\", all data will be replaced.";
    static constexpr char fname [] = "test_file.shsf";

    shs::FS fs;
    bool create = true; //!fs.exists(fname);
    char buf[100]{};
    out.pn("File exists: ");
    out.pnln(fs.exists(fname));
    out.pn("File create: ");
    out.pnln(create);
    out.psln("");

    shs::File file = fs.open(fname, shs::fs::File_Write, create);
    create = false;

    if (!file) { status |= 0b1; out.pmln("ERROR! The file is not open: 0b1"); }
   // if (file.fstr.fail()) { status |= 0b100; out.pmln("ERROR! The file is not open: 0b100"); }
    file.write((uint8_t*) str, len);
    //file.flush();
    // file.fstr.sync();
    // if (file.fstr.fail()) { status |= 0b100; out.pmln("ERROR! The file is not open: 0b100"); }

     //file.close();
     //return 0;

    file.seek(0);
   // if (file.fstr.fail()) { status |= 0b100; out.pmln("ERROR! The file is not open: 0b100"); }
    file.read((uint8_t*) buf, len);
    for (auto i = 0; i < len; i++) out.pv(buf[i]);
    out.pvln("\n");
    file.close();
    if (file) { status |= 0b10; out.pmln("ERROR! The file is not closed: 0b10"); }

    file = fs.open(fname, shs::fs::File_Append);
    if (!file) { status |= 0b100; out.pmln("ERROR! The file is not open: 0b100"); }
    file.write((uint8_t*) str2, len2);
    file.close();
    if (file) { status |= 0b1000; out.pmln("ERROR! The file is not closed: 0b1000"); }

    file = fs.open(fname, shs::fs::File_Read);

    logFile(file);
    file.close();
    out.pvln("");


    file = fs.open(fname, shs::fs::File_Write);
    file.seek(0);
    file.write((uint8_t*) str3, 8);
    file.seek(4, shs::fs::Seek_Cur);
    file.write((uint8_t*) &str3[8], len3 - 8);
    file.close();
    if (file) { status |= 0b10000; out.pmln("ERROR! file 0b10000"); }


    file = fs.open(fname, shs::fs::File_Read);
    file.seek(0);
    logFile(file);
    file.close();
    out.pvln("");

    out.psln("");
    out.pm("The test FSTest::simpleFile is completed with code: ");
    out.pm(status);
    out.pmln('.');
    out.sep();
    return status;
}

int shs::tests::FSTest::simpleSHSF()
{
    int status{};
    out.sep();
    out.pmln("Starting the test FSTest::simpleSHSF.");
    out.psln("");
    shs::FS fs;
    shs::SHSF file = fs.open("test.shsf", shs::fs::File_Write, true);

    file.header_data.type = shs::fs::SHSF_type::text;
    file.header_data.CRCdegree = 5;
    file.writeHeader();

    static constexpr char comment [] = "Testing the class shs::SHSF in this file.";
    file.writeInfoComment(comment, strlen(comment));
    file.writeInfoSize();

    file.seekToBeginning();
    static constexpr char str [] = "Testing the data writing protocol class with various data types and sizes to ensure proper file writing functionality. This test includes writing strings, integers, and arrays to the file and verifying the data integrity upon reading. Generated by a neural network.";

    out.pn("Position: "); out.pnln(file.position());
    out.pn("Free    : "); out.pnln(file.getFree());
    out.pn("file.add() return: "); out.pnln(file.add((uint8_t*) str, strlen(str)));
    file.close();


    file = fs.open("test.shsf", shs::fs::File_Read);
    file.header_data = {};
    file.readHeader();

    out.pvln("HEADER:");
    out.pv("  version  : ");
    out.pvln((int) file.header_data.version);
    out.pv("  type     : ");
    out.pvln((int) file.header_data.type);
    out.pv("  CRCdegree: ");
    out.pvln((int) file.header_data.CRCdegree);
    out.pvln("");


    char* buf{};
    uint16_t cm_size = file.readInfoComment(buf);
    if (cm_size != strlen(comment)) { status |= 0b1; out.pmln("ERROR! comment sizes are not match. 0b1"); }
    out.pvln("INFO:");
    out.pv("  info-size   : "); out.pvln(file.readInfoSize());
    out.pv("  comment-size: "); out.pvln(file.readInfoCommentSize());
    out.pv("  comment     : ");
    for (auto i = 0; i < cm_size; i++) out.pv(buf[i]);
    delete [] buf;
    out.pvln('\n');


    file.seekToBeginning();
    size_t size = strlen(str);
    char* text = new char[size];
    size_t r_size = file.get((uint8_t*) text, size);
    if (r_size != size) { status |= 0b10; out.pmln("ERROR! text sizes are not match. 0b10"); }

    out.pvln("DATA:");
    for (auto i = 0; i < size; i++) out.pv(text[i]);
    out.pvln('\n');
    delete [] text;
    file.close();

    out.psln("");
    out.pm("The test FSTest::simpleSHSF is completed with code: ");
    out.pm(status);
    out.pmln('.');
    out.sep();

    return status;
}

void shs::tests::FSTest::logFile(shs::File& file)
{
    for (auto i = 0; i < file.size(); i++)
        out.pv(file.read());
    out.pvln("");
}
