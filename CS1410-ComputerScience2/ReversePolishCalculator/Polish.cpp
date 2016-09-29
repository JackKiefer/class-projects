#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <exception>
#include "Rational.hpp"

bool isFraction(std::string input)
{
	for (char& c : input)
	{
		if (c == '/') return true;
	}
	return false;
}

void push(std::string input, std::vector<Rational>& stack)
{
	Rational r;
	std::stringstream ss;	
	ss << input;

	if (isFraction(input)) { ss >> r; }
	else {	
		int n;
		ss >> n;
		r.setValues(n, 1);
	}

	stack.push_back(r);
}

int getOp(std::string input)
{
	if (input == "+") return 0;
	if (input == "-") return 1;
	if (input == "*") return 2;
	if (input == "/") return 3;
}

void evaluate(std::vector<Rational>& stack, std::string input)
{
	Rational b = stack.back();
	stack.pop_back();
	Rational a = stack.back();
	stack.pop_back();
	
	Rational c;

	int op = getOp(input);
	switch(op)
	{
		case 0: c = a + b; break;
		case 1: c = a - b; break;
		case 2: c = a * b; break;
		case 3: c = a / b; break;
	}

	stack.push_back(c);
}

void operatorError()
{
	std::cout << "Error: insufficient values to evaluate expression" << std::endl; 
}

void operate(std::vector<Rational>& stack, std::string input)
{
	if(stack.size() < 2){
		operatorError();
		return;
	}

	evaluate(stack, input);

	if(stack.size() == 1) std::cout << "= " << stack[0] << std::endl;
}

bool validRational(std::string & input)
{
	std::locale loc;
	int delim = 0;
	for (char& c : input)
	{
		if (c == '/') ++delim;
		if (!isdigit(c, loc) && c != '/') return false;
	}
	if (delim > 1 || input.back() == '/') return false;
	return true;
}

void inputError()
{
	std::cout << "Invalid input" << std::endl;
}

void evaluateInput(std::string & input, std::vector<Rational>& stack)
{
	if (input == "+" ||
	    input == "-" ||
		input == "/" ||
		input == "*") operate(stack, input);

	else if (input == "C" || input == "c") stack.clear();
	else if (input == "D" || input == "d")
	{
		if  (stack.size() == 0) std::cout << '0';	
		for (Rational& e : stack) { std::cout << e << " "; }
		std::cout << std::endl;	
	}
	else if (validRational(input))
	{
			push(input, stack);
	}

	else inputError(); return;
}

void getInput(bool& exit, std::vector<Rational>& stack)
{
    std::string input;
    std::getline(std::cin, input);
    if (input == "E" || input == "e") exit = true;
    else evaluateInput(input, stack);
}

void runCalculator()
{
	bool exit = false;
	std::vector<Rational> stack;
	while (!exit)
	{
		getInput(exit, stack);
	}
	stack.clear();
	std::cout << "Exiting..." << std::endl;
}

