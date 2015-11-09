#include "gtest/gtest.h"
#include <iostream>
#include <Eigen/Dense>
#include "vector_matrix.h"
#include <cmath>

using namespace Eigen;

class TestVec4 : public ::testing::Test
{
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
protected:
	vec4 my_vec_1;
	Vector4f eigen_vec_1;
	vec4 my_vec_2;
	Vector4f eigen_vec_2;
	void SetUp()
	{
		my_vec_1 = vec4(1, 2, 3, 4);
		eigen_vec_1 = Vector4f(1, 2, 3, 4);
		my_vec_2 = vec4(-100.123f, 23425.1234f, -12341234.25145f, 4.123f);
		eigen_vec_2 = Vector4f(-100.123f, 23425.1234f, -12341234.25145f, 4.123f);
	}
};

void TestValues(vec4& vec, Vector4f& e_vec)
{
	for (int i = 0; i < 4; ++i)
	{
		EXPECT_FLOAT_EQ(vec[i], e_vec[i]);
	}
}

void TestValues(vec4& vec, float x, float y, float z, float w)
{
	EXPECT_FLOAT_EQ(vec.x, x);
	EXPECT_FLOAT_EQ(vec.y, y);
	EXPECT_FLOAT_EQ(vec.z, z);
	EXPECT_FLOAT_EQ(vec.w, w);
}

TEST(Vec4, Init) 
{
	vec4 test(1.2f, 2.2f, 3.2f, 4.2f);
	TestValues(test, 1.2f, 2.2f, 3.2f, 4.2f);
}

TEST(Vec4, InitByZeroes)
{
	vec4 test;
	TestValues(test, 0, 0, 0, 0);
}

TEST(Vec4, InitFromArray)
{
	float source[4] = {1.1f, 2.2f, 3.3f, 4.4f};
	vec4 test(source);
	TestValues(test, 1.1f, 2.2f, 3.3f, 4.4f);
}

TEST_F(TestVec4, Length)
{
	EXPECT_FLOAT_EQ(my_vec_1.length(), eigen_vec_1.norm());
	EXPECT_FLOAT_EQ(my_vec_2.length(), eigen_vec_2.norm());
}

TEST_F(TestVec4, Normalize)
{
	vec4 my_vec;
	EXPECT_THROW(my_vec.normalize(), runtime_error);
	TestValues(my_vec_1.normalize(), (Vector4f)(eigen_vec_1.normalized()));
	TestValues(my_vec_1, eigen_vec_1);
	TestValues(my_vec_2.normalize(), (Vector4f)(eigen_vec_2.normalized()));
	TestValues(my_vec_2, eigen_vec_2);
}

TEST_F(TestVec4, NormalizeInPlace)
{
	vec4 my_vec;
	EXPECT_THROW(my_vec.normalize_in_place(), runtime_error);
	eigen_vec_1.normalize();
	my_vec_1.normalize_in_place();
	TestValues(my_vec_1, eigen_vec_1);
	eigen_vec_2.normalize();
	my_vec_2.normalize_in_place();
	TestValues(my_vec_2, eigen_vec_2);
}

TEST_F(TestVec4, Add)
{
	TestValues(my_vec_1 + my_vec_1, (Vector4f)(eigen_vec_1 + eigen_vec_1));
	TestValues(my_vec_1 + my_vec_2, (Vector4f)(eigen_vec_1 + eigen_vec_2));
	TestValues(my_vec_2 + my_vec_1, (Vector4f)(eigen_vec_2 + eigen_vec_1));
	TestValues(my_vec_2 + my_vec_2, (Vector4f)(eigen_vec_2 + eigen_vec_2));
}

TEST_F(TestVec4, Sub)
{
	TestValues(my_vec_1 - my_vec_1, (Vector4f)(eigen_vec_1 - eigen_vec_1));
	TestValues(my_vec_1 - my_vec_2, (Vector4f)(eigen_vec_1 - eigen_vec_2));
	TestValues(my_vec_2 - my_vec_1, (Vector4f)(eigen_vec_2 - eigen_vec_1));
	TestValues(my_vec_2 - my_vec_2, (Vector4f)(eigen_vec_2 - eigen_vec_2));
}

TEST_F(TestVec4, MultScalar)
{
	TestValues(my_vec_1 * 2, (Vector4f)(eigen_vec_1 * 2));
	TestValues(2 * my_vec_1, (Vector4f)(2 * eigen_vec_1));
	TestValues(my_vec_2 * -12456.21578647f, (Vector4f)(eigen_vec_2 * -12456.21578647f));
	TestValues(0.356365f * my_vec_2, (Vector4f)(0.356365f * eigen_vec_2));
}

TEST_F(TestVec4, MultComp)
{
	TestValues(my_vec_1 * my_vec_1, 1, 4, 9, 16);
	TestValues(my_vec_1 * my_vec_2, -100.123f, 46850.2468f, -37023702.75435f, 16.492f);
	TestValues(my_vec_2 * my_vec_1, -100.123f, 46850.2468f, -37023702.75435f, 16.492f);
}

TEST_F(TestVec4, Dot)
{	
	EXPECT_FLOAT_EQ(my_vec_1.dot(my_vec_1), eigen_vec_1.dot(eigen_vec_1));
	EXPECT_FLOAT_EQ(my_vec_1.dot(my_vec_2), eigen_vec_1.dot(eigen_vec_2));
	EXPECT_FLOAT_EQ(my_vec_2.dot(my_vec_1), eigen_vec_2.dot(eigen_vec_1));
	EXPECT_FLOAT_EQ(my_vec_2.dot(my_vec_2), eigen_vec_2.dot(eigen_vec_2));
}

TEST_F(TestVec4, Cross)
{
	vec4 vec_1(3, 4, 5, 1);
	TestValues(my_vec_1.cross(my_vec_1), 0, 0, 0, 0);
	TestValues(my_vec_1.cross(vec_1), -2, 4, -2, 0);
	TestValues(vec_1.cross(my_vec_1), 2, -4, 2, 0);
	vec4 vec_2(3.5f, -0.4f, 5.1f, 1.0f);
	TestValues(my_vec_1.cross(vec_2), 11.4f, 5.4f, -7.4f, 0.0f);

}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}