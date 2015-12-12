#define _USE_MATH_DEFINES
#include <glew.h>
#include <freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector_matrix.h>
#include <cmath>
#include <camera.h>
#include <string>
#include <sstream>
#include <lights.h>
#include <vector>
#include <mesh.h>
#include <model.h>
#include <math.h>

GLuint main_program;
GLuint light_program;
GLuint VAO, plane_VAO;
GLuint VBO, plane_VBO;
GLuint attr_location;
GLuint mvp_location;
int win_width = 1920;
int win_height = 1080;
Mesh plane, cube;
Model mi28_model, sphere_model, crate_model, crysis_model, floor_model;
Camera camera(70.0f, win_width, win_height, 0.1f, 500.0f);
//Camera camera(-880.0f, 800.0f, -600.0f, 600.0f, 0.1f, 2000.0f);  
enum focus {f_camera, f_point, f_dir, f_spot, f_ambient} cur_focus;

vector <Vertex> cube_vertices = {
	Vertex(vec4(-0.5f, -0.5f, -0.5f),  vec4(0.0f,  0.0f, -1.0f), 0.0f,  0.0f),
	Vertex(vec4(0.5f, -0.5f, -0.5f),   vec4(0.0f,  0.0f, -1.0f), 0.0f,  0.0f),
	Vertex(vec4(0.5f,  0.5f, -0.5f),   vec4(0.0f,  0.0f, -1.0f), 0.0f,  0.0f),
	Vertex(vec4(-0.5f,  0.5f, -0.5f),  vec4(0.0f,  0.0f, -1.0f), 0.0f,  0.0f),
														
	Vertex(vec4(-0.5f, -0.5f,  0.5f),  vec4(0.0f,  0.0f, 1.0f) , 0.0f,  0.0f),
	Vertex(vec4(0.5f, -0.5f,  0.5f),   vec4(0.0f,  0.0f, 1.0f) , 0.0f,  0.0f),
	Vertex(vec4(0.5f,  0.5f,  0.5f),   vec4(0.0f,  0.0f, 1.0f) , 0.0f,  0.0f),
	Vertex(vec4(-0.5f,  0.5f,  0.5f),  vec4(0.0f,  0.0f, 1.0f) , 0.0f,  0.0f),
														
	Vertex(vec4(-0.5f,  0.5f,  0.5f), vec4(-1.0f,  0.0f,  0.0f), 0.0f,  0.0f),
	Vertex(vec4(-0.5f,  0.5f, -0.5f), vec4(-1.0f,  0.0f,  0.0f), 0.0f,  0.0f),
	Vertex(vec4(-0.5f, -0.5f, -0.5f), vec4(-1.0f,  0.0f,  0.0f), 0.0f,  0.0f),
	Vertex(vec4(-0.5f, -0.5f,  0.5f), vec4(-1.0f,  0.0f,  0.0f), 0.0f,  0.0f),
															
	Vertex(vec4(0.5f,  0.5f,  0.5f),  vec4(1.0f,  0.0f,  0.0f) , 0.0f,  0.0f),
	Vertex(vec4(0.5f,  0.5f, -0.5f),  vec4(1.0f,  0.0f,  0.0f) , 0.0f,  0.0f),
	Vertex(vec4(0.5f, -0.5f, -0.5f),  vec4(1.0f,  0.0f,  0.0f) , 0.0f,  0.0f),
	Vertex(vec4(0.5f, -0.5f,  0.5f),  vec4(1.0f,  0.0f,  0.0f) , 0.0f,  0.0f),
														
	Vertex(vec4(-0.5f, -0.5f, -0.5f),  vec4(0.0f, -1.0f,  0.0f), 0.0f,  0.0f),
	Vertex(vec4(0.5f, -0.5f, -0.5f),   vec4(0.0f, -1.0f,  0.0f), 0.0f,  0.0f),
	Vertex(vec4(0.5f, -0.5f,  0.5f),   vec4(0.0f, -1.0f,  0.0f), 0.0f,  0.0f),
	Vertex(vec4(-0.5f, -0.5f,  0.5f),  vec4(0.0f, -1.0f,  0.0f), 0.0f,  0.0f),
															
	Vertex(vec4(-0.5f,  0.5f, -0.5f),  vec4(0.0f,  1.0f,  0.0f), 0.0f,  0.0f),
	Vertex(vec4(0.5f,  0.5f, -0.5f),   vec4(0.0f,  1.0f,  0.0f), 0.0f,  0.0f),
	Vertex(vec4(0.5f,  0.5f,  0.5f),   vec4(0.0f,  1.0f,  0.0f), 0.0f,  0.0f),
	Vertex(vec4(-0.5f,  0.5f,  0.5f),  vec4(0.0f,  1.0f,  0.0f), 0.0f,  0.0f),
};

