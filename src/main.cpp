#include <iostream>
#include "univalue.h"


int main() {
    char buf[] = "___[1,2,3]___";
    UniValue val;
    std::cout << "Hello, World! " << val.read(buf + 3, 7) << std::endl;
    return 0;
}
