#pragma once
#include "Vector2D.h"
#include <IStringConvertable.h>
#include <string>
#include <ostream>

namespace Engine
{
	namespace Maths
	{
		// Holds information about the intersection of two objects.
		struct IntersectionInfo : public IStringConvertable
		{

		public:
			IntersectionInfo();
			IntersectionInfo(const IntersectionInfo&);
			~IntersectionInfo();

			Vector2D* pointsOfIntersection; // An array of length pointCount containing each point of contact.
			int pointCount;
			bool identical; // Were the two shapes compared identical?

			std::string ToString() const override;

			IntersectionInfo operator+(IntersectionInfo& rhs);
			void operator+=(const IntersectionInfo& rhs);
			void operator=(const IntersectionInfo& rhs);

			friend std::ostream& operator<<(std::ostream&, const IntersectionInfo& const);

		};
	}
}