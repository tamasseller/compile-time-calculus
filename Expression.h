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

template<class X, class Y, class Op>
class BinaryOperationExpression: public Operators<BinaryOperationExpression<X, Y, Op>> {
protected:
	template<class F> friend struct detail::derivate;
	typename X::Handle x;
	typename Y::Handle y;

public:
	static constexpr bool isConst = false;

	typedef const BinaryOperationExpression Handle;
		static constexpr auto precedence = Op::precedence;

		inline BinaryOperationExpression(const X &x, const Y &y): x(x), y(y) {}
		std::string print(unsigned int precedence=-1u) const {
			std::string ret;

			ret = Op::print(x, y, this->precedence);

			if(precedence < this->precedence)
				ret = "(" + ret + ")";


			return ret;
		}

		double value() const {return Op::calculate(this->x.value(), this->y.value());}
};




#endif /* EXPRESSION_H_ */
