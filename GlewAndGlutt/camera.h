#pragma once
#include <vector_matrix.h>
class Camera
{
	public:
		Camera(float fovy, int width, int hight, float near_plane, float far_plane);
		Camera(float left, float right, float bottom, float top, float near_plane, float far_plane);
		void move(const vec4 &vec);
		void rotate(float angle, const vec4 &vec);
		void zoom(float value);
		void look_at(const vec4 &Pos, const vec4 &Tar, const vec4 &Up);
		void set_normal_zoom();
		mat4 get_mat();
		vec4 get_dir() const;
		vec4 get_right() const;
	private:
		int width, hight;
		float normal_fovy, fovy, near_plane, far_plane, left, right_fur, bottom, top;
		bool perspective;
		vec4 pos, up, dir, tar, right;
};