vector <GLuint> cube_ind = { 0, 1, 2, 2, 3, 0,   4, 5, 6, 6, 4, 7,   8, 9, 10, 10, 8, 11,  
							 12, 13, 14, 14, 12, 15,  16, 17, 18, 18, 16, 19,   20, 21, 22, 22, 20, 23};

vector <Vertex> plane_vertices = {
	Vertex(vec4(-100.0f,  0.0f, -100.0f),  vec4(0.0f,  1.0f,  0.0f), 0.0f,  0.0f),
	Vertex(vec4(-100.0f,  0.0f, 100.0f),  vec4(0.0f,  1.0f,  0.0f) , 10.0f,  0.0f),
	Vertex(vec4(100.0f,  0.0f,  100.0f),  vec4(0.0f,  1.0f,  0.0f) , 10.0f,  10.0f),
	Vertex(vec4(100.0f,  0.0f, -100.0f),  vec4(0.0f,  1.0f,  0.0f) , 10.0f,  0.0f),
};
vector <GLuint> plane_ind = { 0, 1, 2, 0, 2, 3 };

bool is_key_press[128];
void press_keys(unsigned char key, int x, int y)
{
	is_key_press[key] = true;
	switch (cur_focus)
	{ 
		case f_spot:
			if (is_key_press['n'])
			{
				if (spot_lights.size() < 10)
				{
					spot_lights.push_back(Spot_Light(vec4(0.0f, 20.0f, 0.0f), vec4(0.0f, -1.0, 0.0f),
						vec4(0.0f, 0.0f, -1.0f), vec4(1.0f, 1.0f, 1.0f), cosf(M_PI / 180.0f * 25.0f), 1.0f, 0.027f, 0.0028f));
					cur_spot_light = spot_lights.size() - 1;
				}
			}
			if (is_key_press['b'])
			{
				if (spot_lights.size() > 1)
				{
					spot_lights.erase(spot_lights.begin() + cur_spot_light);
					cur_spot_light = 0;
				}
			}
			if (is_key_press['y'])
				cur_spot_light = ++cur_spot_light % spot_lights.size();
			if (is_key_press['h'])
				cur_spot_light = --cur_spot_light % spot_lights.size();
			break;
		case f_point:
			if (is_key_press['n'])
			{
				if (point_lights.size() < 10)
				{
					point_lights.push_back(Point_Light(vec4(0.0f, 20.0f, 0.0f), vec4(1.0f, 1.0f, 1.0f), 1.0f, 0.027f, 0.0028f));
					cur_point_light = point_lights.size() - 1;
				}
			}
			if (is_key_press['b'])
			{
				if (point_lights.size() > 1)
				{
					point_lights.erase(point_lights.begin() + cur_point_light);
					cur_point_light = 0;
				}
			}
			if (is_key_press['y'])
				cur_point_light = ++cur_point_light % point_lights.size();
			if (is_key_press['h'])
				cur_point_light = --cur_point_light % point_lights.size();
			break;
		case f_dir:
			if (is_key_press['n'])
			{
				if (dir_lights.size() < 10)
				{
					dir_lights.push_back(Dir_Light(vec4(0.0f, -1.0f, 0.0f), vec4(0.0f, 0.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f)));
					cur_dir_light = dir_lights.size() - 1;
				}
			}
			if (is_key_press['b'])
			{
				if (dir_lights.size() > 1)
				{
					dir_lights.erase(dir_lights.begin() + cur_dir_light);
					cur_dir_light = 0;
				}
			}
			if (is_key_press['y'])
				cur_dir_light = ++cur_dir_light % dir_lights.size();
			if (is_key_press['h'])
				cur_dir_light = --cur_dir_light % dir_lights.size();
			break;
	}
}

void up_keys(unsigned char key, int x, int y)
{
	is_key_press[key] = false;
}

void mouse_move(int x, int y)
{
	float sensitivity = 0.1;
	int cx = win_width / 2;
	int cy = win_height / 2;
	if (x != cx || y != cy)  
	{
		float x_offset = x - cx;
		float y_offset = y - cy;
		glutWarpPointer(cx, cy);
		camera.rotate(y_offset * sensitivity, camera.get_right());
		camera.rotate(x_offset * sensitivity, vec4(0.0f, 1.0f, 0.0f));
		glutPostRedisplay();
	}
}

void read_file(char *file_name, char **text)
{
	FILE *input;
	input = fopen(file_name, "rb");
	fseek(input, 0, SEEK_END);
	int file_size = ftell(input) + 1;
	fseek(input, 0, SEEK_SET);
	*text = (char *)calloc(file_size, sizeof(char));
	fread(*text, sizeof(char), file_size, input);
}

