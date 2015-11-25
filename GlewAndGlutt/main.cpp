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

GLuint main_program;
GLuint light_program;
GLuint VAO, plane_VAO;
GLuint VBO, plane_VBO;
GLuint attr_location;
GLuint mvp_location;
int win_width = 1920;
int win_height = 1080;
Camera camera(70.0f, win_width, win_height, 0.1f, 500.0f);
//Camera camera(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 500.0f);  


const int count_cube_vertices = 36;//806;
//float vertices[count_vertices * 3]; 
float cube_vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

const int count_plane_vertices = 6;
float plane_vertices[] = {
	-100.0f,  0.0f, -100.0f,  0.0f,  1.0f,  0.0f,
	-100.0f,  0.0f, 100.0f,  0.0f,  1.0f,  0.0f,
	100.0f,  0.0f,  100.0f,  0.0f,  1.0f,  0.0f,
	-100.0f,  0.0f,  -100.0f,  0.0f,  1.0f,  0.0f,
	100.0f,  0.0f,  100.0f,  0.0f,  1.0f,  0.0f,
	100.0f,  0.0f, -100.0f,  0.0f,  1.0f,  0.0f
};

//float vertices[count_vertices * 3] = {
//	-0.5f, -0.5f, -0.5f,
//	0.5f, -0.5f, -0.5f,
//	0.5f,  0.5f, -0.5f,
//	0.5f,  0.5f, -0.5f,
//	-0.5f,  0.5f, -0.5f,
//	-0.5f, -0.5f, -0.5f,
//
//	-0.5f, -0.5f,  0.5f,
//	0.5f, -0.5f,  0.5f,
//	0.5f,  0.5f,  0.5f,
//	0.5f,  0.5f,  0.5f,
//	-0.5f,  0.5f,  0.5f,
//	-0.5f, -0.5f,  0.5f,
//
//	-0.5f,  0.5f,  0.5f,
//	-0.5f,  0.5f, -0.5f,
//	-0.5f, -0.5f, -0.5f,
//	-0.5f, -0.5f, -0.5f,
//	-0.5f, -0.5f,  0.5f,
//	-0.5f,  0.5f,  0.5f,
//
//	0.5f,  0.5f,  0.5f,
//	0.5f,  0.5f, -0.5f,
//	0.5f, -0.5f, -0.5f,
//	0.5f, -0.5f, -0.5f,
//	0.5f, -0.5f,  0.5f,
//	0.5f,  0.5f,  0.5f,
//
//	-0.5f, -0.5f, -0.5f,
//	0.5f, -0.5f, -0.5f,
//	0.5f, -0.5f,  0.5f,
//	0.5f, -0.5f,  0.5f,
//	-0.5f, -0.5f,  0.5f,
//	-0.5f, -0.5f, -0.5f,
//
//	-0.5f,  0.5f, -0.5f,
//	0.5f,  0.5f, -0.5f,
//	0.5f,  0.5f,  0.5f,
//	0.5f,  0.5f,  0.5f,
//	-0.5f,  0.5f,  0.5f,
//	-0.5f,  0.5f, -0.5f
//};

void add_vertex(int i, float x, float y, float z)
{
	cube_vertices[3 * i] = x;
	cube_vertices[3 * i + 1] = y;
	cube_vertices[3 * i + 2] = z;
};

void gen_grid()
{	
	int j = 0;
	for (int i = -1000; i <= 1000; i += 10, j += 4)
	{
		add_vertex(j, i, 0, -1000);
		add_vertex(j + 1, i, 0, 1000);
		add_vertex(j + 2, -1000, 0, i);
		add_vertex(j + 3, 1000, 0, i);
	}
	add_vertex(j, 0, 0, 0);
	add_vertex(j + 1, 0, 1000, 0);
}

