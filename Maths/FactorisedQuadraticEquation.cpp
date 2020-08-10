#include "FactorisedQuadraticEquation.h"
#include <math.h>

#include <Debug.h>

using Engine::Utils::AlgorithmProfiler;
using Engine::Maths::FactorisedQuadraticEquation;
using Engine::Maths::ExpandedQuadraticEquation;
using Engine::Maths::BinomialExpression;
typedef  Engine::Maths::Equation::EquationVariable EquationVariable;
typedef Engine::Maths::QuadraticEquation::QuadraticRootsInfo QuadraticRootsInfo;

using std::string;
using std::to_string;

FactorisedQuadraticEquation::FactorisedQuadraticEquation(BinomialExpression expression)
	:
	expression1(expression),
	expression2(expression)
{

}

FactorisedQuadraticEquation::FactorisedQuadraticEquation(BinomialExpression expression1, BinomialExpression expression2)
	:
	expression1(expression1),
	expression2(expression2)
{
	
}

FactorisedQuadraticEquation::FactorisedQuadraticEquation()
{

}

FactorisedQuadraticEquation::~FactorisedQuadraticEquation()
{

}

QuadraticRootsInfo FactorisedQuadraticEquation::Roots() const
{
#ifdef DEBUG
	auto profile = AlgorithmProfiler::GetInstance()->CreateProfile("FactorisedQuadraticEquation::Roots()");
	profile.StartTimer();
#endif
	QuadraticRootsInfo res = Expand().Roots();
#ifdef DEBUG
	profile.PauseTimer();
#endif
	return res;
}

ExpandedQuadraticEquation FactorisedQuadraticEquation::Expand() const
{
#ifdef DEBUG
	auto profile = AlgorithmProfiler::GetInstance()->CreateProfile("FactorisedQuadraticEquation::Expand()");
	profile.StartTimer();
#endif
	float xSquaredCoef = expression1.x*expression2.x;
	float xCoef = (expression1.x*expression2.constant) + (expression1.constant*expression2.x);
	float constant = expression1.constant*expression2.constant;

	ExpandedQuadraticEquation result(EquationVariable(xSquaredCoef,1), EquationVariable(xCoef, 1), EquationVariable(constant, 1));
#ifdef DEBUG
	profile.PauseTimer();
#endif
	return result;
}

string FactorisedQuadraticEquation::ToString() const
{
	return string("FactorisedQuadraticEquation { expression1: " + expression1.ToString() + " expression2: " + expression1.ToString() + " }");
}

