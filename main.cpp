#include <iostream>

#include "dynarray.h"

int main(int argc, char *argv[])
{
    std::cout << "Hello World!" << std::endl;

    dynarray<int> intArray(3);
    intArray[0] = 1;
    intArray.at(1) = 2;
    *(intArray.data() + 2) = 3;

    std::cout << intArray[0] << intArray.at(1) << intArray.back() << std::endl;

    return 0;
}
