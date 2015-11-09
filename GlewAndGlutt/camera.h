#pragma once
#include <vector_matrix.h>
class Camera
{
	public:
		float fovy;
		int width, hight;
		float n, f;
		vec4 pos, up, dir, tar, right;
		Camera(float fovy, int width, int hight, float n, float f) : fovy(fovy), width(width), hight(hight), n(n), f(f) {};
		void move(const vec4 &vec);
		void rotate(float angle, const vec4 &vec);
		void zoom(float vlaue);
		void look_at(const vec4 &Pos, const vec4 &Tar, const vec4 &Up);
		mat4 get_mat();
};