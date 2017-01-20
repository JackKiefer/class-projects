// Demonstrates a simple implementation of a rational numbers class

#include <iostream>
#include <string>
#include "Rational.hpp"

std::string compare(Rational const & a, Rational const & b, std::string c)
{
	if (c == ">"  && a > b)  return "true";
	if (c == "<"  && a < b)  return "true";
	if (c == "<=" && a <= b) return "true";
	if (c == ">=" && a >= b) return "true";
	if (c == "!=" && a != b) return "true";
	if (c == "==" && a == b) return "true";
	return "false";
}

int main()
{
	Rational a;
	Rational b;

	std::cout << "This program demonstrates basic implementation of the rational  numbers class." << std::endl;
	std::cout << "Input the first number's numerator, press enter, and then input its denominator:" << std::endl;

	std::cin >> a;

	std::cout << std::endl << "Input accepted: " << a << std::endl << std::endl;
	std::cout << "Now, input the second number's values:" << std::endl;

	std::cin >> b;

	std::cout << std::endl << "Input accepted: " << b << std::endl << std::endl;

	auto sum        = a + b;
	auto difference = a - b;
	auto product    = a * b;
	auto quotient   = a / b;
	
	std::cout << "Arithmetic operators:" << std::endl;

	std::cout << a << " + " << b << " = " << sum << std::endl;
	std::cout << a << " - " << b << " = " << difference << std::endl;
	std::cout << a << " * " << b << " = " << product << std::endl;
	std::cout << a << " / " << b << " = " << quotient << std::endl << std::endl;

	std::cout << "Comparison operators:" << std::endl;
	std::cout << a << " > " << b << " : " << compare(a, b, ">") << std::endl;
	std::cout << a << " < " << b << " : " << compare(a, b, "<") << std::endl;
	std::cout << a << " >= " << b << " : " << compare(a, b, ">=") << std::endl;
	std::cout << a << " <= " << b << " : " << compare(a, b, "<=") << std::endl;
	std::cout << a << " == " << b << " : " << compare(a, b, "==") << std::endl;
	std::cout << a << " != " << b << " : " << compare(a, b, "!=") << std::endl;

	float aFloat = static_cast<float>(a);
	double bDouble = static_cast<double>(b);

	std::cout << std::endl << "Type casting:" << std::endl;
	std::cout << "First rational as a float:   " << aFloat << std::endl;
	std::cout << "Second rational as a double: " << bDouble << std::endl;
	
	int stacysMom;
	std::cout << "Enter an integer to be type-casted as a rational:" << std::endl;
	std::cin >> stacysMom;

	static_cast<Rational>(stacysMom);

	std::cout << "Your integer as a rational: " << stacysMom << std::endl;
	std::cout << "It's a rational, I promise!" << std::endl;

	char dummy;
	std::cin >> dummy;
}