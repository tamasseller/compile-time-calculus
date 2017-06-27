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

	template<class X, class Y, class = typename std::enable_if<!X::isConst && !Y::isConst>::type>
	static inline constexpr std::string print(const X& x, const Y& y, int precedence) {
		return x.print(precedence) + "+" + y.print(precedence);
	}

	template<class X, class Y, class = typename std::enable_if<X::isConst>::type, class=void>
	static inline constexpr std::string print(const X& x, const Y& y, int precedence) {
		if(x.content == 0.0)
			return y.print(precedence);
		else
			return y.print(precedence) + "+" + x.print(precedence);
	}

	template<class X, class Y, class = typename std::enable_if<Y::isConst>::type, class=void, class=void>
	static inline constexpr std::string print(const X& x, const Y& y, int precedence) {
		if(y.content == 0.0)
			return x.print(precedence);
		else
			return x.print(precedence) + "+" + y.print(precedence);
	}
};

template<> struct BinaryOperation<BinaryOperationType::Sub>
{
	static constexpr auto precedence = 2u;

	static inline constexpr double calculate(double x, double  y) {
		return x - y;
	}

	template<class X, class Y, class = typename std::enable_if<!X::isConst && !Y::isConst>::type>
	static inline constexpr std::string print(const X& x, const Y& y, int precedence) {
		return x.print(precedence) + "-" + y.print(precedence);
	}

	template<class X, class Y, class = typename std::enable_if<X::isConst>::type, class=void>
	static inline constexpr std::string print(const X& x, const Y& y, int precedence) {
		if(x.content == 0.0)
			return "-" + y.print(precedence);
		else
			return x.print(precedence) + "-" + y.print(precedence);
	}

	template<class X, class Y, class = typename std::enable_if<Y::isConst>::type, class=void, class=void>
	static inline constexpr std::string print(const X& x, const Y& y, int precedence) {
		if(y.content == 0.0)
			return x.print(precedence);
		else
			return x.print(precedence) + "-" + y.print(precedence);
	}
};

template<> struct BinaryOperation<BinaryOperationType::Mul>
{
	static constexpr auto precedence = 1u;

	static inline constexpr double calculate(double x, double  y) {
		return x * y;
	}

	template<class X, class Y, class = typename std::enable_if<!X::isConst && !Y::isConst>::type>
	static inline constexpr std::string print(const X& x, const Y& y, int precedence) {
		return x.print(precedence) + "*" + y.print(precedence);
	}

	template<class X, class Y, class = typename std::enable_if<X::isConst>::type, class=void>
	static inline constexpr std::string print(const X& x, const Y& y, int precedence) {
		if(x.content == 0.0)
			return "0";
		else if(x.content == 1.0)
			return y.print(precedence);
		else
			return x.print(precedence) + "*" + y.print(precedence);
	}

	template<class X, class Y, class = typename std::enable_if<Y::isConst>::type, class=void, class=void>
	static inline constexpr std::string print(const X& x, const Y& y, int precedence) {
		if(y.content == 0.0)
			return "0";
		else if(y.content == 1.0)
			return x.print(precedence);
		else
			return y.print(precedence) + "*" + x.print(precedence);
	}
};

template<> struct BinaryOperation<BinaryOperationType::Div>
{
	static constexpr auto precedence = 0u;

	static inline constexpr double calculate(double x, double  y) {
		return x / y;
	}

	template<class X, class Y, class = typename std::enable_if<!X::isConst && !Y::isConst>::type>
	static inline constexpr std::string print(const X& x, const Y& y, int precedence) {
		return x.print(precedence) + "/" + y.print(precedence);
	}

	template<class X, class Y, class = typename std::enable_if<X::isConst>::type, class=void>
	static inline constexpr std::string print(const X& x, const Y& y, int precedence) {
		if(x.content == 0.0)
			return "0";
		else
			return x.print(precedence) + "/" + y.print(precedence);
	}

	template<class X, class Y, class = typename std::enable_if<Y::isConst>::type, class=void, class=void>
	static inline constexpr std::string print(const X& x, const Y& y, int precedence) {
		if(y.content == 1.0)
			return x.print(precedence);
		else
			return x.print(precedence) + "/" + y.print(precedence);
	}
};

template<> struct BinaryOperation<BinaryOperationType::Exp>
{
	static constexpr auto precedence = 0u;

	static inline constexpr double calculate(double x, double  y) {
		return pow(x, y);
	}

	template<class X, class Y>
	static inline constexpr std::string print(const X& x, const Y& y, int precedence) {
		return x.print(precedence) + "^" + y.print(precedence);
	}
};

#endif /* BINARYOPERATION_H_ */
