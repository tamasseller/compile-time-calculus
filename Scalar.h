/*
 * Scalar.h
 *
 *  Created on: 2017.06.26.
 *      Author: tooma
 */

#ifndef SCALAR_H_
#define SCALAR_H_

#include "Expression.h"

template<char n>
class Variable;
class Constant;

template<class Child>
struct Operators {
	template<class Other>
	BinaryOperationExpression<Child, Other, BinaryOperation<BinaryOperationType::Add>> operator +(const Other& other) const {
		return BinaryOperationExpression<Child, Other, BinaryOperation<BinaryOperationType::Add>>(*static_cast<const Child*>(this), other);
	}

	template<class Other>
	BinaryOperationExpression<Child, Other, BinaryOperation<BinaryOperationType::Sub>> operator -(const Other& other) const {
		return BinaryOperationExpression<Child, Other, BinaryOperation<BinaryOperationType::Sub>>(*static_cast<const Child*>(this), other);
	}

	template<class Other>
	BinaryOperationExpression<Child, Other, BinaryOperation<BinaryOperationType::Mul>> operator *(const Other& other) const {
		return BinaryOperationExpression<Child, Other, BinaryOperation<BinaryOperationType::Mul>>(*static_cast<const Child*>(this), other);
	}

	template<class Other>
	BinaryOperationExpression<Child, Other, BinaryOperation<BinaryOperationType::Div>> operator /(const Other& other) const {
		return BinaryOperationExpression<Child, Other, BinaryOperation<BinaryOperationType::Div>>(*static_cast<const Child*>(this), other);
	}

	BinaryOperationExpression<Child, Constant, BinaryOperation<BinaryOperationType::Add>> operator +(const double& other) const {
		return BinaryOperationExpression<Child, Constant, BinaryOperation<BinaryOperationType::Add>>(*static_cast<const Child*>(this), other);
	}

	BinaryOperationExpression<Child, Constant, BinaryOperation<BinaryOperationType::Sub>> operator -(const double& other) const {
		return BinaryOperationExpression<Child, Constant, BinaryOperation<BinaryOperationType::Sub>>(*static_cast<const Child*>(this), other);
	}

	BinaryOperationExpression<Child, Constant, BinaryOperation<BinaryOperationType::Mul>> operator *(const double& other) const {
		return BinaryOperationExpression<Child, Constant, BinaryOperation<BinaryOperationType::Mul>>(*static_cast<const Child*>(this), other);
	}

	BinaryOperationExpression<Child, Constant, BinaryOperation<BinaryOperationType::Div>> operator /(const double& other) const {
		return BinaryOperationExpression<Child, Constant, BinaryOperation<BinaryOperationType::Div>>(*static_cast<const Child*>(this), other);
	}
};

class Constant: public Operators<Constant> {
	template<BinaryOperationType> friend struct BinaryOperation;
	const double content;
public:
	static constexpr bool isConst = true;
	static constexpr auto precedence = 0u;
	typedef const Constant Handle;

	double value() const {return content;}
	Constant(double content): content(content){};

	std::string print(unsigned int=0) const {return std::to_string(content);}

	Constant operator +(const Constant& other) const {
		return content + other.content;
	}

	Constant operator -(const Constant& other) const {
		return content - other.content;
	}

	Constant operator *(const Constant& other) const {
		return content * other.content;
	}

	Constant operator /(const Constant& other) const {
		return content / other.content;
	}

	Constant operator +(const double& other) const {
		return content + other;
	}

	Constant operator -(const double& other) const {
		return content - other;
	}

	Constant operator *(const double& other) const {
		return content * other;
	}

	Constant operator /(const double& other) const {
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

	double value() const {return content;}

	inline Variable& operator =(const double& v) {
		content = v;
		return *this;
	}

	std::string print(unsigned int=0) const {return std::string(1, n);}
};

#endif /* SCALAR_H_ */
