#pragma region Constructors and Destructor

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& rhs)
	:
	Matrix(rhs.height, rhs.width)
{
	memcpy(values, rhs.values, sizeof(T)*height*width);
}

template<typename T>
Matrix<T>::Matrix(unsigned int height, unsigned int width)
	:
	height(height),
	width(width)
{
	if (height == 0 || width == 0)
		throw std::runtime_error("A Matrix cannot have a height or width of 0");
	else
	{
		values = new T[height*width];
	}
}

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
		values = new int[height*width]{0};
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

template<typename T>
Matrix<T>::Matrix(unsigned int n)
	:
	Matrix<T>(n, n)
{
}

template<typename T>
Matrix<T>::Matrix(unsigned int height, unsigned int width, std::initializer_list<T> init)
	:
	Matrix(height,width)
{
	size_t row = 0, counter = 1;

	for (size_t i = 0; i < init.size() && i < (width*height); i++, counter++)
	{
		if (counter > this->width)
		{
			counter = 1;
			row++;
		}

		(this->operator[](row))[counter - 1] = *(init.begin() + i);
	}
}

template<typename T>
Matrix<T>::~Matrix()
{
	delete[] values;
}

#pragma endregion

#pragma region Accessors

template<typename T>
unsigned int Matrix<T>::Height() const
{
	return height;
}

template<typename T>
unsigned int Matrix<T>::Width() const
{
	return width;
}

template<typename T>
std::vector<T*> Matrix<T>::GetColumn(unsigned int col) const
{
	if (col >= width)
		throw std::out_of_range("Column index out of range.");
	else
	{
		std::vector<T
*> result;

		for (size_t i = 0; i < height; i++)
		{
			result.push_back(&(this->operator[](i)[col]));
		}
		return result;
	}
}

template<typename T>
std::vector<T*> Matrix<T>::GetRow(unsigned int row) const
{
	if (row >= height)
		throw std::out_of_range("Row index out of range.");
	else
	{
		std::vector<T*> result;

		for (size_t i = 0; i < width; i++)
		{
			result.push_back(&(this->operator[](row)[i]));
		}
		return result;
	}
}

#pragma endregion

#pragma region Operators

template<typename T>
void Matrix<T>::operator=(const Matrix<T>& rhs)
{
	width = rhs.width;
	height = rhs.height;

	delete[] values;
	values = new T[width*height];

	memcpy(values, rhs.values, sizeof(T)*width*height);
}

template<typename T>
T* Matrix<T>::operator[](unsigned int row) const
{
	if (row >= height)
		throw std::out_of_range("Row index out of range.");

	return (values + (width*row));
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& rhs) const
{
	if (rhs.width != width || rhs.height != height)
		throw std::runtime_error("Matrices are incompatible for addition.");
	else
	{
		Matrix<T> res = *this;

		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0; j < width; j++)
			{
				res[i][j] += rhs[i][j];
			}
		}
		return res;
	}
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& rhs) const
{
	if (rhs.width != width || rhs.height != height)
		throw std::runtime_error("Matrices are incompatible for subtraction.");
	else
	{
		Matrix<T> res = *this;

		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0; j < width; j++)
			{
				res[i][j] -= rhs[i][j];
			}
		}
		return res;
	}
}

template<typename T>
void Matrix<T>::operator+=(const Matrix<T>& rhs)
{
	Matrix<T> res = *this + rhs;
	memcpy(values, res.values, sizeof(T)*width*height);
}

template<typename T>
void Matrix<T>::operator-=(const Matrix<T>& rhs)
{
	Matrix<T> res = *this - rhs;
	memcpy(values, res.values, sizeof(T)*width*height);
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs) const
{
	if (this->width != rhs.height)
		throw std::runtime_error("Cannot only multiply matrices when the width of m1 = the height of m2. Where m1 * m2.");
	else
	{
		Matrix<T> result = Matrix<T>(this->height, rhs.width);

		for (size_t i = 0; i < this->height; i++)
		{

			auto row = GetRow(i);

			for (size_t j = 0; j < rhs.width; j++)
			{
				int value = 0;
				auto column = rhs.GetColumn(j);

				for (size_t k = 0; k < row.size(); k++)
				{
					value += ((*row[k]) * (*column[k]));
				}

				result[i][j] = value;

			}

		}

		return result;
	}
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T& rhs) const
{
	Matrix<T> res = *this;

	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			res[i][j] *= rhs;
		}
	}
	return res;
}

