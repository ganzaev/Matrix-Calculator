#include<iostream>
#include<fstream>
#include<string>

template < typename T >
class matrix4x4
{
public:
	using value_type = T;
	using reference = T&;
	using pointer = T*;
	using const_pointer = T const*;
	using size_type = std::size_t;

public:
	static size_type const size = 4;

public:

	matrix4x4() { std::memset(matrix_, 0, sizeof(matrix_)); }
	matrix4x4(matrix4x4<T> const&) = default;

	matrix4x4<T>& operator=(matrix4x4<T> const& rhs)
	{
		std::memcpy(matrix_, rhs.matrix_, sizeof(matrix_));
		return *this;
	}

	const_pointer operator[](std::size_t index) const { return matrix_[index]; }
	pointer operator[](std::size_t index) { return matrix_[index]; }

	matrix4x4<T>& operator+=(matrix4x4<T> const& rhs)
	{
		for (std::size_t i = 0; i < matrix4x4<T>::size; ++i) {
			for (std::size_t j = 0; j < matrix4x4<T>::size; ++j) {
				matrix_[i][j] += rhs[i][j];
			}
		}
		return *this;
	}

	matrix4x4<T>& operator-=(matrix4x4<T> const& rhs)
	{
		return *this;
	}

	matrix4x4<T>& operator*=(matrix4x4<T> const& rhs)
	{
		for (std::size_t i = 0; i < matrix4x4<T>::size; ++i) {
			for (std::size_t j = 0; j < matrix4x4<T>::size; ++j) {
				matrix_[i][j] *= rhs[i][j];
			}
		}
		return *this;
	}

private:
	T matrix_[matrix4x4<T>::size][matrix4x4<T>::size];
};

template < typename T >
matrix4x4<T> operator+(matrix4x4<T> const& lhs, matrix4x4<T> const& rhs)
{
	auto temp = lhs;
	return temp += rhs;
}

template < typename T >
matrix4x4<T> operator-(matrix4x4<T> const& lhs, matrix4x4<T> const& rhs)
{
	return matrix4x4<T>();
}

template < typename T >
matrix4x4<T> operator*(matrix4x4<T> const& lhs, matrix4x4<T> const& rhs)
{
	auto temp = lhs;
	return temp *= rhs;
}

template < typename T >
std::istream& operator >> (std::istream& is, matrix4x4<T>& matrix)
{
	for (std::size_t x = 0; x < 4; ++x) {
		for (std::size_t y = 0; y < 4; ++y) {
			is >> matrix[x][y];
		}
	}
	return is;
}

template < typename T >
std::ostream& operator<<(std::ostream& os, matrix4x4<T> const& matrix)
{
	for (std::size_t x = 0; x < 4; ++x) {
		for (std::size_t y = 0; y < 4; ++y) {
			os << matrix[x][y] << " ";
		}
		os << std::endl;
	}
	return os;
}

int main()
{
	matrix4x4<int> matrices[3];

	{
		std::ifstream file("file.txt");
		if (!file) {
			return -1;
		}

		file >> matrices[0] >> matrices[1];
	}

	std::cout << "Matrix 0:" << std::endl << matrices[0] << "Matrix 1:" << std::endl << matrices[1];
	matrices[2] = matrices[0] * matrices[1];
	std::cout << "Matrices addition: " << std::endl << matrices[2] << std::endl;
	return 0;
}