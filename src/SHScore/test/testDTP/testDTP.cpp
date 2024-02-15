#include <iostream>
#include <stdint.h>
#include "../../SHSdtp.h"
#include "../../SHSByteCollector.h"

int main()
{
    shs::ByteCollector col(12);
    col.add("Hello, user!");
    
    shs::DTP dtp(104);
    dtp.packDTP(&col, 127);
    
    return 0;
}