template<typename T>
Matrix<T> Matrix<T>::operator/(const T& rhs) const
{
	Matrix<T> res = *this;

	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			res[i][j] /= rhs;
		}
	}
	return res;
}

template<typename T>
void Matrix<T>::operator*=(const Matrix<T>& rhs)
{
	Matrix<T> result = (*this)*rhs;
	memcpy(values, result.values, sizeof(T)*width*height);
}

template<typename T>
void Matrix<T>::operator*=(const T& rhs)
{
	Matrix<T> result = (*this)*rhs;
	memcpy(values, result.values, sizeof(T)*width*height);
}

template<typename T>
void Matrix<T>::operator/=(const T& rhs)
{
	Matrix<T> result = (*this) / rhs;
	memcpy(this->values, result.values, sizeof(T)*width*height);
}

#pragma endregion

#pragma region Properties

template<typename T>
Matrix<T> Matrix<T>::Identity(unsigned int n)
{
	Matrix<T> identity = Matrix<T>(n, n);

	for (size_t i = 0, j = 0; i < n; i++,j++)
	{
		identity[i][j] = static_cast<T>(1);
	}

	return identity;
}

template<typename T>
int Matrix<T>::Determinant() const
{
	if (height != width)
		throw std::runtime_error("Cannot calculate the determinant of a non-square matrix!");
	else
	{

		int determinant = 0;
		int sign = 1;

		if (height == 1)
			determinant = operator[](0)[0];
		else if (height == 2)
			determinant = (operator[](0)[0] * operator[](1)[1]) - (operator[](0)[1] * operator[](1)[0]);
		else
		{
			for (size_t i = 0; i < width; i++) // note height == width!
			{
				int coefficient = operator[](0)[i];
				Matrix<T> subMatrix = Matrix<T>(height-1,width-1);

				for (size_t j = 1; j < height; j++)
				{
					auto row = GetRow(j);
					row.erase(row.begin() + i);

					for (size_t k = 0; k < row.size(); k++)
					{
						subMatrix[j - 1][k] = *row[k];
					}
				}

				determinant += sign * (subMatrix.Determinant()*coefficient);
				sign *= -1;
			}
		}
		return determinant;
	}
}

template<typename T>
Matrix<T> Matrix<T>::Adjugate() const
{
	if (height != width)
		throw std::runtime_error("Cannot find the adjugate of a non-square matrix.");
	else
	{
		Matrix<T> adjugate = Matrix<T>(height, width);

		if (height == 1)
			adjugate[0][0] = 1;
		else if (height == 2)
		{
			adjugate[0][0] = operator[](1)[1];
			adjugate[1][1] = operator[](0)[0];
			adjugate[0][1] = -operator[](0)[1];
			adjugate[1][0] = -operator[](1)[0];
		}
		else
		{
			int sign = 1;
			for (size_t i = 0; i < height; i++)
			{
				for (size_t j = 0; j < width; j++)
				{
					Matrix<T> subMatrix = Matrix<T>(height - 1, width - 1);
					for (size_t rowIndex = 0, k = 0; k < height; k++)
					{
						if (k != i)
						{
							std::vector<T*> row = GetRow(k);

							row.erase(row.begin() + j);

							for (size_t l = 0; l < row.size(); l++)
							{
								subMatrix[rowIndex][l] = *row[l];
							}

							rowIndex++;
						}

						adjugate[j][i] = sign * subMatrix.Determinant();
					}
					sign *= -1;
				}
			}
		}
		return adjugate;
	}
}

template<typename T>
Matrix<T> Matrix<T>::Inverse() const
{
	return Adjugate()/Determinant();
}

#pragma endregion