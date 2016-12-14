#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <iostream>

class Rational
{
public:
	Rational(int n = 0, int d = 1);
	int getNumerator()   const;
	int getDenominator() const;
	void operator+=(Rational const &);
	void operator-=(Rational const &);
	void operator*=(Rational const &);
	void operator/=(Rational const &);
	void simplify(int, int);
	void reduce(int, int);
	void setValues(int, int);
	operator float();
	operator double();
	operator Rational();
private:
	int numerator;
	int denominator;
};

Rational operator+(Rational const & a, Rational const & b);

Rational operator-(Rational const & a, Rational const & b);

Rational operator*(Rational const & a, Rational const & b);

Rational operator/(Rational const & a, Rational const & b);

std::ostream& operator<<(std::ostream&, Rational const & a);

std::istream& operator >> (std::istream&, Rational &);

bool operator<=(Rational const &, Rational const &);

bool operator==(Rational const &, Rational const &);

bool operator<(Rational const &, Rational const &);

bool operator>(Rational const &, Rational const &);

bool operator>=(Rational const &, Rational const &);

bool operator!=(Rational const &, Rational const &);

#endif