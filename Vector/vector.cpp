#include "vector_matrix.h"
#include <cmath>
#include <sstream>
#include <string>

vec4::vec4()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

vec4::vec4(float * source)
{
	memcpy(this, source, 4 * sizeof(float));
}

float vec4::length() const
{
	return sqrt(x*x + y*y + z*z + w*w);
};

vec4 vec4::normalize() const
{
	float norm = length();
	if (norm == 0)
	{
		throw runtime_error("Length = 0");
	}
	return vec4(x/norm, y/norm, z/norm, w/norm);
}

void vec4::normalize_in_place()
{
	float norm = length();
	if (norm == 0)
	{
		throw runtime_error("Length = 0");
	}
	x /= norm;
	y /= norm;
	z /= norm;
	w /= norm;
}

vec4 vec4::operator+(const vec4 &other) const
{
	return vec4(x + other.x, y + other.y, z + other.z, w + other.w);
}

vec4 vec4::operator*(float a) const
{
	return vec4(x * a, y * a, z * a, w * a);
}

vec4 vec4::operator*(const vec4 & other) const
{
	return vec4(x * other.x, y * other.y, z * other.z, w * other.w);
}

float vec4::dot(const vec4 &other) const
{
	return x * other.x + y * other.y + z * other.z + w * other.w;
}

vec4 vec4::cross(const vec4 &other) const
{
	return vec4(y * other.z - z * other.y, - x * other.z + z * other.x, x * other.y - y * other.x, 0);
}

vec4 operator*(float a, vec4 &vec)
{
	return vec * a;
}

vec4 vec4::operator-(const vec4 &other) const
{
	return vec4(x - other.x, y - other.y, z - other.z, w - other.w);
}

float& vec4::operator[](int i)
{
	switch (i)
	{
		case 0:
		{
			return x;
			break;
		}
		case 1:
		{
			return y;
			break;
		}
		case 2:
		{
			return z;
			break;
		}
		case 3:
		{
			return w;
			break;
		}
	}

}

string vec4::str() const
{
	stringstream s;
	s << x << " " << y << " " << z << " " << w;
	return s.str();
}
