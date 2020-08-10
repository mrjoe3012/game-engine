#include "Matrix.h"

using Engine::Maths::Matrix;

template<>
Matrix<int>::Matrix(unsigned int height, unsigned int width)
	:
	height(height),
	width(width)
{
	if (height == 0 || width == 0)
		throw std::runtime_error("A Matrix cannot have a height or width of 0");
	else
	{
		values = new int[height*width]{ 0 };
	}
}

template<>
Matrix<short int>::Matrix(unsigned int height, unsigned int width)
	:
	height(height),
	width(width)
{
	if (height == 0 || width == 0)
		throw std::runtime_error("A Matrix cannot have a height or width of 0");
	else
	{
		values = new short int[height*width]{ 0 };
	}
}

template<>
Matrix<unsigned short int>::Matrix(unsigned int height, unsigned int width)
	:
	height(height),
	width(width)
{
	if (height == 0 || width == 0)
		throw std::runtime_error("A Matrix cannot have a height or width of 0");
	else
	{
		values = new unsigned short int[height*width]{ 0 };
	}
}


template<>
Matrix<long int>::Matrix(unsigned int height, unsigned int width)
	:
	height(height),
	width(width)
{
	if (height == 0 || width == 0)
		throw std::runtime_error("A Matrix cannot have a height or width of 0");
	else
	{
		values = new long int[height*width]{ 0 };
	}
}

template<>
Matrix<unsigned long int>::Matrix(unsigned int height, unsigned int width)
	:
	height(height),
	width(width)
{
	if (height == 0 || width == 0)
		throw std::runtime_error("A Matrix cannot have a height or width of 0");
	else
	{
		values = new unsigned long int[height*width]{ 0 };
	}
}

template<>
Matrix<long long int>::Matrix(unsigned int height, unsigned int width)
	:
	height(height),
	width(width)
{
	if (height == 0 || width == 0)
		throw std::runtime_error("A Matrix cannot have a height or width of 0");
	else
	{
		values = new long long int[height*width]{ 0 };
	}
}

template<>
Matrix<unsigned long long int>::Matrix(unsigned int height, unsigned int width)
	:
	height(height),
	width(width)
{
	if (height == 0 || width == 0)
		throw std::runtime_error("A Matrix cannot have a height or width of 0");
	else
	{
		values = new unsigned long long int[height*width]{ 0 };
	}
}

template<>
Matrix<unsigned int>::Matrix(unsigned int height, unsigned int width)
	:
	height(height),
	width(width)
{
	if (height == 0 || width == 0)
		throw std::runtime_error("A Matrix cannot have a height or width of 0");
	else
	{
		values = new unsigned int[height*width]{ 0 };
	}
}

template<>
Matrix<float>::Matrix(unsigned int height, unsigned int width)
	:
	height(height),
	width(width)
{
	if (height == 0 || width == 0)
		throw std::runtime_error("A Matrix cannot have a height or width of 0");
	else
	{
		values = new float[height*width]{ 0.0f };
	}
}

template<>
Matrix<double>::Matrix(unsigned int height, unsigned int width)
	:
	height(height),
	width(width)
{
	if (height == 0 || width == 0)
		throw std::runtime_error("A Matrix cannot have a height or width of 0");
	else
	{
		values = new double[height*width]{ 0.0 };
	}
}

template<>
Matrix<long double>::Matrix(unsigned int height, unsigned int width)
	:
	height(height),
	width(width)
{
	if (height == 0 || width == 0)
		throw std::runtime_error("A Matrix cannot have a height or width of 0");
	else
	{
		values = new long double[height*width]{ 0.0 };
	}
}