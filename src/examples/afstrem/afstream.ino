
#include <string>

#include <LittleFS.h>

#include <shs_AFStream.h>
#include <shs_debug.h>


void setup()
{
    dinit();

    if (!LittleFS.begin())
    {
        doutln("FS error! Formating...");
        LittleFS.format();
    }
    else doutln("FS began");

    shs::AFStream::default_fs_ptr = &LittleFS;

    auto file = shs::AFSream("/testFile.txt");

    file << "Hello, world!";
    file.close();

    file = shs::AFStream("/testFile.txt", std::ios_base::openmode::in);

    std::string s;
    file >> s;

    doutln(s.c_str());

}

void loop() {}
