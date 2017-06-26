/*
 * main.cpp
 *
 *      Author: tamas.seller
 */

#include <iostream>
#include <iomanip>

#include <string.h>
#include <type_traits>

#include "Derivate.h"

int main()
{
    Variable<'x'> x;
    Variable<'y'> y;

    x = 3;
    y = 4;

    auto v = Constant(1) / x;
    auto dv_dx = d(v) / d(x);

    std::cout << dv_dx.value() << std::endl;
    std::cout << dv_dx.print() << std::endl;
}
