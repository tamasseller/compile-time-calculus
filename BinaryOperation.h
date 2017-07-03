/*
 * BinaryOperation.h
 *
 *  Created on: 2017.06.26.
 *      Author: tooma
 */

#ifndef BINARYOPERATION_H_
#define BINARYOPERATION_H_

#include "math.h"

enum class BinaryOperationType
{
	Add, Sub, Mul, Div, Exp
};

template<BinaryOperationType op> struct BinaryOperation;

template<> struct BinaryOperation<BinaryOperationType::Add>
{
	static constexpr auto precedence = 2u;

	static inline constexpr double calculate(double x, double  y) {
		return x + y;
	}
};

template<> struct BinaryOperation<BinaryOperationType::Sub>
{
	static constexpr auto precedence = 2u;

	static inline constexpr double calculate(double x, double  y) {
		return x - y;
	}
};

template<> struct BinaryOperation<BinaryOperationType::Mul>
{
	static constexpr auto precedence = 1u;

	static inline constexpr double calculate(double x, double  y) {
		return x * y;
	}
};

template<> struct BinaryOperation<BinaryOperationType::Div>
{
	static constexpr auto precedence = 0u;

	static inline constexpr double calculate(double x, double  y) {
		return x / y;
	}
};

template<> struct BinaryOperation<BinaryOperationType::Exp>
{
	static constexpr auto precedence = 0u;

	static inline constexpr double calculate(double x, double  y) {
		return pow(x, y);
	}
};

#endif /* BINARYOPERATION_H_ */
