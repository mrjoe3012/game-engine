#pragma once
#include "QuadraticEquation.h"
#include <string>

namespace Engine
{
	namespace Maths
	{
		struct ExpandedQuadraticEquation : public QuadraticEquation
		{
		public:
			ExpandedQuadraticEquation();
			ExpandedQuadraticEquation(EquationVariable, EquationVariable, EquationVariable);
			~ExpandedQuadraticEquation();

			void operator=(const ExpandedQuadraticEquation& const rhs);
			void operator+=(const ExpandedQuadraticEquation& const rhs);
			void operator-=(const ExpandedQuadraticEquation& const rhs);
			void operator*=(const float const rhs);
			void operator/=(const float const rhs);
			ExpandedQuadraticEquation operator+(const ExpandedQuadraticEquation& const rhs);
			ExpandedQuadraticEquation operator- (const ExpandedQuadraticEquation& const rhs);
			ExpandedQuadraticEquation operator* (const float const rhs);
			ExpandedQuadraticEquation operator/ (const float const rhs);

			EquationVariable xSquared, x, constant;

			QuadraticRootsInfo Roots() const override;

			string ToString() const override;

		};
	}
}