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
template<class F> struct derivate;
}

template<class Child>
struct ExpressionBase: public Operators<Child> {
	std::string print(unsigned int precedence=-1u) const
	{
		std::string ret = static_cast<const Child*>(this)->printValue();

		if(precedence < Child::precedence)
			ret = "(" + ret + ")";

		return ret;
	}
};

template<class X, class Y, class Op>
class BinaryOperationExpression: public ExpressionBase<BinaryOperationExpression<X, Y, Op>> {
protected:
	template<class F> friend struct detail::derivate;
	typename X::Handle x;
	typename Y::Handle y;

	friend class BinaryOperationExpression::ExpressionBase;
	std::string printValue() const {
		return Op::print(x, y, this->precedence);
	}

public:
	static constexpr bool isConst = false;

	typedef const BinaryOperationExpression Handle;
		static constexpr auto precedence = Op::precedence;

		inline BinaryOperationExpression(const X &x, const Y &y): x(x), y(y) {}


		double value() const {return Op::calculate(this->x.value(), this->y.value());}
};

template<class X, class Description>
class FunctionExpression: public ExpressionBase<FunctionExpression<X, Description>> {
protected:
	template<class F> friend struct detail::derivate;
	typedef Description desc;

	typename X::Handle x;

	friend class FunctionExpression::ExpressionBase;
	std::string printValue() const {
		return std::string(desc::name) + "(" + x.print(-1u) + ")";
	}

public:
	typedef const FunctionExpression Handle;
	static constexpr bool isConst = X::isConst;

	static constexpr auto precedence = 0;

	inline FunctionExpression(const X &x): x(x) {}

	double value() const {return desc::calculate(this->x.value());}
};


#endif /* EXPRESSION_H_ */
