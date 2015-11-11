#include "camera.h"
#include <iostream>

Camera::Camera(float fovy, int width, int hight, float near_plane, float far_plane) : fovy(fovy), width(width), hight(hight), near_plane(near_plane), far_plane(far_plane)
{
	normal_fovy = fovy;
	perspective = true;
}

Camera::Camera(float left, float right, float bottom, float top, float near_plane, float far_plane): left(left), right_fur(right), bottom(bottom), top(top), near_plane(near_plane), far_plane(far_plane)
{
	perspective = false;
}

void Camera::move(const vec4 & vec)
{
	pos = pos + vec;
	tar = tar + vec;
	right = up.cross(dir).normalize();
	dir = pos - tar;
	dir.normalize_in_place();
}

void Camera::rotate(float angle, const vec4 & vec)
{
	mat4 tmp;
	tmp.identity();
	tmp = tmp.rotate(angle, vec);
	up = (tmp * up).normalize();
	dir = (tmp * dir).normalize();
	right = up.cross(dir).normalize();
	tar = pos - dir;
}

void Camera::zoom(float value)
{
	fovy += value;
	if (fovy <= 10)
	{
		fovy = 10;
	}
	else if (fovy >= 150)
	{
		fovy = 150;
	}
}

void Camera::look_at(const vec4 & Pos, const vec4 & Tar, const vec4 & Up)
{
	pos = Pos;
	tar = Tar;
	dir = (pos - tar).normalize();
	up = Up.normalize();
	right = up.cross(dir).normalize();
}

void Camera::set_normal_zoom()
{
	fovy = normal_fovy;
}

mat4 Camera::get_mat()
{
	mat4 projection, view;
	projection.identity();
	if (perspective)
	{
		projection = projection.perspective(fovy, (float)((float)width / (float)hight), near_plane, far_plane);
	}
	else
	{
		projection = projection.orthographic(left, right_fur, bottom, top, near_plane, far_plane);
	}
	view = mat4(right.x, right.y, right.z, 0, up.x, up.y, up.z, 0, dir.x, dir.y, dir.z, 0, 0, 0, 0, 1) * mat4(1, 0, 0, -pos.x, 0, 1, 0, -pos.y, 0, 0, 1, -pos.z, 0, 0, 0, 1);
	return projection * view;
}

vec4 Camera::get_dir() const
{
	return dir;
}

vec4 Camera::get_right() const
{
	return right;
}
