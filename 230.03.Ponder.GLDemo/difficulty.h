#pragma once
#include <string>

class Difficulty
{
public:
	Difficulty(unsigned char difficulty = 0);
	Difficulty operator++(int postfix);
	Difficulty operator--(int postfix);
	std::string toString();
private:
	unsigned char difficulty;
	friend double operator-(const double lhs, Difficulty& rhs);
	friend double operator*(const double lhs, Difficulty& rhs);
};