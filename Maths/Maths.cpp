#include "Maths.h"
#include <Debug.h>
#include <vector>

using namespace Engine::Maths;
using Engine::Maths::IntersectionInfo;
using Engine::Utils::AlgorithmProfileInfo;
using Engine::Utils::AlgorithmProfiler;


IntersectionInfo Engine::Maths::CheckIntersection(Line& l1, Line& l2)
{
#ifdef DEBUG
	auto profile = AlgorithmProfiler::GetInstance()->CreateProfile("CheckIntersection(Line&,Line&)");
	profile.StartTimer();
#endif
	IntersectionInfo possiblePoints;

	if (l1 == l2) // Lines are perfectly identical
	{
		possiblePoints.identical = true;
		possiblePoints.pointCount = 0;
		return possiblePoints;
	}

	Vector2D pointOfIntersection;
	bool foundPoint = false;

	if (isnan(l1.Gradient()) && isnan(l2.Gradient())) // Both gradients are undefined and both vertical lines.
	{
		if (l1.begin.x == l2.begin.x)
		{
			Line line1, line2; // Temporary vars

			line1 = l1.LineVector().y < 0 ? Line(l1.end, l1.begin) : l1; // If the line is going downwards, flip it so that both are going upwards.
			line2 = l2.LineVector().y < 0 ? Line(l2.end, l2.begin) : l2;

			Line lineOnTop = line1.begin.y < line2.begin.y ? line2 : line1; // Find out which line starts furthest up.

			pointOfIntersection = Vector2D(lineOnTop.begin); // Intersects where the overlapping line begins.
			foundPoint = true;
		}
	}
	else if ((isnan(l1.Gradient()) || isnan(l2.Gradient()))) // If only one line has an undefined gradient
	{
		float x = isnan(l1.Gradient()) ? l1.begin.x : l2.begin.x; // Set the x value to the x value of the line with the undefined gradient.
		float y = isnan(l1.Gradient()) ? l2.GetY(x) : l1.GetY(x); // Set the y value to the corresponding point on the line that has a real gradient.

		pointOfIntersection = Vector2D(x, y);
		foundPoint = true;
	}
	else
	{
		float xCoefficient = l1.Gradient() - l2.Gradient();

		float x = 0.0f, y = 0.0f;

		float rhs = l2.ConstantOffset() - l1.ConstantOffset();
		if (xCoefficient == 0 && rhs == 0) // The lines are indentical: y=2x+1;y=2x+1-> 2x+1=2x+1-> 0=0
		{

			Line line1, line2; // Temporary vars

			line1 = l1.LineVector().x < 0 ? Line(l1.end, l1.begin) : l1; // If the line is going backwards, flip it so that both are going forwards.
			line2 = l2.LineVector().x < 0 ? Line(l2.end, l2.begin) : l2;

			Line lineOnRight = line1.begin.x < line2.begin.x ? line2 : line2; // Find out which line starts furthest to the right.

			pointOfIntersection = Vector2D(lineOnRight.begin);
			foundPoint = true;

		}
		else if (xCoefficient == 0) // The lines do not intersect as their equations do not equate. Example: y=3x+1 & y=3x -> 3x=3x+1 -> 0=1, since 0!=1, the lines do not intersect.
		{
			possiblePoints.pointCount = 0;
			possiblePoints.pointsOfIntersection = nullptr;
			return possiblePoints;
		}
		else // Both lines have defined gradients and intersect.
		{
			x = rhs / xCoefficient; // Divide x coefficient by constant value: 4x=12 -> x=12/4 -> x=3
			y = l1.GetY(x); // Use x-value to get y using the linear function y=mx+c

			pointOfIntersection = Vector2D(x, y);
			foundPoint = true;
		}
	}

	if (foundPoint)
	{
		// The point doesnt lie on the defined line if the distance from the point to the start or end of any line is greater than the line's magnitude.
		if ((pointOfIntersection - l1.begin).SquareMagnitude() > (l1.LineVector().SquareMagnitude()) || (pointOfIntersection - l1.end).SquareMagnitude() > (l1.LineVector().SquareMagnitude()) || (pointOfIntersection - l2.begin).SquareMagnitude() > (l2.LineVector().SquareMagnitude()) || (pointOfIntersection - l2.end).SquareMagnitude() > (l2.LineVector().SquareMagnitude()))
		{
			possiblePoints.pointCount = 0;
		}
		else
		{
			possiblePoints.pointCount = 1;
			possiblePoints.pointsOfIntersection = new Vector2D[1]{ pointOfIntersection };
		}
	}
	else
	{
		possiblePoints.pointCount = 0;
		possiblePoints.pointsOfIntersection = nullptr;
	}

#ifdef DEBUG
	profile.PauseTimer();
#endif

	return possiblePoints;
}

