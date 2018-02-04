#include <iostream>

#include "dynarray.h"

struct Foo{
    int x;
    double y;
    std::string z;
};

int main(int argc, char *argv[])
{
    std::cout << "Hello World!" << std::endl;

    dynarray<int> intArray(3);
    intArray[0] = 1;
    intArray.at(1) = 2;
    *(intArray.data() + 2) = 3;

    std::cout << intArray[0] << intArray.at(1) << intArray.back() << std::endl;

    dynarray<Foo> fooArray(5);
    auto& fooFront = fooArray.front();
    fooFront.x = 12;
    fooFront.y = 32.125;
    fooFront.z = "Alphabet Soup";

    auto fooIt = fooArray.begin();

    std::cout << fooIt->x << " " << fooIt->y << " " << fooIt->z << std::endl;

    dynarray<Foo> foo2Array(fooArray);
    dynarray<Foo> foo3Array;
    foo3Array = fooArray;
    std::cout << foo2Array.begin()->x << " " << foo3Array.front().y <<std::endl;

    return 0;
}
