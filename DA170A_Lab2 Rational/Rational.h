#pragma once

#include <iostream>
#include "GCD.h"

template <typename T>
struct TypeSize
{
	static const int value = sizeof(T);
};

//template <>
//struct TypeSize<int>
//{
//	static const int value = sizeof(int); //4
//};


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

};