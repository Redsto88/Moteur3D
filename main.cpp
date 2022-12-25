#include "vector.hpp"
#include <iostream>


int main(int argc, char const *argv[])
{
    Vector v1(1, 2, 3);
    Vector v2(4, 5, 6);
    v1 += v2;
    std::cout << v1.getX() << std::endl;
    return 0;
}
