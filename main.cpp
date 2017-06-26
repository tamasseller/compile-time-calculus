/*
 * main.cpp
 *
 *      Author: tamas.seller
 */

#include <iostream>
#include <iomanip>

#include <string.h>
#include <type_traits>

enum class BinOpType {
	Add, Sub, Mul, Div
};

template<BinOpType op> struct BinOp;

template<char n>
class Var;
class Const;

template<class Child> class Operators;

template<> struct BinOp<BinOpType::Add> {
	static constexpr auto precedence = 1u;
	template<class X, class Y>
	static inline constexpr auto calculate(const X& x, const Y& y) -> decltype(x + y) {
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

template<> struct BinOp<BinOpType::Sub> {
	static constexpr char opChar = '-';
	static constexpr auto precedence = 1u;
	template<class X, class Y>
	static inline constexpr auto calculate(const X& x, const Y& y) -> decltype(x - y) {
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

template<> struct BinOp<BinOpType::Mul> {
private:
public:
	static constexpr auto precedence = 0u;
	template<class X, class Y>
	static inline constexpr auto calculate(const X& x, const Y& y) -> decltype(x * y) {
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

template<> struct BinOp<BinOpType::Div> {
	static constexpr char opChar = '/';
	static constexpr auto precedence = 0u;
	template<class X, class Y>
	static inline constexpr auto calculate(const X& x, const Y& y) -> decltype(x / y) {
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

template<class X, class Y, class Op>
class BinOpExpr: public Operators<BinOpExpr<X, Y, Op>> {
protected:
	template<class F> friend struct derivate;
	typename X::Handle x;
	typename Y::Handle y;

public:
	static constexpr bool isConst = false;

	typedef const BinOpExpr Handle;
		static constexpr auto precedence = Op::precedence;

		inline BinOpExpr(const X &x, const Y &y): x(x), y(y) {}
		std::string print(unsigned int precedence=-1u) const {
			std::string ret;

			ret = Op::print(x, y, this->precedence);

			if(precedence < this->precedence)
				ret = "(" + ret + ")";


			return ret;
		}

		double value() const {return Op::calculate(this->x.value(), this->y.value());}
};

template<class Child>
class Operators {
public:
	template<class Other>
	BinOpExpr<Child, Other, BinOp<BinOpType::Add>> operator +(const Other& other) const {
		return BinOpExpr<Child, Other, BinOp<BinOpType::Add>>(*static_cast<const Child*>(this), other);
	}

	template<class Other>
	BinOpExpr<Child, Other, BinOp<BinOpType::Sub>> operator -(const Other& other) const {
		return BinOpExpr<Child, Other, BinOp<BinOpType::Sub>>(*static_cast<const Child*>(this), other);
	}

	template<class Other>
	BinOpExpr<Child, Other, BinOp<BinOpType::Mul>> operator *(const Other& other) const {
		return BinOpExpr<Child, Other, BinOp<BinOpType::Mul>>(*static_cast<const Child*>(this), other);
	}

	template<class Other>
	BinOpExpr<Child, Other, BinOp<BinOpType::Div>> operator /(const Other& other) const {
		return BinOpExpr<Child, Other, BinOp<BinOpType::Div>>(*static_cast<const Child*>(this), other);
	}

	BinOpExpr<Child, Const, BinOp<BinOpType::Add>> operator +(const double& other) const {
		return BinOpExpr<Child, Const, BinOp<BinOpType::Add>>(*static_cast<const Child*>(this), other);
	}

	BinOpExpr<Child, Const, BinOp<BinOpType::Sub>> operator -(const double& other) const {
		return BinOpExpr<Child, Const, BinOp<BinOpType::Sub>>(*static_cast<const Child*>(this), other);
	}

	BinOpExpr<Child, Const, BinOp<BinOpType::Mul>> operator *(const double& other) const {
		return BinOpExpr<Child, Const, BinOp<BinOpType::Mul>>(*static_cast<const Child*>(this), other);
	}

	BinOpExpr<Child, Const, BinOp<BinOpType::Div>> operator /(const double& other) const {
		return BinOpExpr<Child, Const, BinOp<BinOpType::Div>>(*static_cast<const Child*>(this), other);
	}
};

class Const: public Operators<Const> {
public:
	const double content;
	static constexpr bool isConst = true;
	static constexpr auto precedence = 0u;
	typedef const Const Handle;

	double value() const {return content;}
	Const(double content): content(content){};

	std::string print(unsigned int=0) const {return std::to_string(content);}

	Const operator +(const Const& other) const {
		return content + other.content;
	}

	Const operator -(const Const& other) const {
		return content - other.content;
	}

	Const operator *(const Const& other) const {
		return content * other.content;
	}

	Const operator /(const Const& other) const {
		return content / other.content;
	}

	Const operator +(const double& other) const {
		return content + other;
	}

	Const operator -(const double& other) const {
		return content - other;
	}

	Const operator *(const double& other) const {
		return content * other;
	}

	Const operator /(const double& other) const {
		return content / other;
	}

	using Operators<Const>::operator+;
	using Operators<Const>::operator-;
	using Operators<Const>::operator/;
	using Operators<Const>::operator*;
};

template<char n>
class Var: public Operators<Var<n>> {
	double content;
public:
	static constexpr bool isConst = false;
	static constexpr auto precedence = 0u;
	typedef const Var& Handle;

	double value() const {return content;}

	inline Var& operator =(const double& v) {
		content = v;
		return *this;
	}

	std::string print(unsigned int=0) const {return std::string(1, n);}
	Const d(const Var& var) const {return (&var == this) ? 1.0 : 0.0;}
};

template<class F> struct derivate {};

template<char n> struct derivate<Var<n>> {
	template<char o>
	static Const d(const Var<n>&, const Var<o>&) {
		return 0.0;
	}

	static Const d(const Var<n>&, const Var<n>&) {
		return 1.0;
	}
};

template<> struct derivate<Const> {
	template<char n>
	static Const d(const Const& f, const Var<n>& x) {
		return 0.0;
	}
};

template<class X, class Y>
struct derivate<BinOpExpr<X, Y, BinOp<BinOpType::Add>>> {
	template<char n>
	static auto d(const BinOpExpr<X, Y, BinOp<BinOpType::Add>>& f, const Var<n>& x) ->
			typename std::decay<decltype(derivate<X>::d(f.x, x) + derivate<Y>::d(f.y, x))>::type {
		return derivate<X>::d(f.x, x) + derivate<Y>::d(f.y, x);
	}
};

template<class X, class Y>
struct derivate<BinOpExpr<X, Y, BinOp<BinOpType::Sub>>> {
	template<char n>
	static auto d(const BinOpExpr<X, Y, BinOp<BinOpType::Sub>>& f, const Var<n>& x) ->
			typename std::decay<decltype(derivate<X>::d(f.x, x) - derivate<Y>::d(f.y, x))>::type {
		return derivate<X>::d(f.x, x) - derivate<Y>::d(f.y, x);
	}
};

template<class X, class Y>
struct derivate<BinOpExpr<X, Y, BinOp<BinOpType::Mul>>> {
	template<char n>
	static auto d(const BinOpExpr<X, Y, BinOp<BinOpType::Mul>>& f, const Var<n>& x) ->
			typename std::decay<decltype(f.y * derivate<X>::d(f.x, x) + f.x * derivate<Y>::d(f.y, x))>::type {
		return f.y * derivate<X>::d(f.x, x) + f.x * derivate<Y>::d(f.y, x);
	}
};

template<class X, class Y>
struct derivate<BinOpExpr<X, Y, BinOp<BinOpType::Div>>> {
	template<char n>
	static auto d(const BinOpExpr<X, Y, BinOp<BinOpType::Div>>& f, const Var<n>& x) ->
			typename std::decay<decltype((f.y * derivate<X>::d(f.x, x) - f.x * derivate<Y>::d(f.y, x)) / (f.y * f.y))>::type {
		return (f.y * derivate<X>::d(f.x, x) - f.x * derivate<Y>::d(f.y, x)) / (f.y * f.y);
	}
};

int main()
{
    Var<'x'> x;
    Var<'y'> y;

    x = 3;
    y = 4;

    auto v = x / (x + 1.0);
    auto dv_dx = derivate<decltype(v)>::d(v, x);

    std::cout << dv_dx.value() << std::endl;
    std::cout << dv_dx.print() << std::endl;
}
