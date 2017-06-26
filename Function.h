/*
 * Function.h
 *
 *  Created on: 2017.06.26.
 *      Author: tooma
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

#include "Expression.h"
#include "Scalar.h"

#include <cmath>

namespace detail {

class SineFunction {
	template<class, class> friend class ::FunctionExpression;
	template<class F> friend struct detail::derivate;
	struct Derivative;

	static constexpr const char* name = "sin";

	static inline constexpr double calculate(double x) {
		return sin(x);
	}
};

class CosineFunction {
	template<class, class> friend class ::FunctionExpression;
	template<class F> friend struct detail::derivate;
	class Derivative;

	static constexpr const char* name = "cos";

	static inline constexpr double calculate(double x) {
		return cos(x);
	}
};

class TangentFunction {
	template<class, class> friend class ::FunctionExpression;
	template<class F> friend struct detail::derivate;
	class Derivative;

	static constexpr const char* name = "tan";

	static inline constexpr double calculate(double x) {
		return cos(x);
	}
};

class ArcusTangentFunction {
	template<class, class> friend class ::FunctionExpression;
	template<class F> friend struct detail::derivate;
	class Derivative;

	static constexpr const char* name = "atan";

	static inline constexpr double calculate(double x) {
		return atan(x);
	}
};
}

template<class X>
FunctionExpression<X, detail::SineFunction> sine(const X& x) {
	return x;
}

template<class X>
FunctionExpression<X, detail::CosineFunction> cosine(const X& x) {
	return x;
}

template<class X>
FunctionExpression<X, detail::TangentFunction> tangent(const X& x) {
	return x;
}

template<class X>
FunctionExpression<X, detail::ArcusTangentFunction> arcusTangent(const X& x) {
	return x;
}


struct detail::SineFunction::Derivative {
	template<class X>
	static inline auto construct(const X& x)
	-> decltype(cosine(x)) {
		return cosine(x);
	}
};

struct detail::CosineFunction::Derivative {
	template<class X>
	static inline auto construct(const X& x)
	-> decltype(Constant(0)-sine(x)) {
		return Constant(0)-sine(x);
	}
};

struct detail::TangentFunction::Derivative {
	template<class X>
	static inline auto construct(const X& x)
	-> decltype(Constant(1)/(cosine(x)*cosine(x))) {
		return Constant(1)/(cosine(x)*cosine(x));
	}
};

struct detail::ArcusTangentFunction::Derivative {
	template<class X>
	static inline auto construct(const X& x)
	-> decltype(Constant(1)/(x*x+Constant(1))) {
		return Constant(1)/(x*x+Constant(1));
	}
};

#endif /* FUNCTION_H_ */
