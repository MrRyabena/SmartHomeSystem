#include "../../source/SHSByteCollectorTest.h"

/*
  Testing shs::ByteCollector.
*/

/*
  Last update: v1.1.0
  Versions:
    v1.1.0 — created.
*/

int main()
{
    shs::tests::ByteCollectorTest test;
    int status{};

    // test.out.print_main_information(false);
    // test.out.print_secondary_information(false);
    // test.out.print_values(false);
    // test.out.print_notes(false);
    // test.out.print_separator(false);


    status |= test.multiplatform();
    status |= test.sequence();

    return status;
}