IntersectionInfo Engine::Maths::CheckIntersection(Rect& r, Line& l)
{

#ifdef DEBUG
	auto profile = AlgorithmProfiler::GetInstance()->CreateProfile("CheckIntersection(Rect&, Line&)");
	profile.StartTimer();
#endif

	IntersectionInfo possiblePoints;

	IntersectionInfo temp;
	Line l2;
	// Check if each of the lines of the rectangle intersect with l. Add the points of intersection to possiblePoints and return it.
	l2 = r.Top();
	temp = CheckIntersection(l, l2);

	(possiblePoints) += (temp);

	l2 = r.Right();
	temp = CheckIntersection(l, l2);

	possiblePoints += temp;

	l2 = r.Bottom();
	temp = CheckIntersection(l, l2);

	possiblePoints += temp;

	l2 = r.Left();
	temp = CheckIntersection(l, l2);

	possiblePoints += temp;

#ifdef DEBUG
	profile.PauseTimer();
#endif

	return possiblePoints;

}

IntersectionInfo Engine::Maths::CheckIntersection(Rect& r1, Rect& r2)
{
#ifdef DEBUG
	auto profile = AlgorithmProfiler::GetInstance()->CreateProfile("CheckIntersection(Rect& r1, Rect& r2)");
	profile.StartTimer();
#endif
	Line* r2Lines = *r2.GetLines();

	IntersectionInfo possiblePoints;
	// Get points of intersection between this rectangle and every line that belongs to r2.
	for (size_t i = 0; i < 4; i++)
	{
		
		possiblePoints += CheckIntersection(r1, r2Lines[i]);
		
	}
	// finished with line array
	delete[] r2Lines;

#ifdef DEBUG
	profile.PauseTimer();
#endif

	return possiblePoints;

}

