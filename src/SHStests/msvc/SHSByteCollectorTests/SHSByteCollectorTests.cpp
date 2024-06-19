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
  shs::tests::ByteCollector_test test;
  int status{};

  // test.out.print_main_information(false);
  // test.out.print_secondary_information(false);
  // test.out.print_values(false);
  // test.out.print_notes(false);
  // test.out.print_separator(false);

  status |= test.write_read_test();
  status |= test.add_get_test();
  status |= test.reserve_test();
  status |= test.insert_test();
  status |= test.shrink_to_fit_test();

  status |= test.multiplatform();
  status |= test.sequence();

  //test.myTest();

  return status;
}
