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
	//tar = tar + vec;
}

void Camera::rotate(float angle, const vec4 & vec)
{
	mat4 tmp;
	tmp.identity();
	tmp = tmp.rotate(angle, vec);
	up = (tmp * up).normalize();
	dir = (tmp * dir).normalize();
	right = up.cross(dir).normalize();
	//tar = pos - dir;
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

void Camera::key_press(bool is_key_press[128])
{
	const float rotate_speed = 3.0f;
	const float move_speed = 1.0f;
	if (is_key_press['w'])
		move(vec4(get_dir().x, 0.0f, get_dir().z).normalize() * -move_speed);
	if (is_key_press['s'])
		move(vec4(get_dir().x, 0.0f, get_dir().z).normalize() * move_speed);
	if (is_key_press['d'])
		move(get_right() * move_speed);
	if (is_key_press['a'])
		move(get_right() * -move_speed);
	if (is_key_press[' '])
		move(vec4(0.0f, 1.0f * move_speed, 0.0f));
	if (is_key_press['c'])
		move(vec4(0.0f, -1.0f * move_speed, 0.0f));
	if (is_key_press['e'])
		rotate(rotate_speed, vec4(0.0f, 1.0f, 0.0f));
	if (is_key_press['q'])
		rotate(-rotate_speed, vec4(0.0f, 1.0f, 0.0f));
	if (is_key_press['r'])
		rotate(-rotate_speed, get_right());
	if (is_key_press['f'])
		rotate(rotate_speed, get_right());
	if (is_key_press['z'])
		zoom(5.0f);
	if (is_key_press['x'])
		zoom(-5.0f);
	if (is_key_press['g'])
		set_normal_zoom();
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

vec4 Camera::get_dir()
{
	return dir;
}

vec4 Camera::get_right()
{
	return right;
}

vec4 Camera::get_pos()
{
	return pos;
}
