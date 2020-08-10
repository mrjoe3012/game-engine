#pragma once
#include "QuadraticEquation.h"
#include "ExpandedQuadraticEquation.h"
#include "BinomialExpression.h"
#include <string>

using Engine::Maths::Equation;


namespace Engine
{
	namespace Maths
	{

		struct FactorisedQuadraticEquation : public QuadraticEquation // (x+c1)(x+c2)
		{
		public:
			FactorisedQuadraticEquation(BinomialExpression, BinomialExpression); // Powers ignored
			FactorisedQuadraticEquation(BinomialExpression); // Powers ignored
			FactorisedQuadraticEquation();
			~FactorisedQuadraticEquation();

			BinomialExpression expression1, expression2;

			QuadraticRootsInfo Roots() const override; // Using quadratic formula
			ExpandedQuadraticEquation Expand() const; // returns ax^2 + bx + c
			 
			std::string ToString() const override;
		};

	}
}