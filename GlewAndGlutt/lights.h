#pragma once
#include <vector_matrix.h>
#include <glew.h>
#include <freeglut.h>
#include <vector>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector_matrix.h>
#include <camera.h>
#include <model.h>
#include <mesh.h>
#include <model.h>

class Material {
	public:
		vec4 ambient;
		vec4 diffuse;
		vec4 specular;
		float shininess;
		Material(vec4 ambient, vec4 diffuse, vec4 specular, float shininess) :
			ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {};
};

const float rotate_speed = 3.0f;
const float move_speed = 1.0f;
const float color_speed = 0.05f;

class Ambient_Light
{
	public:
		vec4 color;
		Ambient_Light(vec4 color) : color(color) {};
		void change_color(const vec4 &vec);
		void key_press(bool is_key_press[128], Camera camera);
};

class Dir_Light : public virtual Ambient_Light {
	public:
		vec4 dir;
		vec4 up;
		vec4 right;
		Dir_Light(vec4 Dir, vec4 Up, vec4 color);
		void set(GLuint program, int index);
		void rotate(float angle, const vec4 &vec);
		void key_press(bool is_key_press[128], Camera camera);
};

class Point_Light: public virtual Ambient_Light {
	public:
		vec4 pos;
		float constant;
		float linear;
		float quadr;
		Point_Light(vec4 pos, vec4 color, float constant, float linear, float quadr);
		void set(GLuint program, int index);
		void draw_light_source(GLuint program, Mesh &source_mesh, Camera camera, GLuint color_loc, GLuint mvp_loc, GLuint model_loc);
		void move(const vec4 &vec);
		void key_press(bool is_key_press[128], Camera camera);
};

class Spot_Light: public Point_Light, public Dir_Light{
	public:
		float cutoff;
		Spot_Light(vec4 pos, vec4 dir, vec4 up, vec4 color, float cutoff, float constant, float linear, float quadr);
		void set(GLuint program, int index);
		void key_press(bool is_key_press[128], Camera camera);
};

static vector <Dir_Light> dir_lights;
static vector <Spot_Light> spot_lights;
static vector <Point_Light> point_lights;
static int cur_spot_light, cur_dir_light, cur_point_light;
