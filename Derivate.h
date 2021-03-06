/*
 * Derivate.h
 *
 *  Created on: 2017.06.26.
 *      Author: tooma
 */

#ifndef DERIVATE_H_
#define DERIVATE_H_

#include "Scalar.h"

namespace detail {

template<class F> struct derivate {};

template<char n> struct derivate<Variable<n>> {
	template<char o>
	static inline Zero d(const Variable<n>&, const Variable<o>&) {
		return Zero();
	}

	static inline One d(const Variable<n>&, const Variable<n>&) {
		return One();
	}
};

template<> struct derivate<Constant> {
	template<char n>
	static inline Zero d(const Constant& f, const Variable<n>& x) {
		return Zero();
	}
};

template<class X, class Y>
struct derivate<BinaryOperationExpression<X, Y, BinaryOperation<BinaryOperationType::Add>>> {
	template<char n>
	static inline auto d(const BinaryOperationExpression<X, Y, BinaryOperation<BinaryOperationType::Add>>& f, const Variable<n>& x) ->
			typename std::decay<decltype(derivate<X>::d(f.x, x) + derivate<Y>::d(f.y, x))>::type {
		return derivate<X>::d(f.x, x) + derivate<Y>::d(f.y, x);
	}
};

template<class X, class Y>
struct derivate<BinaryOperationExpression<X, Y, BinaryOperation<BinaryOperationType::Sub>>> {
	template<char n>
	static inline auto d(const BinaryOperationExpression<X, Y, BinaryOperation<BinaryOperationType::Sub>>& f, const Variable<n>& x) ->
			typename std::decay<decltype(derivate<X>::d(f.x, x) - derivate<Y>::d(f.y, x))>::type {
		return derivate<X>::d(f.x, x) - derivate<Y>::d(f.y, x);
	}
};

template<class X, class Y>
struct derivate<BinaryOperationExpression<X, Y, BinaryOperation<BinaryOperationType::Mul>>> {
	template<char n>
	static inline auto d(const BinaryOperationExpression<X, Y, BinaryOperation<BinaryOperationType::Mul>>& f, const Variable<n>& x) ->
			typename std::decay<decltype(f.y * derivate<X>::d(f.x, x) + f.x * derivate<Y>::d(f.y, x))>::type {
		return f.y * derivate<X>::d(f.x, x) + f.x * derivate<Y>::d(f.y, x);
	}
};

template<class X, class Y>
struct derivate<BinaryOperationExpression<X, Y, BinaryOperation<BinaryOperationType::Div>>> {
	template<char n>
	static inline auto d(const BinaryOperationExpression<X, Y, BinaryOperation<BinaryOperationType::Div>>& f, const Variable<n>& x) ->
			typename std::decay<decltype((f.y * derivate<X>::d(f.x, x) - f.x * derivate<Y>::d(f.y, x)) / (f.y * f.y))>::type {
		return (f.y * derivate<X>::d(f.x, x) - f.x * derivate<Y>::d(f.y, x)) / (f.y * f.y);
	}
};

template<class X, class Y>
struct derivate<BinaryOperationExpression<X, Y, BinaryOperation<BinaryOperationType::Exp>>> {
	template<char n>
	static inline auto d(const BinaryOperationExpression<X, Y, BinaryOperation<BinaryOperationType::Exp>>& f, const Variable<n>& x) ->
			typename std::decay<decltype((f.x^f.y)*(derivate<X>::d(f.x, x)*f.y/f.x+derivate<Y>::d(f.y, x)*logarithm(f.x)))>::type {
		return ((f.x^f.y)*(derivate<X>::d(f.x, x)*f.y/f.x+derivate<Y>::d(f.y, x)*logarithm(f.x)));
	}
};

template<class X>
struct derivate<BinaryOperationExpression<X, Constant, BinaryOperation<BinaryOperationType::Exp>>> {
	template<char n>
	static inline auto d(const BinaryOperationExpression<X, Constant, BinaryOperation<BinaryOperationType::Exp>>& f, const Variable<n>& x) ->
			typename std::decay<decltype(f.y*(f.x^(f.y-1.0)) * derivate<X>::d(f.x, x))>::type {
		return f.y*(f.x^(f.y-1.0)) * derivate<X>::d(f.x, x);
	}
};

template<class Y>
struct derivate<BinaryOperationExpression<Constant, Y, BinaryOperation<BinaryOperationType::Exp>>> {
	template<char n>
	static inline auto d(const BinaryOperationExpression<Constant, Y, BinaryOperation<BinaryOperationType::Exp>>& f, const Variable<n>& x) ->
			typename std::decay<decltype((f.x^f.y) * log(f.x.value()) * derivate<Y>::d(f.y, x))>::type {
		return (f.x^f.y) * log(f.x.value()) * derivate<Y>::d(f.y, x);
	}
};

template<class X, class Desc>
struct derivate<FunctionExpression<X, Desc>> {
	template<char n>
	static inline auto d(const FunctionExpression<X, Desc>& f, const Variable<n>& x) ->
			typename std::decay<decltype(Desc::Derivative::construct(f.x) * derivate<X>::d(f.x, x))>::type {
		return Desc::Derivative::construct(f.x) * derivate<X>::d(f.x, x);
	}
};

template<class F>
class LeibnizWrapper {
	template<class>
	friend class LeibnizWrapper;
	const F& f;
public:
	inline LeibnizWrapper(const F& f): f(f) {}

	template<char n>
	inline auto operator /(const LeibnizWrapper<Variable<n>>& other) const ->
		decltype(derivate<F>::d(f, other.f)) {
		return derivate<F>::d(f, other.f);
	}
};

} // namespace detail

template<class F>
inline detail::LeibnizWrapper<F> d(const F& f) {
	return f;
}

#endif /* DERIVATE_H_ */
