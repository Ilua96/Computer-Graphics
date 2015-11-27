#pragma once
#include <vector_matrix.h>
#include <glew.h>
#include <freeglut.h>
#include <vector>
#include <stdlib.h>
#include <string>
#include <sstream>
class Material {
	public:
		vec4 ambient;
		vec4 diffuse;
		vec4 specular;
		float shininess;
		Material(vec4 ambient, vec4 diffuse, vec4 specular, float shininess) :
			ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {};
};

class Dir_Light {
	public:
		vec4 dir;
		vec4 color;
		Dir_Light(vec4 dir, vec4 color) : dir(dir), color(color) {};
};

class Point_Light {
	public:
		vec4 pos;
		vec4 color;
		float constant;
		float linear;
		float quadr;
		Point_Light(vec4 pos, vec4 color, float constant, float linear, float quadr) :
			pos(pos), color(color), linear(linear), constant(constant), quadr(quadr) {};
		void set(GLuint program, int index)
		{
			stringstream s_index;
			s_index << index;
			glUniform3f(glGetUniformLocation(program, ("point_lights[" + s_index.str() + "].pos").c_str()), pos.x, pos.y, pos.z);
			glUniform3f(glGetUniformLocation(program, ("point_lights[" + s_index.str() + "].color").c_str()), color.x, color.y, color.z);
			glUniform1f(glGetUniformLocation(program, ("point_lights[" + s_index.str() + "].constant").c_str()), constant);
			glUniform1f(glGetUniformLocation(program, ("point_lights[" + s_index.str() + "].liner").c_str()), linear);
			glUniform1f(glGetUniformLocation(program, ("point_lights[" + s_index.str() + "].quadr").c_str()), quadr);
		};
};

class Spot_Light {
	public:
		vec4 pos;
		vec4 dir;
		vec4 color;
		float cutoff;
		float constant;
		float linear;
		float quadr;
		Spot_Light(vec4 pos, vec4 dir, vec4 color, float cutoff, float constant, float linear, float quadr) :
			pos(pos), dir(dir), color(color), cutoff(cutoff), constant(constant), linear(linear), quadr(quadr) {};
};

vector <Dir_Light> dir_lights;
vector <Spot_Light> spot_lights;
vector <Point_Light> point_lights;