IntersectionInfo Engine::Maths::CheckIntersection(Line& l, Ellipse& e)
{
#ifdef DEBUG
	auto profile = AlgorithmProfiler::GetInstance()->CreateProfile("Engine::Maths::CheckIntersection(Line& l, Ellipse& e)");
	profile.StartTimer();
#endif
	IntersectionInfo info;
	std::vector<Vector2D> possiblePoints;
	ExpandedQuadraticEquation resultOfEquation;

	Line rotatedLine = Line::AddRotation(l, e.center, -e.rotation);

	float gradient = rotatedLine.Gradient();

	if (isnan(gradient))
	{
		int pointCount;
		int* points = nullptr;
		pointCount = (e.GetY(rotatedLine.begin.x, &points));

		for (size_t i = 0; i < pointCount; i++)
		{
			Vector2D point(rotatedLine.begin.x, points[i]);
			possiblePoints.push_back(point);
		}

		if (points)
			delete[] points;

	}
	else
	{
		float constantOffset = rotatedLine.ConstantOffset();
		constantOffset -= e.center.y;

		// a^2*b^2 = a^2(y-k)^2 + b^2(x-h)^2
		resultOfEquation = ((FactorisedQuadraticEquation(BinomialExpression(gradient, constantOffset, 1)).Expand()) * powf(e.radii.x, 2)) + ((FactorisedQuadraticEquation(BinomialExpression(1, -e.center.x, 1)).Expand()) * powf(e.radii.y, 2));
		// 0 = (a^2(y-k)^2 + b^2(x-h)^2) - a^2*b^2
		resultOfEquation.constant.coefficient -= powf(e.radii.x, 2)*powf(e.radii.y, 2);

		auto roots = resultOfEquation.Roots();

		if (roots.discriminant == 0)
		{
			possiblePoints.push_back(Vector2D(roots.root1, rotatedLine.GetY(roots.root1)));
		}
		else if (roots.discriminant > 0)
		{
			possiblePoints.push_back(Vector2D(roots.root1, rotatedLine.GetY(roots.root1)));
			possiblePoints.push_back(Vector2D(roots.root2, rotatedLine.GetY(roots.root2)));
		}
	}
		std::vector<Vector2D> pointsOfIntersection;

		for (size_t i = 0; i < possiblePoints.size(); i++)
		{
			if ((possiblePoints[i] - rotatedLine.begin).Magnitude() <= rotatedLine.LineVector().Magnitude() && (possiblePoints[i] - rotatedLine.end).Magnitude() <= rotatedLine.LineVector().Magnitude())
			{
				pointsOfIntersection.push_back(possiblePoints[i]);
			}
		}
	
		info.pointCount = pointsOfIntersection.size();

		if (pointsOfIntersection.size() == 0)
			info.pointsOfIntersection = nullptr;
		else
		{
			info.pointsOfIntersection = new Vector2D[info.pointCount];

			for (size_t i = 0; i < info.pointCount; i++)
			{
				info.pointsOfIntersection[i] = Vector2D::AddRotation(e.center, pointsOfIntersection[i], e.rotation);
			}

		}
	
#ifdef DEBUG
		profile.PauseTimer();
#endif

	return info;

}

IntersectionInfo Engine::Maths::CheckIntersection(Rect& r, Ellipse& e)
{

	IntersectionInfo info;

	Line* rectangleLines = *r.GetLines();

	for (size_t i = 0; i < 4; i++)
	{
		info += CheckIntersection(rectangleLines[i], e);
	}

	delete[] rectangleLines;


	return info;
}

