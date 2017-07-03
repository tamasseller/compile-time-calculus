/*
 * Expression.h
 *
 *  Created on: 2017.06.26.
 *      Author: tooma
 */

#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include "BinaryOperation.h"

template<class Child> class Operators;

namespace detail {
template<class T> struct derivate;
template<class T> struct ContentPrinter;
}

template<class X, class Y, class Op>
class BinaryOperationExpression: public Operators<BinaryOperationExpression<X, Y, Op>> {
protected:
	template<class T> friend struct detail::derivate;
	template<class T> friend struct detail::ContentPrinter;
	typename X::Handle x;
	typename Y::Handle y;

public:
	typedef const BinaryOperationExpression Handle;
	static constexpr auto precedence = Op::precedence;

	inline BinaryOperationExpression(const X &x, const Y &y): x(x), y(y) {}

	__attribute__((always_inline))
	inline double value() const {return Op::calculate(this->x.value(), this->y.value());}
};

template<class X, class Description>
class FunctionExpression: public Operators<FunctionExpression<X, Description>> {
protected:
	template<class F> friend struct detail::derivate;
	template<class T> friend struct detail::ContentPrinter;
	typedef Description desc;

	typename X::Handle x;

public:
	typedef const FunctionExpression Handle;
	static constexpr auto precedence = 0;

	inline FunctionExpression(const X &x): x(x) {}

	__attribute__((always_inline))
	inline double value() const {return desc::calculate(this->x.value());}
};


#endif /* EXPRESSION_H_ */
