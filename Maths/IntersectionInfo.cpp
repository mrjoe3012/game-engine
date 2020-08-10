#include "IntersectionInfo.h"

using Engine::Maths::IntersectionInfo;

IntersectionInfo::IntersectionInfo()
	:
	identical(false),
	pointCount(0),
	pointsOfIntersection(nullptr)
{

}

IntersectionInfo::IntersectionInfo(const IntersectionInfo& rhs)
{
	this->identical = rhs.identical;
	this->pointCount = rhs.pointCount;
	this->pointsOfIntersection = nullptr;
	if (pointCount > 0)
	{
		this->pointsOfIntersection = new Vector2D[pointCount];
		memcpy(this->pointsOfIntersection, rhs.pointsOfIntersection, sizeof(Vector2D)*pointCount);
	}
}

IntersectionInfo::~IntersectionInfo()
{
	if (pointsOfIntersection)
		delete[] pointsOfIntersection;
}

std::string IntersectionInfo::ToString() const
{
	std::string output("IntersectionInfo { identical: " + std::to_string(identical) + " pointsOfIntersection: ");

	for (size_t i = 0; i < pointCount; i++)
	{
		output += std::string("\n" + (pointsOfIntersection[i]).ToString());
	}
	output += std::string(" }");
	return output;
}

std::ostream& Engine::Maths::operator<<(std::ostream& os, const IntersectionInfo& const obj)
{
	os << obj.ToString();
	return os;
}

IntersectionInfo IntersectionInfo::operator+(IntersectionInfo& rhs)
{
	IntersectionInfo result;
	result.pointCount = rhs.pointCount + pointCount;
	if (result.pointCount == 0)
		result.pointsOfIntersection = nullptr;
	else
	{
		result.pointsOfIntersection = new Vector2D[result.pointCount];
		delete[] result.pointsOfIntersection;
	}
	int index = 0, index2 = 0; 
	for (; index < pointCount; index++)
	{
		result.pointsOfIntersection[index] = pointsOfIntersection[index];
	}
	for (; index2 < rhs.pointCount; index++, index2++)
	{
		result.pointsOfIntersection[index] = rhs.pointsOfIntersection[index2];
	}

	return result;
}

void IntersectionInfo::operator+=(const IntersectionInfo& rhs)
{
	int newLength = pointCount + rhs.pointCount;

	Vector2D* points = nullptr;

	if(newLength > 0)
		points = new Vector2D[newLength];
		
	int i = 0, j = 0;

	for (; i < pointCount; i++)
	{
		points[i] = this->pointsOfIntersection[i];
	}
	for (; j < rhs.pointCount; i++,j++)
	{
		points[i] = rhs.pointsOfIntersection[j];
	}
	
	if (this->pointCount > 0)
		delete[] this->pointsOfIntersection;

	this->pointCount = newLength;
	this->pointsOfIntersection = points;
}

void IntersectionInfo::operator=(const IntersectionInfo& rhs)
{

	if (pointsOfIntersection)
		delete[] pointsOfIntersection;

	pointCount = rhs.pointCount;
	pointsOfIntersection = new Vector2D[pointCount];
	
	if (pointCount > 0)
		memcpy(this->pointsOfIntersection, rhs.pointsOfIntersection, sizeof(Vector2D)*pointCount);

}