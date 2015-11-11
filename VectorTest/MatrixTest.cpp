#include "gtest/gtest.h"
#include <iostream>
#include <Eigen/Dense>
#include "vector_matrix.h"
#include <cmath>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Eigen;

void CopyArrayInMatrix(Matrix4f& mat, float* arr)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			mat(i, j) = arr[4 * i + j];
		}
	}
}

class TestMat4 : public ::testing::Test
{
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
protected:
	mat4 my_mat_1;
	Matrix4f eigen_mat_1;
	float source_1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
	mat4 my_mat_2;
	Matrix4f eigen_mat_2;
	float source_2[16] = { -11.123f, 2125.6782874f, 3.00003f, 4.125f, -535.32f, 6, 70, 886.87f, 9, 0.00400123f, 11784.1251235f, 1212.14767f, 13.2367f, 123544, 15.32643264f, 0.1246325f };
	void SetUp()
	{		
		my_mat_1 = mat4(source_1);
		CopyArrayInMatrix(eigen_mat_1, source_1);
		my_mat_2 = mat4(source_2);
		CopyArrayInMatrix(eigen_mat_2, source_2);
	}
};

void TestValues(mat4& mat, Matrix4f& e_mat)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			EXPECT_FLOAT_EQ(mat[i][j], e_mat(i, j));
		}
	}
}

void TestValues(mat4& mat, glm::mat4& g_mat)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			EXPECT_FLOAT_EQ(mat[i][j], g_mat[i][j]);
		}
	}
}

void TestValues(mat4& mat, float* arr)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			EXPECT_FLOAT_EQ(mat[i][j], arr[4 * i + j]);
		}
	}
}

void TestValues(vec4& vec, VectorXf& e_vec)
{
	for (int i = 0; i < 4; ++i)
	{
		EXPECT_FLOAT_EQ(vec[i], e_vec[i]);
	}
}

TEST(Mat4, Init)
{
	float arr[16] = { 1, 2, 3, 4, 2, 3, 4, 5, 3, 4, 5, 6, 4, 5, 6, 7 };
	mat4 my_mat(1, 2, 3, 4, 2, 3, 4, 5, 3, 4, 5, 6, 4, 5, 6, 7);
	TestValues(my_mat, arr);
}

TEST(Mat4, InitByZeroes)
{
	float arr[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	mat4 my_mat;
	TestValues(my_mat, arr);
}

TEST(Mat4, InitFromArray)
{
	float arr[16] = {1, 2, 3, 4, 2, 3, 4, 5, 3, 4, 5, 6, 4, 5, 6, 7};
	mat4 my_mat(arr);
	TestValues(my_mat, arr);
}

TEST(Mat4, InitFrom2XArray)
{
	float source[4][4] = { {1, 2, 3, 4}, {2, 3, 4, 5}, {3, 4, 5, 6}, {4, 5, 6, 7} };
	mat4 my_mat(source);
	TestValues(my_mat, *source);
}

TEST(Mat4, Identity)
{
	mat4 my_mat;
	my_mat.identity();
	float arr[4][4] = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} };
	TestValues(my_mat, *arr);
}

TEST_F(TestMat4, Transpose)
{
	TestValues(my_mat_1.transpose(), (Matrix4f)(eigen_mat_1.transpose()));
}

TEST_F(TestMat4, Determinant)
{
	EXPECT_FLOAT_EQ(my_mat_1.det(), eigen_mat_1.determinant());
	EXPECT_FLOAT_EQ(my_mat_2.det(), eigen_mat_2.determinant());
}

TEST_F(TestMat4, Inverse)
{	
	EXPECT_THROW(my_mat_1.inverse(), runtime_error);
	TestValues(my_mat_2.inverse(), (Matrix4f)(eigen_mat_2.inverse()));
}

TEST_F(TestMat4, Add)
{
	TestValues(my_mat_1 + my_mat_1, (Matrix4f)(eigen_mat_1 + eigen_mat_1));
	TestValues(my_mat_1 + my_mat_2, (Matrix4f)(eigen_mat_1 + eigen_mat_2));
	TestValues(my_mat_2 + my_mat_2, (Matrix4f)(eigen_mat_2 + eigen_mat_2));
	TestValues(my_mat_2 + my_mat_1, (Matrix4f)(eigen_mat_2 + eigen_mat_1));
}

