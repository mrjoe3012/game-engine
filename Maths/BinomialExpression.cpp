#include "BinomialExpression.h"
#include <iostream>
#include <string>

using Engine::Maths::BinomialExpression;
using std::ostream;
using std::string;
using std::to_string;

BinomialExpression::BinomialExpression(float x, float constant, float exponent)
	:
	x(x),
	constant(constant), 
	exponent(exponent)
{

}

BinomialExpression::BinomialExpression()
	:
	x(0),
	constant(0),
	exponent(0)
{

}

BinomialExpression::~BinomialExpression()
{

}

string BinomialExpression::ToString() const
{
	return std::string("BinomialExpression { x: " + to_string(x) + " constant: " + to_string(constant) + " exponent: " + to_string(exponent) + " } ");
}
ostream& Engine::Maths::operator<<(ostream& os, const BinomialExpression& const obj)
{
	os << obj.ToString();
	return os;
}