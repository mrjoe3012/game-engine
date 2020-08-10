#include "Equation.h"

using std::ostream;
using Engine::Maths::Equation;
using std::string;
using std::to_string;

Equation::Equation()
{

}

Equation::~Equation()
{

}

ostream& Engine::Maths::operator<<(ostream& os, const Equation& const eq)
{
	os << eq.ToString();
	return os;
}

Equation::EquationVariable::EquationVariable()
	:
	EquationVariable(0,0)
{

}

Equation::EquationVariable::EquationVariable(float coef, float exp)
	:
	coefficient(coef),
	exponent(exp)
{

}

Equation::EquationVariable::~EquationVariable()
{

}

ostream& Engine::Maths::operator<<(ostream& os, const Equation::EquationVariable& const eqtn)
{
	os << eqtn.ToString();
	return os;
}

string Equation::EquationVariable::ToString() const
{
	return std::string("EquationVariable { coefficient: " + to_string(coefficient) + " exponent: " + to_string(exponent) + " }");
}