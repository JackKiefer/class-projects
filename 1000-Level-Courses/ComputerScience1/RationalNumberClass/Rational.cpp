#include <iostream>
#include "Rational.hpp"

Rational::Rational(int n, int d) : numerator(n), denominator(d) {}

/*-----------------------*/
/*   Fun with Functions  */
/*-----------------------*/

int Rational::getNumerator() const { return numerator; }

int Rational::getDenominator() const { return denominator; }

void Rational::setValues(int n, int d)
{
	numerator = n;
	denominator = d;
	simplify(numerator, denominator);
}

int getGCD(int a, int b)
{
	int remainder = a % b;
	if (remainder == 0) return b;
	return getGCD(b, remainder);
}

bool canReduce(int num, int dem)
{
	if (getGCD(num, dem) == 1) return false;
	return true;
}

void Rational::reduce(int num, int dem)
{
	int gcd = getGCD(num, dem);
	numerator = num / gcd;
	denominator = dem / gcd;
	return;
}

void Rational::simplify(int num, int dem)
{
	if (numerator == 0)
	{
		denominator = 0;
	}
	else if (numerator == denominator)
	{
		numerator = 1;
		denominator = 1;
	}
	else if (canReduce(num, dem))
	{
		reduce(num, dem);
	}
	return;
}

/*---------------------------*/
/*    Arithmetic operators   */
/*---------------------------*/

void Rational::operator+=(Rational const& b)
{
	numerator = numerator * b.denominator + b.numerator * denominator;
	denominator = denominator * b.denominator;
	simplify(numerator, denominator);
}

void Rational::operator-=(Rational const& b)
{
	numerator = numerator * b.denominator - b.numerator * denominator;
	denominator = denominator * b.denominator;
	simplify(numerator, denominator);
}

void Rational::operator*=(Rational const& b)
{
	numerator = numerator * b.numerator;
	denominator = denominator * b.denominator;
	simplify(numerator, denominator);
}

void Rational::operator/=(Rational const& b)
{
	numerator = numerator * b.denominator;
	denominator = denominator * b.numerator;
	simplify(numerator, denominator);
}

Rational operator+(Rational const & a, Rational const & b)
{
	Rational result(a);
	result += b;
	return result;
}

Rational operator-(Rational const & a, Rational const & b)
{
	Rational result(a);
	result -= b;
	return result;
}

Rational operator*(Rational const & a, Rational const & b)
{
	Rational result(a);
	result *= b;
	return result;
}

Rational operator/(Rational const & a, Rational const & b)
{
	Rational result(a);
	result /= b;
	return result;
}

/*---------------------------*/
/*    I/O operators          */
/*---------------------------*/

std::ostream& operator<<(std::ostream& o, Rational const & a)
{
	if (a.getNumerator() == a.getDenominator())
	{
		o << "1";
		return o;
	}
	else if (a.getNumerator() == 0)
	{
		o << "0";
		return o;
	}
	else if (a.getDenominator() == 0)
	{
		o << "undef";
		return o;
	}
	else if (a.getDenominator() == 1)
	{
		o << a.getNumerator();
		return o;
	}
	else
	{
		o << a.getNumerator() << "/" << a.getDenominator();
		return o;
	}
}

std::istream& operator >> (std::istream& i, Rational & a)
{
	int n, d;
	i >> n >> d;
	a.setValues(n, d);
	return i;
}

/*---------------------------*/
/*    Comparison operators   */
/*---------------------------*/

bool operator<=(Rational const & a, Rational const & b)
{
	return (a.getNumerator() * b.getDenominator() <= b.getNumerator() * a.getDenominator());
}

bool operator>=(Rational const & a, Rational const & b)
{
	return (a.getNumerator() * b.getDenominator() >= b.getNumerator() * a.getDenominator());
}

bool operator<(Rational const & a, Rational const & b)
{
	return (a.getNumerator() * b.getDenominator() < b.getNumerator() * a.getDenominator());
}

bool operator>(Rational const & a, Rational const & b)
{
	return (a.getNumerator() * b.getDenominator() > b.getNumerator() * a.getDenominator());
}

bool operator==(Rational const & a, Rational const & b)
{
	return (a.getNumerator() * b.getDenominator() == b.getNumerator() * a.getDenominator());
}

bool operator!=(Rational const & a, Rational const & b)
{
	return (a.getNumerator() * b.getDenominator() != b.getNumerator() * a.getDenominator());
}


/*---------------------------*/
/*    Type casting           */
/*---------------------------*/


Rational::operator float()
{
	float num = static_cast<float>(numerator);
	float dem = static_cast<float>(denominator);
	return num / dem;
}

Rational::operator double()
{
	double num = static_cast<double>(numerator);
	double dem = static_cast<double>(denominator);
	return num / dem;
}

Rational::operator Rational()
{
	return Rational();
}