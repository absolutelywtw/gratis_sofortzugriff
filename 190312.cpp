//спасибо Каленюку И.В. за помощь

#include "pch.h"
#include <iostream>
#include <vector>																//библиотека по работе с векторами
#include <string>
using namespace std;

class Matrix
{
public:
	Matrix(int n_rows, int n_columns);						//объявление

	double &operator()(int row, int column);					//возвращается не копия, а ссылка, чтобы его можно было менять

	int nRows() const;
	int nColumns() const;

private:
	vector<double> el;
	int n_rows;																	//строки
	int n_columns;																//столбцы
};


Matrix::Matrix(int n_rows, int n_columns)										
	/*:
	n_rows(n_rows), n_columns(n_columns),
	el(n_rows * n_columns)
	*/
{
	if ( n_rows < 1 || n_columns < 1 )
		throw string("Wrong number of rows and columns");			//выкинуть ошибку
																				//this-> указатель на объект класса
	this->n_rows = n_rows;
	this->n_columns = n_columns;
	el.resize( n_rows * n_columns );
}

int Matrix::nRows() const
{
	return n_rows;
}

int Matrix::nColumns() const
{
	return n_columns;
}

double &Matrix::operator()(int row, int column)						//выражаем матрицу в виде вектора
{
	/*
	234
	567
	108

	(2,3,4,5,6,7,1,0,8)
	*/

	if (row < 0 || row >= n_rows)
		throw string("Wrong row index");
	if (column < 0 || column >= n_columns)
		throw string("Wrong column index");
	return el[n_columns * row + column];
}

Matrix add(Matrix m1, Matrix m2, int sign)						//костыль для сложения-вычитания
{
	Matrix result(m1.nRows(), m1.nColumns());
	for (int i = 0; i < m1.nRows(); i++)
	{
		for (int j = 0; j < m1.nColumns(); j++)
		{
			result(i, j) = m1(i, j) + sign * m2(i, j);
		}
	}
	return result;
}

Matrix operator+(Matrix m1, Matrix m2)							//сложение матриц
{
	return add(m1, m2, +1);
}

Matrix operator-(Matrix m1, Matrix m2)							//вычитание матриц
{
	return add(m1, m2, -1);
}

Matrix operator*(Matrix m, double value)						//умножение матрицы на константу
{
	Matrix result(m.nRows(), m.nColumns());
	for (int i = 0; i < m.nRows(); i++)
	{
		for (int j = 0; j < m.nColumns(); j++)
		{
			result(i, j) = value * m(i, j);
		}
	}
	return result;
}

Matrix operator*(double value, Matrix m)						//умножение константы на матрицу
{
	return m * value;
}

Matrix operator*(Matrix m1, Matrix m2)							//умножение матрицы на матрицу
{
	Matrix result(m1.nRows(), m2.nColumns());
	for (int i = 0; i < m1.nRows(); i++)
	{
		
		for (int j = 0; j < m2.nColumns(); j++)
		{
			double tmp = 0;
			for (int k = 0; k < m2.nRows(); k++)
			{
				tmp += m1(i, k) * m2(k, j);
			}
			result(i, j) = tmp;
		}
	}
	return result;
}

ostream &operator<<(ostream &out, Matrix m)						//вывод матрицы
{
	for (int i = 0; i < m.nRows(); i++)
	{
		for (int j = 0; j < m.nColumns(); j++)
		{
			out << m(i, j) << "";
		}
		out << endl;
	}
	return out;
}

double det(Matrix m)
{
	for (int i = 0; i < m.nRows() - 1; i++)
	{
		for (int j = i + 1; j < m.nRows(); j++)
		{
			double coeff = m(j, i) / m(i, i);
			for (int k = i; k < m.nColumns(); k++)
			{
				m(j, k) = m(j, k) - coeff * m(i, k);
			}

		}


	}

	double result = 1;
	for (int i = 0; i < m.nRows(); i++)
	{
		result *= m(i, i);
	}
	return result;

}

//метод Жордана-Гаусса
//A*X=B

Matrix jordan_gauss(Matrix a, Matrix b)
{
	/*
	1)
	723
	345
	410

	2)
	723
	0##
	0##
	
	*/



	for (int i = 0; i < a.nRows() - 1; i++)						//ведущая строка
	{
		for (int j = i + 1; j < a.nRows; j++)					//текущая строка
		{
			double coeff = a(j, i) / a(i, i);				//коэффициент
			for (int k = i; k < a.nColumns(); k++)
			{
				a(j, k) = a(j, k) - coeff * a(i, k);
			}

		}


	}

	for (int i = a.nRows() - 1; i >= 1; i--)
	{
		for (int j = i - 1; j >= 0; j--)
		{
			double coeff = a(j, i) / a(i, i);
			a(j, i) = a(j, i) - coeff * a(i, i);
			b(j, 0) = b(j, 0) - coeff * b(i, i);
		}
	}

	for (int i = 0; i < a.nRows(); i++)
	{
		b(i, 0) = b(i, 0) / a(i, i);
		a(i, i) = 1;
	}

	return b;		

	//X = jordan_gauss(a, b)
	//для проверки считаем A*X, должно получиться B
}



int main()
{

	//выявление ошибок
	/*
	try
	{
		Matrix m1(2, 2);
		m1(0, 0) = 1;
		m1(0, 1) = 2;
		m1(1, 0) = 3;
		m1(1, 1) = 4;

		Matrix m2(2, 2);
		m2(0, 0) = 5;
		m2(0, 1) = 6;
		m2(1, 0) = 7;
		m2(1, 1) = 8;

		Matrix m3 = m1 + m2;

		cout << m3(1, 0) << endl;
	}
	catch (string s)
	{
		cout << s << endl;
	}

	*/
	
	
	return 0;
}
