#pragma once
#include <vector_matrix.h>
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
		Point_Light(vec4 pos, vec4 color, float constant, float liner, float quadr) :
			pos(pos), color(color), constant(constant), quadr(quadr) {};
};

class Spot_Light {
	public:
		vec4 pos;
		vec4 dir;
		vec4 color;
		float angle;
		float constant;
		float linear;
		float quadr;
		Spot_Light(vec4 pos, vec4 dir, vec4 color, float angle, float constant, float linear, float quadr) :
			pos(pos), dir(dir), color(color), angle(angle), constant(constant), linear(linear), quadr(quadr) {};
};