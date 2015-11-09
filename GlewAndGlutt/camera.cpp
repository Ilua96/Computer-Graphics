#include "camera.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Camera::move(const vec4 & vec)
{
	pos = pos - vec;
	tar = tar - vec;
	dir = pos - tar;
	dir.normalize_in_place();
	//cout << "a";
}

void Camera::rotate(float angle, const vec4 & vec)
{
	mat4 tmp;
	tmp.identity();
	tmp = tmp.rotate(angle, vec);
	up = tmp * up;
	dir = tmp * dir;
	dir.normalize_in_place();
	tar = pos - dir;
}

void Camera::zoom(float vlaue)
{
}

void Camera::look_at(const vec4 & Pos, const vec4 & Tar, const vec4 & Up)
{
	pos = Pos.normalize();
	tar = Tar;
	dir = pos - tar;
	up = Up.normalize();
	right = up.cross(dir).normalize();
}

mat4 Camera::get_mat()
{
	right = up.cross(dir).normalize();
	mat4 projection, view;
	projection.identity();
	projection = projection.perspective(fovy, (float)((float)width / (float)hight), n, f);
	view = mat4(right.x, right.y, right.z, 0, up.x, up.y, up.z, 0, dir.x, dir.y, dir.z, 0, 0, 0, 0, 1) * mat4(1, 0, 0, -pos.x, 0, 1, 0, -pos.y, 0, 0, 1, -pos.z, 0, 0, 0, 1);
	return (projection * view).transpose();
}
