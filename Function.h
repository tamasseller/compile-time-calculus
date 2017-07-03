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
	template<class T> friend struct detail::ContentPrinter;
	struct Derivative;

	static constexpr const char* name = "sin";

	static inline constexpr double calculate(double x) {
		return sin(x);
	}
};

class CosineFunction {
	template<class, class> friend class ::FunctionExpression;
	template<class F> friend struct detail::derivate;
	template<class T> friend struct detail::ContentPrinter;
	class Derivative;

	static constexpr const char* name = "cos";

	static inline constexpr double calculate(double x) {
		return cos(x);
	}
};

class TangentFunction {
	template<class, class> friend class ::FunctionExpression;
	template<class F> friend struct detail::derivate;
	template<class T> friend struct detail::ContentPrinter;
	class Derivative;

	static constexpr const char* name = "tan";

	static inline constexpr double calculate(double x) {
		return tan(x);
	}
};

class ArcusTangentFunction {
	template<class, class> friend class ::FunctionExpression;
	template<class F> friend struct detail::derivate;
	template<class T> friend struct detail::ContentPrinter;
	class Derivative;

	static constexpr const char* name = "atan";

	static inline constexpr double calculate(double x) {
		return atan(x);
	}
};

class NaturalLogarithmFunction {
	template<class, class> friend class ::FunctionExpression;
	template<class F> friend struct detail::derivate;
	template<class T> friend struct detail::ContentPrinter;
	class Derivative;

	static constexpr const char* name = "ln";

	static inline constexpr double calculate(double x) {
		return log(x);
	}
};

}

template<class X>
inline FunctionExpression<X, detail::SineFunction> sine(const X& x) {
	return x;
}

inline Constant sine(const Constant& c) {
	return sin(c.value());
}

template<class X>
inline FunctionExpression<X, detail::CosineFunction> cosine(const X& x) {
	return x;
}

inline Constant cosine(const Constant& c) {
	return cos(c.value());
}

template<class X>
inline FunctionExpression<X, detail::TangentFunction> tangent(const X& x) {
	return x;
}

inline Constant tangent(const Constant& c) {
	return tan(c.value());
}

template<class X>
inline FunctionExpression<X, detail::ArcusTangentFunction> arcusTangent(const X& x) {
	return x;
}

inline Constant arcusTangent(const Constant& c) {
	return atan(c.value());
}

template<class X>
inline FunctionExpression<X, detail::NaturalLogarithmFunction> logarithm(const X& x) {
	return x;
}

inline Constant logarithm(const Constant& c) {
	return log(c.value());
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
	-> decltype(-sine(x)) {
		return -sine(x);
	}
};

struct detail::TangentFunction::Derivative {
	template<class X>
	static inline auto construct(const X& x)
	-> decltype(Constant(1)/(cosine(x)^2.0)) {
		return Constant(1)/(cosine(x)^2.0);
	}
};

struct detail::ArcusTangentFunction::Derivative {
	template<class X>
	static inline auto construct(const X& x)
	-> decltype(Constant(1)/((x^Constant(2.0))+Constant(1))) {
		return Constant(1)/((x^Constant(2.0))+Constant(1));
	}
};

struct detail::NaturalLogarithmFunction::Derivative {
	template<class X>
	static inline auto construct(const X& x)
	-> decltype(Constant(1)/x) {
		return Constant(1)/x;
	}
};


#endif /* FUNCTION_H_ */
