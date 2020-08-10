#pragma once

#include "Vector.h"
#include "Vector2D.h"
#include "Line.h"
#include "Primitive.h"
#include "Rect.h"
#include "Circle.h"
#include "Ellipse.h"
#include "IntersectionInfo.h"
#include "Equation.h"
#include "QuadraticEquation.h"
#include "FactorisedQuadraticEquation.h"
#include "ExpandedQuadraticEquation.h"
#include "BinomialExpression.h"
//#include "Matrix.h"

namespace Engine
{
	namespace Maths
	{

		/*
		* Functions used to retrieve intersection info from two given shapes.
		* Purely mathematical and no physics calculations are performed.
		*/ 

		IntersectionInfo CheckIntersection(Rect& r1, Rect& r2);
		IntersectionInfo CheckIntersection(Rect& r, Ellipse& e);
		IntersectionInfo CheckIntersection(Rect& r, Line& l);
		IntersectionInfo CheckIntersection(Line& l1, Line& l2); // Simple linear intersection by equating formulae (y=mx+c)
		IntersectionInfo CheckIntersection(Line& l, Ellipse& e);
		IntersectionInfo CheckIntersection(Circle& c1, Circle& c2);
		IntersectionInfo CheckIntersection(Line& l, Circle& c);
		IntersectionInfo CheckIntersection(Rect& r, Circle& c);
		//IntersectionInfo* CheckIntersection(Ellipse& e1, Ellipse& e2);

	}
}