#pragma once
#include "Equation.h"
#include <IStringConvertable.h>
#include <string>
#include <iostream>

namespace Engine
{
	namespace Maths
	{

		struct BinomialExpression : public IStringConvertable
		{

		public:
			BinomialExpression();
			BinomialExpression(float x, float constant, float exponent);
			~BinomialExpression();
			float x, constant, exponent;

			std::string ToString() const override;
			friend std::ostream& operator<<(std::ostream&, const BinomialExpression& const);
		};

	}
}