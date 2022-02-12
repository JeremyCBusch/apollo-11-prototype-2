#include "difficulty.h"

Difficulty::Difficulty(unsigned char difficulty) : difficulty(difficulty % 5) {}

Difficulty Difficulty::operator++(int postfix)
{
	Difficulty temp(this->difficulty);
	this->difficulty++;
	return temp;
}

Difficulty Difficulty::operator--(int postfix)
{
	Difficulty temp(this->difficulty);
	this->difficulty++;
	return temp;
}

std::string Difficulty::toString()
{
	switch (difficulty % 5) {
	case 0:
		return std::string("Easy");
	case 1:
		return std::string("Medium");
	case 2:
		return std::string("Hard");
	case 3:
		return std::string("Super Hard");
	case 4:
		return std::string("Impossible");
	}
}

double operator - (const double lhs, Difficulty& rhs)
{
	return lhs - (double)(rhs.difficulty % 5);
}

double operator * (const double lhs, Difficulty& rhs)
{
	return lhs * (double)(rhs.difficulty % 5);
}