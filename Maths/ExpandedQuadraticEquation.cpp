#include "ExpandedQuadraticEquation.h"
#include <math.h>

#include <Debug.h>

using Engine::Utils::AlgorithmProfileInfo;
using Engine::Utils::AlgorithmProfiler;
using Engine::Maths::ExpandedQuadraticEquation;
typedef Engine::Maths::QuadraticEquation::EquationVariable EquationVariable;
typedef Engine::Maths::QuadraticEquation::QuadraticRootsInfo QuadraticRootsInfo;

ExpandedQuadraticEquation::ExpandedQuadraticEquation()
{

}

ExpandedQuadraticEquation::ExpandedQuadraticEquation(EquationVariable xSquared, EquationVariable x, EquationVariable constant)
	:
	xSquared(xSquared),
	x(x),
	constant(constant)
{

}

ExpandedQuadraticEquation::~ExpandedQuadraticEquation()
{

}

std::string ExpandedQuadraticEquation::ToString() const
{
	return std::string("ExpandedQuadraticEquation { xSquared: " + xSquared.ToString() + " x: " + x.ToString() + " constant: " + constant.ToString() + " }");
}

QuadraticRootsInfo ExpandedQuadraticEquation::Roots() const
{
#ifdef DEBUG
	auto profile = AlgorithmProfiler::GetInstance()->CreateProfile("ExpandedQuadraticEquation::Roots()");
	profile.StartTimer();
#endif
	float discriminant = powf(this->x.coefficient, 2) - (4 * this->xSquared.coefficient*this->constant.coefficient);
	float root1 = 0, root2 = 0;

	if (discriminant > 0.0f && discriminant < 0.001f)
		discriminant = 0.0f;

	if (discriminant < 0)
	{
		root1 = NAN, root2 = NAN;
	}
	else
	{
		if (xSquared.coefficient == 0)
		{
			if (constant.coefficient == 0)
			{
				root1 = 0;
				root2 = 0;
			}
			else
			{
				root1 = (-constant.coefficient) / x.coefficient;
				root2 = (-constant.coefficient) / x.coefficient;
			}
		}
		else
		{
			root1 = ((-x.coefficient) + (sqrtf(discriminant))) / (2 * xSquared.coefficient);
			root2 = ((-x.coefficient) - (sqrtf(discriminant))) / (2 * xSquared.coefficient);
		}
	}

#ifdef DEBUG
	profile.PauseTimer();
#endif

	return QuadraticRootsInfo(discriminant, root1, root2);
}

void ExpandedQuadraticEquation::operator=(const ExpandedQuadraticEquation& const rhs)
{
	this->xSquared = rhs.xSquared;
	this->x = rhs.x;
	this->constant = rhs.constant;
}

void ExpandedQuadraticEquation::operator+=(const ExpandedQuadraticEquation& const rhs)
{
	this->xSquared.coefficient += rhs.xSquared.coefficient;
	this->x.coefficient += rhs.x.coefficient;
	this->constant.coefficient += rhs.constant.coefficient;
}

void ExpandedQuadraticEquation::operator-=(const ExpandedQuadraticEquation& const rhs)
{
	this->xSquared.coefficient -= rhs.xSquared.coefficient;
	this->x.coefficient -= rhs.x.coefficient;
	this->constant.coefficient -= rhs.constant.coefficient;
}

void ExpandedQuadraticEquation::operator*=(const float const rhs)
{
	this->xSquared.coefficient *= rhs;
	this->x.coefficient *= rhs;
	this->constant.coefficient *= rhs;
}

void ExpandedQuadraticEquation::operator/=(const float const rhs)
{
	this->xSquared.coefficient /= rhs;
	this->x.coefficient /= rhs;
	this->constant.coefficient /= rhs;
}

ExpandedQuadraticEquation ExpandedQuadraticEquation::operator+(const ExpandedQuadraticEquation& const rhs)
{
	ExpandedQuadraticEquation result(EquationVariable(this->xSquared.coefficient+rhs.xSquared.coefficient, 1), EquationVariable(this->x.coefficient + rhs.x.coefficient, 1), EquationVariable(this->constant.coefficient + rhs.constant.coefficient, 1));
	return result;
}

ExpandedQuadraticEquation ExpandedQuadraticEquation::operator- (const ExpandedQuadraticEquation& const rhs)
{
	ExpandedQuadraticEquation result(EquationVariable(this->xSquared.coefficient - rhs.xSquared.coefficient, 1), EquationVariable(this->x.coefficient - rhs.x.coefficient, 1), EquationVariable(this->constant.coefficient - rhs.constant.coefficient, 1));
	return result;
}

ExpandedQuadraticEquation ExpandedQuadraticEquation::operator*(const float const rhs)
{
	ExpandedQuadraticEquation result = *this;
	result.xSquared.coefficient *= rhs;
	result.x.coefficient *= rhs;
	result.constant.coefficient *= rhs;

	return result;

}

ExpandedQuadraticEquation ExpandedQuadraticEquation::operator/(const float const rhs)
{
	ExpandedQuadraticEquation result = *this;
	result.xSquared.coefficient /= rhs;
	result.x.coefficient /= rhs;
	result.constant.coefficient /= rhs;

	return result;
}