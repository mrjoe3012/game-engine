#pragma once
#include <IStringConvertable.h>
#include <iostream>
#include <string>

using std::string;
using Engine::Utils::IStringConvertable;

namespace Engine
{

	namespace Maths
	{

		struct Equation : public IStringConvertable
		{
		public:
			Equation();
			~Equation();
			
			struct EquationVariable : public IStringConvertable
			{

			public:
				EquationVariable();
				EquationVariable(float, float);
				~EquationVariable();
				float coefficient;
				float exponent;

				friend ostream& operator<<(ostream&, const EquationVariable& const);
				string ToString() const override;
			};

			friend ostream& operator<<(ostream&, const Equation& const);

		};

	}

}