TEST_F(TestMat4, Sub)
{
	TestValues(my_mat_1 - my_mat_1, (Matrix4f)(eigen_mat_1 - eigen_mat_1));
	TestValues(my_mat_1 - my_mat_2, (Matrix4f)(eigen_mat_1 - eigen_mat_2));
	TestValues(my_mat_2 - my_mat_2, (Matrix4f)(eigen_mat_2 - eigen_mat_2));
	TestValues(my_mat_2 - my_mat_1, (Matrix4f)(eigen_mat_2 - eigen_mat_1));
}

TEST_F(TestMat4, MultScalar)
{
	TestValues(my_mat_1 * 3, (Matrix4f)(eigen_mat_1 * 3));
	TestValues(1124.869f * my_mat_1, (Matrix4f)(1124.869f * eigen_mat_1));
	TestValues(my_mat_2 * -34.36f, (Matrix4f)(eigen_mat_2 * -34.36f));
	TestValues(-34.36f * my_mat_2, (Matrix4f)(eigen_mat_2 * -34.36f));
}

TEST_F(TestMat4, Mult)
{
	TestValues(my_mat_1 * my_mat_1, (Matrix4f)(eigen_mat_1 * eigen_mat_1));
	TestValues(my_mat_1 * my_mat_2, (Matrix4f)(eigen_mat_1 * eigen_mat_2));
	TestValues(my_mat_2 * my_mat_2, (Matrix4f)(eigen_mat_2 * eigen_mat_2));
	TestValues(my_mat_2 * my_mat_1, (Matrix4f)(eigen_mat_2 * eigen_mat_1));
}

TEST_F(TestMat4, MultVector)
{
	vec4 my_vec(12.35f, -2145.1234f, 1254.125321f, 5.0f);
	Vector4f eigen_vec(12.35f, -2145.1234f, 1254.125321f, 5.0f);
	TestValues(my_mat_1 * my_vec, (VectorXf)(eigen_mat_1 * eigen_vec));
	TestValues(my_mat_2 * my_vec, (VectorXf)(eigen_mat_2 * eigen_vec));
}

TEST_F(TestMat4, Translate)
{
	glm::mat4 g_mat;
	mat4 my_mat;
	my_mat.identity();
	g_mat = glm::translate(g_mat, glm::vec3(-13.5f, 56.0f, 1.0f));
	my_mat = my_mat.translate(vec4(-13.5f, 56.0f, 1.0f)).transpose();
	TestValues(my_mat, g_mat);
}

TEST_F(TestMat4, Rotate)
{
	glm::mat4 g_mat, g_mat_1;
	mat4 my_mat;
	my_mat.identity();
	g_mat = glm::rotate(g_mat, glm::radians(-67.3f), glm::vec3(-13.5f, 56.0f, 1.0f));
	my_mat = my_mat.rotate(-67.3f, vec4(-13.5f, 56.0f, 1.0f));
	TestValues(my_mat, g_mat);
	my_mat.identity();
	g_mat_1 = glm::rotate(g_mat_1, glm::radians(160.0f), glm::vec3(3.0f, -156.0f, 123.044f));
	my_mat = my_mat.rotate(160.0f, vec4(3.0f, -156.0f, 123.044f));
	TestValues(my_mat, g_mat_1);
}

TEST_F(TestMat4, Perspective)
{
	glm::mat4 g_mat;
	mat4 my_mat;
	my_mat.identity();
	g_mat = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.1f, 200.0f);
	my_mat = my_mat.perspective(60.0f, 800.0f / 600.0f, 0.1f, 200.0f).transpose();
	TestValues(my_mat, g_mat);
}


TEST_F(TestMat4, Orthographic)
{
	glm::mat4 g_mat;
	mat4 my_mat;
	my_mat.identity();
	g_mat = glm::ortho(-200.0f, 800.0f, -150.0f, 600.0f, 0.1f, 300.0f);
	my_mat = my_mat.orthographic(-200.0f, 800.0f, -150.0f, 600.0f, 0.1f, 300.0f).transpose();
	TestValues(my_mat, g_mat);
}