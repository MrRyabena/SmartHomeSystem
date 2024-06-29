#include "../../source/SHSByteCollectorTest.h"

/*
  Testing shs::ByteCollector.
*/

/*
  Last update: v1.1.0
  Versions:
    v1.1.0 — created.
*/

int tests()
{
  shs::tests::ByteCollector_test test;
  int status{};

  // test.out.print_main_information(false);
  // test.out.print_secondary_information(false);
  // test.out.print_values(false);
  // test.out.print_notes(false);
  // test.out.print_separator(false);

  status |= test.write_read_test();
  status |= test.push_get_test();
  status |= test.reserve_test();
  status |= test.insert_test();
  status |= test.shrink_to_fit_test();

  status |= test.move_test();

  status |= test.multiplatform();
  status |= test.sequence();

  //test.myTest();
  return status;
}

int main()
{
  int status{ 0xff };

  try
  {
    status = tests();
  } catch (std::exception &exc)
  {
    std::cout << exc.what();
  } catch (...)
  {
    std::cout << "Undefined exception!" << std::endl;
  }
  return status;
}