bool is_key_press[128];
void press_keys(unsigned char key, int x, int y)
{
	is_key_press[key] = true;
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
	float rotate_speed = 3.0f;
	float move_speed = 1.0f;
	for (int i = 0; i < 128; ++i)
	{
		if (is_key_press[i])
		{
			switch (i)
			{
			case 'w':
				camera.move(vec4(camera.get_dir().x, 0.0f, camera.get_dir().z).normalize() * -move_speed);
				break;
			case 's':
				camera.move(vec4(camera.get_dir().x, 0.0f, camera.get_dir().z).normalize() * move_speed);
				break;
			case 'd':
				camera.move(camera.get_right() * move_speed);
				break;
			case 'a':
				camera.move(camera.get_right() * -move_speed);
				break;
			case ' ':
				camera.move(vec4(0.0f, 1.0f * move_speed, 0.0f));
				break;
			case 'c':
				camera.move(vec4(0.0f, -1.0f * move_speed, 0.0f));
				break;
			case 'e':
				camera.rotate(rotate_speed, vec4(0.0f, 1.0f, 0.0f));
				break;
			case 'q':
				camera.rotate(-rotate_speed, vec4(0.0f, 1.0f, 0.0f));
				break;
			case 'r':
				camera.rotate(-rotate_speed, camera.get_right());
				break;
			case 'f':
				camera.rotate(rotate_speed, camera.get_right());
				break;
			case 'z':
				camera.zoom(5.0f);
				break;
			case 'x':
				camera.zoom(-5.0f);
				break;
			case 'g':
				camera.set_normal_zoom();
				break;
			case 27:
				exit(0);
				break;
			}
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

void render()
{
	mat4 mvp, model;
	model.identity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(main_program);
	mvp_location = glGetUniformLocation(light_program, "mvp");
	model = model.translate(vec4(0.0f, 5.0f, 0.0f)) * model.scale(vec4(3.0f, 3.0f, 3.0f));
	mvp = camera.get_mat() * model;
	glUniform3f(glGetUniformLocation(main_program, "view_pos"), camera.get_pos().x, camera.get_pos().y, camera.get_pos().z);
	// Set material properties
	glUniform1f(glGetUniformLocation(main_program, "material.shininess"), 32.0f);
	glUniform3f(glGetUniformLocation(main_program, "material.ambient"), 1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation(main_program, "material.diffuse"), 1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation(main_program, "material.specular"), 0.5f, 0.5f, 0.5f);
	glUniform3f(glGetUniformLocation(main_program, "point_lights[0].pos"), 10.0f, 10.0f, 5.0f);
	glUniform3f(glGetUniformLocation(main_program, "point_lights[0].color"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(main_program, "point_lights[0].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(main_program, "point_lights[0].linear"), 0.09);
	glUniform1f(glGetUniformLocation(main_program, "point_lights[0].quadr"), 0.032);
	//GLint object_color_loc = glGetUniformLocation(main_program, "object_color");
	//GLint light_color_loc = glGetUniformLocation(main_program, "light_color");
	//GLint light_pos_loc = glGetUniformLocation(main_program, "light_pos");
	GLint model_loc = glGetUniformLocation(main_program, "model");
	//GLint view_pos_loc = glGetUniformLocation(main_program, "view_pos");
	//glUniform3f(object_color_loc, 0.0f, 0.5f, 0.0f);
	//glUniform3f(light_color_loc, 1.0f, 1.0f, 1.0f);
	//glUniform3f(light_pos_loc, 10.0f, 10.0f, 5.0f);
	//glUniform3f(view_pos_loc, camera.get_pos().x, camera.get_pos().y, camera.get_pos().z);
	glUniformMatrix4fv(mvp_location, 1, GL_TRUE, *(mvp.matrix));
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, *(model.matrix));
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, count_cube_vertices);
	glBindVertexArray(0);

	glBindVertexArray(plane_VAO);
	mvp = camera.get_mat();
	glUniformMatrix4fv(mvp_location, 1, GL_TRUE, *(mvp.matrix));
	model.identity();
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, *(model.matrix));
	glDrawArrays(GL_TRIANGLES, 0, count_plane_vertices);
	glBindVertexArray(0);
	
	glUseProgram(0);

	glUseProgram(light_program);
	model.identity();
	model = model.translate(vec4(10.0f, 10.0f, 5.0f, 0.0f));
	mvp = camera.get_mat() * model;
	mvp_location = glGetUniformLocation(light_program, "mvp");
	glUniformMatrix4fv(mvp_location, 1, GL_TRUE, *(mvp.matrix));
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, count_cube_vertices);
	glBindVertexArray(0);
	glUseProgram(0);

	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	//gen_grid();
	camera.look_at(vec4(5.0f, 5.0f, -25.0f),
				   vec4(0.0f, 0.0f, 0.0f),
				   vec4(0.0f, 1.0f, 0.0f));
	//camera.get_mat();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
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

	glGenVertexArrays(1, &plane_VAO);
	glGenBuffers(1, &plane_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, plane_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sizeof(plane_vertices), &plane_vertices, GL_STATIC_DRAW);
	glBindVertexArray(plane_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, plane_VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	attr_location = glGetAttribLocation(main_program, "position");
	glVertexAttribPointer(attr_location, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(attr_location);
	attr_location = glGetAttribLocation(main_program, "normal");
	glVertexAttribPointer(attr_location, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	glEnableVertexAttribArray(attr_location);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glutDisplayFunc(render);
	glutKeyboardFunc(press_keys);
	glutKeyboardUpFunc(up_keys);
	glutPassiveMotionFunc(mouse_move);
	glutTimerFunc(40, timer, 0);
	glutMainLoop();
	return 0;
}