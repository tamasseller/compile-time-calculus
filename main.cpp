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
#include "Function.h"

int main()
{
    Variable<'x'> x;
    Variable<'y'> y;
    Constant e(exp(1));

    x = 10;
    y = 4;

    auto v = sine(Constant(1.0)/x);

    std::cout << v.value() << std::endl;
    std::cout << v.print() << std::endl;

    auto dv_dx = d(v) / d(x);

    std::cout << dv_dx.value() << std::endl;
    std::cout << dv_dx.print() << std::endl;

    auto dv_dx_dx = d(dv_dx) / d(x);

	std::cout << dv_dx_dx.value() << std::endl;
    std::cout << dv_dx_dx.print() << std::endl;
}
