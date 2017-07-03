/*
 * Scalar.h
 *
 *  Created on: 2017.06.26.
 *      Author: tooma
 */

#ifndef SCALAR_H_
#define SCALAR_H_

#include "Expression.h"

#include <string>

template<char n>
class Variable;
class Constant;

template<class Child>
struct Operators {
	inline BinaryOperationExpression<Constant, Child, BinaryOperation<BinaryOperationType::Sub>> operator -() const {
		return BinaryOperationExpression<Constant, Child, BinaryOperation<BinaryOperationType::Sub>>(0, *static_cast<const Child*>(this));
	}

	template<class Other>
	inline BinaryOperationExpression<Child, Other, BinaryOperation<BinaryOperationType::Add>> operator +(const Other& other) const {
		return BinaryOperationExpression<Child, Other, BinaryOperation<BinaryOperationType::Add>>(*static_cast<const Child*>(this), other);
	}

	template<class Other>
	inline BinaryOperationExpression<Child, Other, BinaryOperation<BinaryOperationType::Sub>> operator -(const Other& other) const {
		return BinaryOperationExpression<Child, Other, BinaryOperation<BinaryOperationType::Sub>>(*static_cast<const Child*>(this), other);
	}

	template<class Other>
	inline BinaryOperationExpression<Child, Other, BinaryOperation<BinaryOperationType::Mul>> operator *(const Other& other) const {
		return BinaryOperationExpression<Child, Other, BinaryOperation<BinaryOperationType::Mul>>(*static_cast<const Child*>(this), other);
	}

	template<class Other>
	inline BinaryOperationExpression<Child, Other, BinaryOperation<BinaryOperationType::Div>> operator /(const Other& other) const {
		return BinaryOperationExpression<Child, Other, BinaryOperation<BinaryOperationType::Div>>(*static_cast<const Child*>(this), other);
	}

	template<class Other>
	inline BinaryOperationExpression<Child, Other, BinaryOperation<BinaryOperationType::Exp>> operator ^(const Other& other) const {
		return BinaryOperationExpression<Child, Other, BinaryOperation<BinaryOperationType::Exp>>(*static_cast<const Child*>(this), other);
	}

	inline BinaryOperationExpression<Child, Constant, BinaryOperation<BinaryOperationType::Add>> operator +(const double& other) const {
		return BinaryOperationExpression<Child, Constant, BinaryOperation<BinaryOperationType::Add>>(*static_cast<const Child*>(this), other);
	}

	inline BinaryOperationExpression<Child, Constant, BinaryOperation<BinaryOperationType::Sub>> operator -(const double& other) const {
		return BinaryOperationExpression<Child, Constant, BinaryOperation<BinaryOperationType::Sub>>(*static_cast<const Child*>(this), other);
	}

	inline BinaryOperationExpression<Child, Constant, BinaryOperation<BinaryOperationType::Mul>> operator *(const double& other) const {
		return BinaryOperationExpression<Child, Constant, BinaryOperation<BinaryOperationType::Mul>>(*static_cast<const Child*>(this), other);
	}

	inline BinaryOperationExpression<Child, Constant, BinaryOperation<BinaryOperationType::Div>> operator /(const double& other) const {
		return BinaryOperationExpression<Child, Constant, BinaryOperation<BinaryOperationType::Div>>(*static_cast<const Child*>(this), other);
	}

	inline BinaryOperationExpression<Child, Constant, BinaryOperation<BinaryOperationType::Exp>> operator ^(const double& other) const {
		return BinaryOperationExpression<Child, Constant, BinaryOperation<BinaryOperationType::Exp>>(*static_cast<const Child*>(this), other);
	}
};

class Constant: public Operators<Constant> {
	template<BinaryOperationType> friend struct BinaryOperation;
	const double content;
public:
	static constexpr bool isConst = true;
	static constexpr auto precedence = 0u;
	typedef const Constant Handle;

	__attribute__((always_inline))
	inline double value() const {return content;}
	inline Constant(double content): content(content){};

	inline std::string print(unsigned int=0) const {return std::to_string(content);}

	inline Constant operator +(const Constant& other) const {
		return content + other.content;
	}

	inline Constant operator -(const Constant& other) const {
		return content - other.content;
	}

	inline Constant operator *(const Constant& other) const {
		return content * other.content;
	}

	inline Constant operator /(const Constant& other) const {
		return content / other.content;
	}

	inline Constant operator +(const double& other) const {
		return content + other;
	}

	inline Constant operator -(const double& other) const {
		return content - other;
	}

	inline Constant operator *(const double& other) const {
		return content * other;
	}

	inline Constant operator /(const double& other) const {
		return content / other;
	}

	using Operators<Constant>::operator+;
	using Operators<Constant>::operator-;
	using Operators<Constant>::operator/;
	using Operators<Constant>::operator*;
};

template<char n>
class Variable: public Operators<Variable<n>> {
	double content;
public:
	static constexpr bool isConst = false;
	static constexpr auto precedence = 0u;
	typedef const Variable& Handle;

	__attribute__((always_inline))
	inline double value() const {return content;}

	inline Variable& operator =(const double& v) {
		content = v;
		return *this;
	}

	inline std::string print(unsigned int=0) const {return std::string(1, n);}
};

#endif /* SCALAR_H_ */