void create_shader(GLuint shader, char **string, char *shader_name)
{
	glShaderSource(shader, 1, string, NULL);
	glCompileShader(shader);
	GLint status;
	GLchar log[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderInfoLog(shader, 512, NULL, log);
		printf("%s shader compile error.\n %s", shader_name, log);
		glDeleteShader(shader);
		return;
	}
}

GLuint create_program(char *VS_name, char *FS_name)
{
	char *vs_text = NULL;
	char *fs_text = NULL;
	read_file(VS_name, &vs_text);
	read_file(FS_name, &fs_text);

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	create_shader(vertex_shader, &vs_text, "Vertex");

	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	create_shader(fragment_shader, &fs_text, "Fragment");

	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	int link_status;
	glGetProgramiv(program, GL_LINK_STATUS, &link_status);
	if (link_status != GL_TRUE)
	{
		printf("LINK ERROR!\n");
		return -1;;
	}
	return program;
}

void timer(int value)
{
	if (is_key_press[27])
		exit(0);
	if (is_key_press['p'])
	{
		cur_focus = f_point;
		cur_point_light = 0;
	}
	if (is_key_press['o'])
	{
		cur_focus = f_spot;
		cur_spot_light = 0;
	}
	if (is_key_press['i'])
	{
		cur_focus = f_dir;
		cur_dir_light = 0;
	}
	if (is_key_press['u'])
	{
		cur_focus = f_camera;
	}
	switch (cur_focus)
	{
		case (f_camera):
		{
			camera.key_press(is_key_press);
			break;
		}
		case (f_point):
		{
			point_lights[cur_point_light].key_press(is_key_press, camera);
			break;
		}
		case (f_spot):
		{
			spot_lights[cur_spot_light].key_press(is_key_press, camera);
			break;
		}
		case (f_dir):
		{
			dir_lights[cur_dir_light].key_press(is_key_press, camera);
			break;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(40, timer, 0);
}

string get_game_mode_string()
{
	stringstream s;
	s << win_width << "x" << win_height << ":" << 32;
	return s.str();
}

void set_lights(GLuint program)
{
	glUniform1i(glGetUniformLocation(program, "count_point_lights"), point_lights.size());
	glUniform1i(glGetUniformLocation(program, "count_dir_lights"), dir_lights.size());
	glUniform1i(glGetUniformLocation(program, "count_spot_lights"), spot_lights.size());
	for (int i = 0; i < spot_lights.size(); ++i)
	{
		spot_lights[i].set(program, i);
	}
	for (int i = 0; i < dir_lights.size(); ++i)
	{
		dir_lights[i].set(program, i);
	}
	for (int i = 0; i < point_lights.size(); ++i)
	{
		point_lights[i].set(program, i);
	}
}

void render()
{
	mat4 mvp, model;
	model.identity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(main_program);
	mvp_location = glGetUniformLocation(light_program, "mvp");
	GLint model_loc = glGetUniformLocation(main_program, "model");
	glUniform3f(glGetUniformLocation(main_program, "view_pos"), camera.get_pos().x, camera.get_pos().y, camera.get_pos().z);
	glUniform1f(glGetUniformLocation(main_program, "material.shininess"), 64.0f);
	glUniform3f(glGetUniformLocation(main_program, "material.ambient"), 0.25f, 0.25f, 0.25f);
	glUniform3f(glGetUniformLocation(main_program, "material.diffuse"), 0.4f, 0.4f, 0.4f);
	glUniform3f(glGetUniformLocation(main_program, "material.specular"), 0.774597f, 0.774597f, 0.774597f);

	set_lights(main_program);

	mvp = camera.get_mat();
	model.identity();
	model = model.translate(vec4(50.0f, 15.0f, 10.0f)) * model.scale(vec4(0.05f, 0.05f, 0.05f));
	mi28_model.draw(main_program, mvp_location, model_loc, mvp, model);
	
	mvp = camera.get_mat();
	model.identity();
	plane.draw(main_program, mvp_location, model_loc, mvp, model);

	mvp = camera.get_mat();
	model.identity();
	model = model.translate(vec4(0.0f, 10.0f, 0.0f)) *  model.scale(vec4(0.1f, 0.1f, 0.1f));
	sphere_model.draw(main_program, mvp_location, model_loc, mvp, model);
	
	mvp = camera.get_mat();
	model.identity();
	model = model.translate(vec4(10.0f, 5.0f, 50.0f)) * model.scale(vec4(5.0f, 5.0f, 5.0f));
	crate_model.draw(main_program, mvp_location, model_loc, mvp, model);

	//mvp = camera.get_mat();
	//model.identity();
	//model = model.scale(vec4(0.1f, 0.1f, 0.1f));
	//sphere_model.draw(main_program, mvp_location, model_loc, mvp, model);

	//mvp = camera.get_mat();
	//model.identity();
	//model = model.translate(vec4(30.0f, 0.0f, 50.0f)) /* * model.scale(vec4(1.5f, 1.5f, 1.5f))*/ * model.rotate(90, vec4(1.0f, 0.0f, 0.0f));
	//crysis_model.draw(main_program, mvp_location, model_loc, mvp, model);

	glUseProgram(0);

	glUseProgram(light_program);
	glBindVertexArray(VAO);
	mvp_location = glGetUniformLocation(light_program, "mvp");
	model_loc = glGetUniformLocation(light_program, "model");
	GLuint light_color_loc = glGetUniformLocation(light_program, "light_color");
	for (int i = 0; i < point_lights.size(); ++i)
	{
		point_lights[i].draw_light_source(light_program, cube, camera, light_color_loc, mvp_location, model_loc);
	}
	for (int i = 0; i < spot_lights.size(); ++i)
	{
		spot_lights[i].draw_light_source(light_program, cube, camera, light_color_loc, mvp_location, model_loc);
	}
	glBindVertexArray(0);
	glUseProgram(0);

	glutSwapBuffers();
}

void init_lights()
{
	point_lights.push_back(Point_Light(vec4(10.0f, 20.0f, 5.0f), vec4(1.0f, 1.0f, 1.0f), 1.0f, 0.027f, 0.0028f));
	spot_lights.push_back(Spot_Light(vec4(40.0f, 10.0f, 15.0f), vec4(0.0f, -1.0, 0.0f), vec4(0.0f, 0.0f, -1.0f),
		vec4(1.0f, 0.0f, 0.0f), cosf(M_PI / 180.0f * 25.0f), 1.0f, 0.027f, 0.0028f));
	dir_lights.push_back(Dir_Light(vec4(0.0f, -1.0f, 0.0f), vec4(0.0f, 0.0f, 1.0f), vec4(0.2f, 0.2f, 0.2f)));
}

int main(int argc, char *argv[])
{
	//gen_grid
	cur_focus = f_camera;
	init_lights();
	camera.look_at(vec4(5.0f, 5.0f, -25.0f),
				   vec4(0.0f, 0.0f, 0.0f),
				   vec4(0.0f, 1.0f, 0.0f));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutGameModeString(get_game_mode_string().c_str());
	glutEnterGameMode();
	glutSetCursor(GLUT_CURSOR_NONE);
	glutWarpPointer(win_width / 2, win_height / 2);
	glutInitContextVersion(4, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		printf("Error: %s.\n", glewGetErrorString(err));
		return 1;
	}
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.12f, 0.34f, 0.35f, 0.0f);
	main_program = create_program("VS.txt", "FS.txt");
	light_program = create_program("VS_light.txt", "FS_light.txt");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sizeof(cube_vertices), &cube_vertices, GL_STATIC_DRAW);
	glBindVertexArray(VAO);
	attr_location = glGetAttribLocation(main_program, "position");
	glVertexAttribPointer(attr_location, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(attr_location);
	attr_location = glGetAttribLocation(main_program, "normal");
	glVertexAttribPointer(attr_location, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	glEnableVertexAttribArray(attr_location);
	glBindVertexArray(0);

	sphere_model = Model("Models\\Moon\\moon.obj");
	crate_model = Model("Models\\Crate\\crate1.obj");
	floor_model = Model("Models\\Cobblestones\\CobbleStones2.obj");
	crate_model.load_texture("Well Preserved Chesterfield - Color Map.png", "Well Preserved Chesterfield - Specular Map.png");
	//mi28_model = Model("Models\\Mi-28\\havoc.obj");
	//crysis_model = Model("Models\\Nanosuit\\nanosuit.blend");
	//crysis_model = Model("Models\\Crate\\crate1.obj");
	vector <Texture> textures;
	plane = Mesh(plane_vertices, plane_ind, textures);
	plane.load_texture("Models\\Plane", "Medievil Stonework - Color Map.png", "Medievil Stonework - Specular Map.png");
	cube = Mesh(cube_vertices, cube_ind, textures);

	glutDisplayFunc(render);
	glutKeyboardFunc(press_keys);
	glutKeyboardUpFunc(up_keys);
	glutPassiveMotionFunc(mouse_move);
	glutTimerFunc(40, timer, 0);
	glutMainLoop();
	return 0;
}