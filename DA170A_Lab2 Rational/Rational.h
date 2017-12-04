#pragma once

#include <iostream>
#include "GCD.h"

template <typename T>
struct TypeSize
{
	static const int value = -1; //sizeof(T);
};

template <>
struct TypeSize<int>
{
	static const int value = 4;
};

template <>
struct TypeSize<short>
{
	static const int value = 2;
};

template <>
struct TypeSize<long long>
{
	static const int value = 8;
};

template<typename Tint>
class Rational
{
public:
	Tint p;
	Tint q;

	Rational(Tint p, Tint q) : p(p), q(q)
	{
	}

	Rational(Tint p) : Rational(p, 1)
	{
	}

	Rational() : Rational(0)
	{
	}

	template <typename arg>
	Rational(Rational<arg> r) : Rational(r.p, r.q)
	{
	}

	friend std::ostream& operator<< (std::ostream &cout, Rational<Tint> R)
	{
		cout << R.p << '/' << R.q;
		return cout;
	}

	friend std::istream& operator >> (std::istream& in, Rational<Tint>& r) 
	{
		int p, q;
		in >> p;
		in.ignore(1);
		in >> q;
		r = Rational<Tint>(p, q);
		return in;
	}

	bool Rational<Tint>::operator==(const Rational& rhs) const
	{
		return ((p / q) == (rhs.p / rhs.q));
	}

	Rational<Tint> Rational<Tint>::operator=(const Tint& rhs)
	{
		p = rhs;
		q = 1;
		return (*this);
	}

	Rational<Tint> Rational<Tint>::operator+=(const Tint& rhs)
	{
		p += rhs * q;
		return (*this);
	}

	Rational<Tint> Rational<Tint>::operator+(const Tint& rhs)
	{
		Rational<Tint> copy(*this);
		copy.p += rhs * copy.q;
		return copy;
	}

	Rational<Tint> operator-()
	{
		Tint tempP = -p;
		Tint tempQ = q;
		return Rational<Tint>(tempP, tempQ);
	}

	Rational<Tint>& operator++ () //Prefix
	{
		p += q;
		return *this;
	}

	Rational<Tint> operator++ (int) //Postfix
	{
		Rational<Tint> copy(*this);   
		++(*this);
		return copy;
	}

	explicit operator int()
	{
		return (p/q);
	}
};

template <typename L, typename R>
Rational<L> operator+(const Rational<L>& lhs, const Rational<R>& rhs)
{
	L tempP = rhs.q * lhs.p + lhs.q * rhs.p;
	L tempQ = lhs.q * rhs.q;

	Reduce<L>(tempP, tempQ);

	return Rational<L>(tempP, tempQ);
}