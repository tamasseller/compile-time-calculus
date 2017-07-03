/*
 * Print.h
 *
 *  Created on: 2017.07.03.
 *      Author: tooma
 */

#ifndef PRINT_H_
#define PRINT_H_

#include "Expression.h"

#include <string>
#include <sstream>

/*
 *
 * inline std::string printValue() const {
	return std::string(desc::name) + "(" + x.print(-1u) + ")";
}
 *
 */

namespace detail {

template<class T>
inline std::string printInternal(const T& expr, unsigned int precedence=-1u);

template<class T>
struct ContentPrinter {
	static inline std::string print(const T &constant) {
		std::stringstream ss;
		ss << constant.value();
		return ss.str();
	}
};

template<BinaryOperationType Op> struct OpChars;
template<> struct OpChars<BinaryOperationType::Add> {static constexpr char c = '+';};
template<> struct OpChars<BinaryOperationType::Sub> {static constexpr char c = '-';};
template<> struct OpChars<BinaryOperationType::Mul> {static constexpr char c = '*';};
template<> struct OpChars<BinaryOperationType::Div> {static constexpr char c = '/';};
template<> struct OpChars<BinaryOperationType::Exp> {static constexpr char c = '^';};

template<class X, class Y, BinaryOperationType Op>
struct ContentPrinter<BinaryOperationExpression<X, Y, BinaryOperation<Op>>> {
	static inline std::string print(const BinaryOperationExpression<X, Y, BinaryOperation<Op>>& expr) {
		return detail::printInternal(expr.x, BinaryOperation<Op>::precedence) + OpChars<Op>::c + detail::printInternal(expr.y, BinaryOperation<Op>::precedence);
	}
};

template<class Y>
struct ContentPrinter<BinaryOperationExpression<Zero, Y, BinaryOperation<BinaryOperationType::Sub>>> {
	static inline std::string print(const BinaryOperationExpression<Zero, Y, BinaryOperation<BinaryOperationType::Sub>>& expr) {
		return "-" + detail::printInternal(expr.y, BinaryOperation<BinaryOperationType::Sub>::precedence);
	}
};

template<class X, class Description>
struct ContentPrinter<FunctionExpression<X, Description>> {
	static inline std::string print(const FunctionExpression<X, Description>& expr) {
		return std::string(Description::name) + "(" + detail::printInternal(expr.x, 0) + ")";
	}
};

template<char c>
struct ContentPrinter<Variable<c>> {
	static inline std::string print(const Variable<c> &) {
		return std::string(1, c);
	}
};

template<class T>
inline std::string printInternal(const T& expr, unsigned int precedence)
{
	std::string ret = ContentPrinter<T>::print(expr);

	if(precedence < expr.precedence)
		ret = "(" + ret + ")";

	return ret;
}

}

template<class T>
inline std::string print(const T& expr) {
	return detail::printInternal(expr);
}

#endif /* PRINT_H_ */
