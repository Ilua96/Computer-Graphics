#include <glew.h>
#include <freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector_matrix.h>
#include <cmath>
#include <camera.h>

GLuint program;
GLuint VAO;
GLuint VBO;
GLuint attr_location;
GLuint mvp_location;
int win_width = 1920;
int win_height = 1080;
Camera camera(70.0f, win_width, win_height, 0.1f, 500.0f);
//Camera camera(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

const int count_vertices = 806;
float vertices[count_vertices * 3]; 

void add_vertex(int i, float x, float y, float z)
{
	vertices[3 * i] = x;
	vertices[3 * i + 1] = y;
	vertices[3 * i + 2] = z;
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

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program);
	mat4 mvp;
	mvp = camera.get_mat();
	mvp_location = glGetUniformLocation(program, "mvp");
	glUniformMatrix4fv(mvp_location, 1, GL_TRUE, *(mvp.matrix));
	glDrawArrays(GL_LINES, 0, count_vertices);
	glUseProgram(0);
	glutSwapBuffers();
}

bool is_key_press[128];
void press_keys(unsigned char key, int x, int y)
{
	is_key_press[key] = true;
	float rotate_speed = 4.0f;
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

void read_all_file(char *file_name, char **text)
{
	FILE *input;
	input = fopen(file_name, "rb");
	fseek(input, 0, SEEK_END);
	int file_size = ftell(input);
	fseek(input, 0, SEEK_SET);
	*text = (char *)malloc(sizeof(char) *  file_size);
	fread(*text, sizeof(char), file_size, input);
}

void create_shader(GLuint shader, char **string, char *shader_name)
{
	glShaderSource(shader, 1, string, NULL);
	glCompileShader(shader);
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		printf("%s shader compile error.\n", shader_name);
		glDeleteShader(shader);
		return;
	}
}

void init_shader() 
{
	char *vs_text = NULL;
	read_all_file("VS.txt", &vs_text);

	char *fs_text = NULL;
	read_all_file("FS.txt", &fs_text);

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	create_shader(vertex_shader, &vs_text, "Vertex");

	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	create_shader(fragment_shader, &fs_text, "Fragment");

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	int link_status;
	glGetProgramiv(program, GL_LINK_STATUS, &link_status);
	if (link_status != GL_TRUE)
	{
		printf("LINK ERROR!\n");
		return;
	}
}

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(40, timer, 0);
}

int main(int argc, char *argv[])
{
	gen_grid();
	camera.look_at(vec4(5.0f, 10.0f, 90.0f),
				   vec4(0.0f, 0.0f, 0.0f),
				   vec4(0.0f, 1.0f, 0.0f));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutGameModeString("1920x1080:32");
	glutEnterGameMode();
	glutSetCursor(GLUT_CURSOR_NONE);
	glutInitContextVersion(4, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		printf("Error: %s.\n", glewGetErrorString(err));
		return 1;
	}

	glClearColor(0.12, 0.34, 0.35, 0);
	init_shader();
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count_vertices * 3, &vertices, GL_STATIC_DRAW);

	attr_location = glGetAttribLocation(program, "position");
	glVertexAttribPointer(attr_location, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attr_location);

	glutWarpPointer(win_width / 2, win_height / 2);
	glutDisplayFunc(render);
	glutKeyboardFunc(press_keys);
	glutKeyboardUpFunc(up_keys);
	glutPassiveMotionFunc(mouse_move);
	//glutTimerFunc(40, timer, 0);
	glutMainLoop();
	return 0;
}