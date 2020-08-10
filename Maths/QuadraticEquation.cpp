#include "QuadraticEquation.h"

using Engine::Maths::QuadraticEquation;
typedef Engine::Maths::Equation::EquationVariable EquationVariable;
typedef Engine::Maths::QuadraticEquation::QuadraticRootsInfo QuadraticRootsInfo;

using std::string;
using std::ostream;
using std::to_string;

QuadraticEquation::QuadraticEquation()
{

}

QuadraticEquation::~QuadraticEquation()
{

}

QuadraticRootsInfo::QuadraticRootsInfo()
	:
	discriminant(0),
	root1(0.0f),
	root2(0.0f)
{

}

QuadraticRootsInfo::QuadraticRootsInfo(float discriminant, float root)
	:
	discriminant(discriminant),
	root1(root),
	root2(0.0f)
{

}

QuadraticRootsInfo::QuadraticRootsInfo(float discriminant, float root1, float root2)
	:
	discriminant(discriminant),
	root1(root1),
	root2(root2)
{

}

QuadraticRootsInfo::~QuadraticRootsInfo()
{

}

string QuadraticRootsInfo::ToString() const
{
	return string("QuadraticRootsInfo { discriminant: " + to_string(discriminant) + " root1: " + to_string(root1) + " root2: " + to_string(root2) + " } ");
}

ostream& Engine::Maths::operator<<(ostream& os, const QuadraticRootsInfo& const obj)
{
	os << obj.ToString();
	return os;
}