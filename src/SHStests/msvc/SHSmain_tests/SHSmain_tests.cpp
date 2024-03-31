#include "../../source/SHSByteCollectorTest.h"
#include "../../source/SHSCRCTest.h"
#include "../../source/SHSRandomTest.h"
#include "../../source/SHSprinter.h"

int main() {
  shs::tests::Printer out;
  out.pmln("\n========== STARTING THE MAIN TESTS ==========");
 
  int status{};
  shs::tests::ByteCollectorTest bc_test;
  shs::tests::CRCTest crc_test;
  shs::tests::RandomTest rnd_test;

  bc_test.out.flags = 0;
  bc_test.out.print_main_information(true);
  bc_test.out.print_separator(true);
  bc_test.quantity = 1'000'000;
  
  crc_test.out.flags = bc_test.out.flags;
  rnd_test.out.flags = bc_test.out.flags;

  crc_test.quantity = bc_test.quantity;
  rnd_test.quantity = bc_test.quantity;

  status |= bc_test.multiplatform();
  status |= crc_test.multiplatform();
  status |= rnd_test.correctRange<int>(-65000, 65000);
  status |= rnd_test.correctRange<double>(-1.414, 3.1415926535);
  
  out.pmln("========== THE MAIN TESTS IS COMPLETED ==========\n");
  
  return status;
}