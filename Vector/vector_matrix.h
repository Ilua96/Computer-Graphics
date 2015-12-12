#pragma once

#include <string>
using namespace std;
class vec4
{
	public:
		float x, y, z, w;
		vec4(float x, float y, float z, float w = 0): x(x), y(y), z(z), w(w) {};
		vec4();
		vec4(float* source);
		string str() const;
		float length() const;
		vec4 normalize() const;
		void normalize_in_place();
		vec4 operator+(const vec4 &other) const;
		vec4 operator-(const vec4 &other) const;
		vec4 operator*(float a) const;
		friend vec4 operator*(float a, vec4 &vec);
		vec4 operator*(const vec4 &other) const;
		float dot(const vec4 &other) const;
		vec4 cross(const vec4 &other) const;
		float& operator[](int i);
};

class mat4
{
	public:
		float matrix[4][4];
		mat4(float X1, float Y1, float Z1, float W1, float X2, float Y2, float Z2, float W2,
			 float X3, float Y3, float Z3, float W3, float X4, float Y4, float Z4, float W4);
		mat4();
		mat4(float* source);
		mat4(float source[4][4]);
		void identity();
		mat4 transpose();
		float* operator[](int i);
		float det();
		float det3(int row, int col);
		mat4 inverse();
		mat4 operator+(mat4 &other);
		mat4 operator-(mat4 &other);
		mat4 operator*(float a);
		friend mat4 operator*(float a, mat4 &vec);
		mat4 operator*(mat4 &other);
		vec4 operator*(vec4 &vec);
		mat4 scale(vec4 &vec);
		mat4 rotate(float angle, vec4 axis);
		mat4 translate(vec4 &vec);
		mat4 perspective(float fovy, float aspect, float near, float far);
		mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
		string str();
};

