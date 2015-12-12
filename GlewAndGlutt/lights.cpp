#define _USE_MATH_DEFINES
#include "lights.h"
#include "camera.h"
#include <iostream>
#include <math.h>
#include <model.h>

Spot_Light::Spot_Light(vec4 pos, vec4 dir, vec4 up, vec4 color, float cutoff, float constant, float linear, float quadr) :
	Point_Light(pos, color, constant, linear, quadr), Dir_Light(dir, up, color), Ambient_Light(color), cutoff(cutoff)
{

}

void Spot_Light::set(GLuint program, int index)
{
	stringstream s_index;
	s_index << index;
	glUniform3f(glGetUniformLocation(program, ("spot_lights[" + s_index.str() + "].pos").c_str()), pos.x, pos.y, pos.z);
	glUniform3f(glGetUniformLocation(program, ("spot_lights[" + s_index.str() + "].color").c_str()), color.x, color.y, color.z);
	glUniform3f(glGetUniformLocation(program, ("spot_lights[" + s_index.str() + "].dir").c_str()), dir.x, dir.y, dir.z);
	glUniform1f(glGetUniformLocation(program, ("spot_lights[" + s_index.str() + "].cutoff").c_str()), cutoff);
	glUniform1f(glGetUniformLocation(program, ("spot_lights[" + s_index.str() + "].constant").c_str()), constant);
	glUniform1f(glGetUniformLocation(program, ("spot_lights[" + s_index.str() + "].liner").c_str()), linear);
	glUniform1f(glGetUniformLocation(program, ("spot_lights[" + s_index.str() + "].quadr").c_str()), quadr);
}

void Spot_Light::key_press(bool is_key_press[128], Camera camera)
{
	Point_Light::key_press(is_key_press, camera);
	Dir_Light::key_press(is_key_press, camera);
}

Point_Light::Point_Light(vec4 pos, vec4 color, float constant, float linear, float quadr) : Ambient_Light(color),
pos(pos), linear(linear), constant(constant), quadr(quadr) {};

void Point_Light::set(GLuint program, int index)
{
	stringstream s_index;
	s_index << index;
	glUniform3f(glGetUniformLocation(program, ("point_lights[" + s_index.str() + "].pos").c_str()), pos.x, pos.y, pos.z);
	glUniform3f(glGetUniformLocation(program, ("point_lights[" + s_index.str() + "].color").c_str()), color.x, color.y, color.z);
	glUniform1f(glGetUniformLocation(program, ("point_lights[" + s_index.str() + "].constant").c_str()), constant);
	glUniform1f(glGetUniformLocation(program, ("point_lights[" + s_index.str() + "].liner").c_str()), linear);
	glUniform1f(glGetUniformLocation(program, ("point_lights[" + s_index.str() + "].quadr").c_str()), quadr);
}

void Point_Light::draw_light_source(GLuint program, Mesh &source_mesh, Camera camera, GLuint color_loc, GLuint mvp_loc, GLuint model_loc)
{
	mat4 model, mvp;
	model.identity();
	model = model.translate(pos);
	mvp = camera.get_mat();
	glUniform3f(color_loc, color.x, color.y, color.z);
	source_mesh.draw(program, mvp_loc, model_loc, mvp, model);
}

void Point_Light::move(const vec4 & vec)
{
	pos = pos + vec;
}

void Point_Light::key_press(bool is_key_press[128], Camera camera)
{
	Ambient_Light::key_press(is_key_press, camera);
	if (is_key_press['w'])
		move(vec4(camera.get_dir().x, 0.0f, camera.get_dir().z).normalize() * -move_speed);
	if (is_key_press['s'])
		move(vec4(camera.get_dir().x, 0.0f, camera.get_dir().z).normalize() * move_speed);
	if (is_key_press['d'])
		move(camera.get_right() * move_speed);
	if (is_key_press['a'])
		move(camera.get_right() * -move_speed);
	if (is_key_press[' '])
		move(vec4(0.0f, 1.0f * move_speed, 0.0f));
	if (is_key_press['c'])
		move(vec4(0.0f, -1.0f * move_speed, 0.0f));
}

void Ambient_Light::change_color(const vec4 & vec)
{
	color = color + vec;
	for (int i = 0; i < 4; ++i)
	{
		if (color[i] > 1.0f)
		{
			color[i] = 1.0f;
		}
		if (color[i] < 0.0f)
		{
			color[i] = 0.0f;
		}
	}
}

void Ambient_Light::key_press(bool is_key_press[128], Camera camera)
{
	if (is_key_press['j'])
		change_color(vec4(1.0f * color_speed, 0.0f, 0.0f));
	if (is_key_press['m'])
		change_color(vec4(1.0f * -color_speed, 0.0f, 0.0f));
	if (is_key_press['k'])
		change_color(vec4(0.0f, 1.0f * color_speed, 0.0f));
	if (is_key_press[','])
		change_color(vec4(0.0f, 1.0f * -color_speed, 0.0f));
	if (is_key_press['l'])
		change_color(vec4(0.0f, 0.0f, 1.0f * color_speed));
	if (is_key_press['.'])
		change_color(vec4(0.0f, 0.0f, 1.0f * -color_speed));
}

Dir_Light::Dir_Light(vec4 Dir, vec4 Up, vec4 color) : Ambient_Light(color), dir(Dir), up(Up)
{
	dir.normalize_in_place();
	up.normalize_in_place();
	right = up.cross(dir).normalize();
}
void Dir_Light::set(GLuint program, int index)
{
	stringstream s_index;
	s_index << index;
	glUniform3f(glGetUniformLocation(program, ("dir_lights[" + s_index.str() + "].color").c_str()), color.x, color.y, color.z);
	glUniform3f(glGetUniformLocation(program, ("dir_lights[" + s_index.str() + "].dir").c_str()), dir.x, dir.y, dir.z);
}

void Dir_Light::rotate(float angle, const vec4 & vec)
{
	mat4 tmp;
	tmp.identity();
	tmp = tmp.rotate(angle, vec);
	dir = (tmp * dir).normalize();
	up = (tmp * up).normalize();
	right = (tmp * right).normalize();
}

void Dir_Light::key_press(bool is_key_press[128], Camera camera)
{
	Ambient_Light::key_press(is_key_press, camera);
	if (is_key_press['e'])
		rotate(-rotate_speed, up);
	if (is_key_press['q'])
		rotate(rotate_speed, up);
	if (is_key_press['r'])
		rotate(-rotate_speed, right);
	if (is_key_press['f'])
		rotate(rotate_speed, right);
}