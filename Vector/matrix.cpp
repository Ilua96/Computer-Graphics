#include "vector_matrix.h"
#include <iostream>
#include <sstream>
#include <cmath>
#define PI 3.14159265

mat4::mat4(float X1, float Y1, float Z1, float W1, float X2, float Y2, float Z2, float W2, 
	float X3, float Y3, float Z3, float W3, float X4, float Y4, float Z4, float W4)
{
	matrix[0][0] = X1;
	matrix[0][1] = Y1;
	matrix[0][2] = Z1;
	matrix[0][3] = W1;
	matrix[1][0] = X2;
	matrix[1][1] = Y2;
	matrix[1][2] = Z2;
	matrix[1][3] = W2;
	matrix[2][0] = X3;
	matrix[2][1] = Y3;
	matrix[2][2] = Z3;
	matrix[2][3] = W3;
	matrix[3][0] = X4;
	matrix[3][1] = Y4;
	matrix[3][2] = Z4;
	matrix[3][2] = Z4;
	matrix[3][3] = W4;
}

mat4::mat4()
{
	memset(matrix, 0, 16 * sizeof(float));
}

mat4::mat4(float* source)
{
	memcpy(matrix, source, 16 * sizeof(float));
}

mat4::mat4(float source[4][4])
{
	memcpy(matrix, source, 16 * sizeof(float));
}

float* mat4::operator[](int i)
{
	return matrix[i];
}

void mat4::identity()
{
	*this = mat4();
	for (int i = 0; i < 4; ++i)
	{
		matrix[i][i] = 1;
	}
}

mat4 mat4::transpose()
{
	mat4 mat;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			mat[i][j] = matrix[j][i];
		}
	}
	return mat;
}


float mat4::det3(int row, int col)
{
	float arr[3][3];
	int a_i = 0;
	for (int i = 0; i < 4; ++i)
	{
		int a_j = 0;
		if (i != row)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (j != col)
				{
					arr[a_i][a_j] = matrix[i][j];
					++a_j;
				}
			}
			++a_i;
		}
	}
	return (arr[0][0] * arr[1][1] * arr[2][2] + arr[0][1] * arr[1][2] * arr[2][0] + arr[0][2] * arr[1][0] * arr[2][1] -
		arr[0][2] * arr[1][1] * arr[2][0] - arr[0][0] * arr[1][2] * arr[2][1] - arr[0][1] * arr[1][0] * arr[2][2]);
}

float mat4::det()
{
	float ans;
	ans = matrix[0][0] * det3(0, 0);
	ans -= matrix[0][1] * det3(0, 1);
	ans += matrix[0][2] * det3(0, 2);
	ans -= matrix[0][3] * det3(0, 3);
	return ans;
}


mat4 mat4::inverse()
{
	float deter = det();
	if (deter == 0)
	{
		throw runtime_error("Determinant = 0");
	}
	mat4 al_mat;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			al_mat[i][j] = pow(-1, i + j) * det3(i, j);
		}
	}
	return 1/deter * al_mat.transpose();
}

mat4 mat4::operator+(mat4 &other)
{
	mat4 ans;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			ans[i][j] = matrix[i][j] + other[i][j];
		}
	}
	return ans;
}

mat4 mat4::operator-(mat4 &other)
{
	mat4 ans;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			ans[i][j] = matrix[i][j] - other[i][j];
		}
	}
	return ans;
}

mat4 mat4::operator*(float a)
{
	mat4 ans;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			ans[i][j] = matrix[i][j] * a;
		}
	}
	return ans;
}

mat4 operator*(float a, mat4 &mat)
{
	return mat * a;
}

mat4 mat4::operator*(mat4 &other)
{
	mat4 ans;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			for (int k = 0; k < 4; ++k)
			{
				ans[i][j] += matrix[i][k] * other[k][j];
			}
		}
	}
	return ans;
}

vec4 mat4::operator*(vec4 &vec) 
{
	vec4 ans;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			ans[i] += matrix[i][j] * vec[j];
		}
	}
	return ans;
}

mat4 mat4::scale(vec4 & vec)
{
	mat4 scale_mat;
	scale_mat[0][0] = vec.x;
	scale_mat[1][1] = vec.y;
	scale_mat[2][2] = vec.z;
	scale_mat[3][3] = 1;
	return scale_mat * (*this);
}

mat4 mat4::rotate(float angle,vec4 axis)
{
	angle = PI / 180 * angle;
	axis.normalize_in_place();
	float c = cos(angle);
	float mc = 1 - c;
	float s = sin(angle);
	mat4 tmp(c + pow(axis.x, 2) * mc,			axis.x * axis.y * mc - axis.z * s, axis.x * axis.z * mc + axis.y * s, 0.0f,
			 axis.y * axis.x * mc + axis.z * s, c + pow(axis.y, 2) * mc,		   axis.y * axis.z * mc - axis.x * s, 0.0f,
			 axis.z * axis.x * mc - axis.y * s, axis.z * axis.y * mc + axis.x * s, c + pow(axis.z, 2) * mc,			  0.0f,
			 0.0f,								0.0f,							   0.0f,							  1.0f);
	return (tmp * (*this)).transpose();
}

mat4 mat4::translate(vec4 & vec)
{
	mat4 tmp;
	tmp.identity();
	tmp[0][3] = vec.x;
	tmp[1][3] = vec.y;
	tmp[2][3] = vec.z;
	return tmp * (*this);
}

mat4 mat4::perspective(float fovy, float aspect, float near, float far)
{
	fovy = PI / 180 * fovy;
	float left, right, bottom, top;
	top = near * tan(fovy / 2);
	bottom = -top;
	right = top * aspect;
	left = -right;
	mat4 tmp;
	tmp[0][0] = (2 * near) / (right - left);
	tmp[0][2] = (right + left) / (right - left);
	tmp[1][1] = (2 * near) / (top - bottom);
	tmp[1][2] = (top + bottom) / (top - bottom);
	tmp[2][2] = -(far + near) / (far - near);
	tmp[2][3] = -(2 * far * near) / (far - near);
	tmp[3][2] = -1;
	return tmp * (*this);
}

mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
{
	mat4 tmp;
	tmp[0][0] = 2.0f / (right - left);
	tmp[1][1] = 2.0f / (top - bottom);
	tmp[2][2] = -2.0f / (far - near);
	tmp[3][3] = 1.0f;
	tmp[0][3] = -(right + left) / (right - left);
	tmp[1][3] = -(top + bottom) / (top - bottom);
	tmp[2][3] = -(far + near) / (far - near);
	return tmp * (*this);
}

string mat4::str()
{
	stringstream s;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			s << matrix[i][j] << " ";
		}
		s << endl;
	}
	return s.str();
}