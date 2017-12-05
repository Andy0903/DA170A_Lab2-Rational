#pragma once

#include <iostream>
#include "GCD.h"

template<typename A>
struct LargerType;

template <>
struct LargerType<int>
{
	typedef long long type;
};

template <>
struct LargerType<short>
{
	typedef int type;
};

template <>
struct LargerType<long long>
{
	typedef long long type;
};

template <typename T>
struct TypeSize;

template <>
struct TypeSize<int>
{
	static const int byte = 4;
};

template <>
struct TypeSize<short>
{
	static const int byte = 2;
};

template <>
struct TypeSize<long long>
{
	static const int byte = 8;
};

template <bool C, typename A, typename B>
struct Conditional;

template<typename A, typename B>
struct Conditional<true, A, B>
{
	typedef A type;
};

template<typename A, typename B>
struct Conditional<false, A, B>
{
	typedef B type;
};

template<typename A, typename B>
struct LargestType
{
	typedef typename Conditional<(TypeSize<A>::byte > TypeSize<B>::byte), A, B>::type type;
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

	Rational(const Tint& p) : Rational(p, 1)
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
Rational<typename LargestType<L,R>::type> operator+(const Rational<L>& lhs, const Rational<R>& rhs)
{
	typedef typename LargestType<L, R>::type commonType;
	typedef typename LargerType<commonType>::type BiggerType;

	BiggerType tempP = rhs.q * lhs.p + lhs.q * rhs.p;
	BiggerType tempQ = lhs.q * rhs.q;

	Reduce<BiggerType>(tempP, tempQ);

	return Rational<commonType>(tempP, tempQ);
}

template <typename L, typename R>
bool operator==(const L& lhs, const Rational<R>& rhs)
{
	return (lhs == (rhs.p / rhs.q));
}