#include <shs_AStreamBuf.h>
#include <iostream>
#include <iterator>
#include <numeric>

static constexpr auto baud = 115200ul;

void setup()
{
    Serial.begin(baud);
    shs::rd_cio_to_ASerial();

    std::cout << "\n\nHello, world!" << '\n';
    std::cout << "Baud rate: " << baud << " baud\n\n";
    std::cout << "Please enter 2 numbers: ";
    std::cout.flush();
    
    int a{}, b{};
    
    if (std::cin >> a >> b) std::cout << a << " + " << b << " = " << a + b << std::endl;
    else
    {
        std::cerr << "\nError input!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }                    



    std::cout << "Enter 2 numbers again: ";
    std::cout.flush();

    std::istream_iterator<int> in{std::cin};
    std::ostream_iterator<int> out{std::cout};
    
    *out = *in++ + *in;
}

void loop() {}