IntersectionInfo Engine::Maths::CheckIntersection(Circle& c1, Circle& c2)
{
	IntersectionInfo info;

	if (c1 == c2) // Check if the circles are identical
	{
		info.identical = true;
		return info;
	}

	if ((c1.center - c2.center).Magnitude() < c1.radius + c2.radius && (c1.center!=c2.center)) // Must collide as distance between centers is <= than sum of radii
	{

		// Finding the radical line

		// (x-h)^2+(y-k)^2-r^2=0
		
		ExpandedQuadraticEquation xRes, yRes;

		FactorisedQuadraticEquation c1X, c1Y; // (x-h)^2 and (y-k)^2
		FactorisedQuadraticEquation c2X, c2Y;

		c1X = FactorisedQuadraticEquation(BinomialExpression(1,-c1.center.x, 2)); // (x-h)^2
		c1Y = FactorisedQuadraticEquation(BinomialExpression(1,-c1.center.y, 2)); // (y-k)^2

		c2X = FactorisedQuadraticEquation(BinomialExpression(1, -c2.center.x, 2)); // (x-h)^2
		c2Y = FactorisedQuadraticEquation(BinomialExpression(1, -c2.center.y, 2)); // (y-k)^2

		xRes = c1X.Expand() - c2X.Expand(); // coefficients of the 2nd degree will be zero always: (x-b)^2=(x-a)^ -> x^2-2xb-b^2=x^2-2xa-a^2 -> x^2-x^2...
		yRes = c1Y.Expand() - c2Y.Expand();

		ExpandedQuadraticEquation radicalLine;

		radicalLine.constant.coefficient = xRes.constant.coefficient + yRes.constant.coefficient; // 1) ax + b 2) cy + d | k = b-d
		radicalLine.constant.coefficient += -powf(c1.radius,2) + powf(c2.radius,2);
		radicalLine.x.coefficient = xRes.x.coefficient;
		radicalLine /= -yRes.x.coefficient; // ay = mx + c -> y = (mx+c) / a


		// Using the radical line to find x position of points of intersection.
		// Substitute y=mx+c into r^2=(x-h)^2+(y-h)^2
		// -> r^2=(x-h)^2+(mx+c-h)^2

		
		ExpandedQuadraticEquation circleEquatedToRadicalLine;
		// Check if radical line has a real gradient
		if ((!isnan(radicalLine.x.coefficient) && !isinf(radicalLine.x.coefficient)) && (!isnan(radicalLine.constant.coefficient) && !isinf(radicalLine.constant.coefficient)))
		{
			circleEquatedToRadicalLine = FactorisedQuadraticEquation(BinomialExpression(1, -c1.center.x, 2)).Expand() + FactorisedQuadraticEquation(BinomialExpression(radicalLine.x.coefficient, radicalLine.constant.coefficient - c1.center.y, 2)).Expand();
			circleEquatedToRadicalLine.constant.coefficient -= powf(c1.radius, 2);

			auto roots = circleEquatedToRadicalLine.Roots();

			if (roots.discriminant == 0) // This should never happen, but just in case we will return a root
			{
				info.pointCount = 1;

				float y = (radicalLine.x.coefficient * roots.root1) + radicalLine.constant.coefficient;

				info.pointsOfIntersection = new Vector2D[1]{ Vector2D(roots.root1, y) };
			}
			else
			{

				info.pointCount = 2;

				float y1 = 0, y2 = 0;
				y1 = (radicalLine.x.coefficient * roots.root1) + radicalLine.constant.coefficient; // Find the point on the line with the x position from the roots.
				y2 = (radicalLine.x.coefficient * roots.root2) + radicalLine.constant.coefficient;

				info.pointsOfIntersection = new Vector2D[2]{ Vector2D(roots.root1, y1), Vector2D(roots.root2, y2) };
			}
		}
		else
		{
			// If no real gradient, revert radical line back to linear form (y=x)
			radicalLine.constant.coefficient = xRes.constant.coefficient + yRes.constant.coefficient; // 1) ax + b 2) cy + d | k = b-d
			radicalLine.constant.coefficient += -powf(c1.radius, 2) + powf(c2.radius, 2);
			radicalLine.x.coefficient = xRes.x.coefficient;
			// Get x value
			float x = radicalLine.constant.coefficient / radicalLine.x.coefficient;
			// Get two yValues if not then do nothing
			int* yValues;				
			info.pointCount = c1.GetEllipse().GetY(x, &yValues);

			if (yValues)
			{
				if(info.pointCount == 2)
					info.pointsOfIntersection = new Vector2D[2]{ Vector2D(x,yValues[0]), Vector2D(x,yValues[1]) };
				else
					info.pointsOfIntersection = new Vector2D[1]{ Vector2D(x,yValues[0])};

				delete[] yValues;
			}
			
		}

	}
	else if ((c1.center - c2.center).Magnitude() == c1.radius + c2.radius && (c1.center != c2.center)) // Special case 1 point of intersection
	{
		Line c1c2 = Line(c1.center, c2.center);
		Vector2D v = Vector2D::Normalize(c1c2.LineVector());

		v *= c1.radius;

		info.pointCount = 1;

		Vector2D point = c1.center + v;

		info.pointsOfIntersection = new Vector2D[1]{ point };

	}
	else
	{
		info.pointCount = 0;
		info.pointsOfIntersection = nullptr;
	}

	return info;
}

IntersectionInfo Engine::Maths::CheckIntersection(Line& l, Circle& c)
{
	Ellipse e = c.GetEllipse();
	return Engine::Maths::CheckIntersection(l, e);
}

IntersectionInfo Engine::Maths::CheckIntersection(Rect& r, Circle& c)
{
	Ellipse e = c.GetEllipse();
	return Engine::Maths::CheckIntersection(r, e);
}