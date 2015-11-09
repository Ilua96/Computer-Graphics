#include <glew.h>
#include <freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector_matrix.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <camera.h>
#include <vector>

GLuint program;
GLuint VAO;
GLuint VBO;
GLuint attr_location;
GLuint mvp_location;
Camera  camera(45.0f, 800,  600, 0.1f, 100.0f);

const int count_vertices = 30;
//float vertices[] = {
//	-1.0f, -1.0f, -0.5f,
//	0.0f,  1.0f, -0.5f,
//	1.0f, -1.0f, -0.5f,
//	1.0f, 1.0f, -0.5f,
//};

//vector <float> vertices;
float vertices[count_vertices * 3] = {
	0.0f, -100.0f, 0.0f,
	0.0f, 100.0f, 0.0f,

	0.0f, 0.0f, -100.0f,
	0.0f, 0.0f, 100.0f,
	- 100.0f, 0.0f, 0.0f,
	100.0f, 0.0f, 0.0f,

	-100.0f, 0.0f, 1.0f,
	100.0f, 0.0f, 1.0f,
	-100.0f, 0.0f, -1.0f,
	100.0f, 0.0f, -1.0f,
	-100.0f, 0.0f, 2.0f,
	100.0f, 0.0f, 2.0f,
	-100.0f, 0.0f, -2.0f,
	100.0f, 0.0f, -2.0f,
	-100.0f, 0.0f, 3.0f,
	100.0f, 0.0f, 3.0f,
	-100.0f, 0.0f, -3.0f,
	100.0f, 0.0f, -3.0f,

	1.0f, 0.0f, -100.0f,
	1.0f, 0.0f, 100.0f,
	-1.0f, 0.0f, -100.0f,
	-1.0f, 0.0f, 100.0f,
	-2.0f, 0.0f, -100.0f,
	-2.0f, 0.0f, 100.0f,
	-3.0f, 0.0f, -100.0f,
	-3.0f, 0.0f, 100.0f,
	2.0f, 0.0f, -100.0f,
	2.0f, 0.0f, 100.0f,
	3.0f, 0.0f, -100.0f,
	3.0f, 0.0f, 100.0f,


	//-0.5f, -0.5f, -0.5f,  
	//0.5f, -0.5f, -0.5f, 
	//0.5f,  0.5f, -0.5f, 
	//0.5f,  0.5f, -0.5f,  
	//-0.5f,  0.5f, -0.5f, 
	//-0.5f, -0.5f, -0.5f, 

	//-0.5f, -0.5f,  0.5f, 
	//0.5f, -0.5f,  0.5f, 
	//0.5f,  0.5f,  0.5f,  
	//0.5f,  0.5f,  0.5f, 
	//-0.5f,  0.5f,  0.5f,  
	//-0.5f, -0.5f,  0.5f, 

	//-0.5f,  0.5f,  0.5f, 
	//-0.5f,  0.5f, -0.5f, 
	//-0.5f, -0.5f, -0.5f,  
	//-0.5f, -0.5f, -0.5f,  
	//-0.5f, -0.5f,  0.5f,  
	//-0.5f,  0.5f,  0.5f,  

	//0.5f,  0.5f,  0.5f, 
	//0.5f,  0.5f, -0.5f,  
	//0.5f, -0.5f, -0.5f, 
	//0.5f, -0.5f, -0.5f,  
	//0.5f, -0.5f,  0.5f, 
	//0.5f,  0.5f,  0.5f, 

	//-0.5f, -0.5f, -0.5f,  
	//0.5f, -0.5f, -0.5f, 
	//0.5f, -0.5f,  0.5f,  
	//0.5f, -0.5f,  0.5f, 
	//-0.5f, -0.5f,  0.5f,  
	//-0.5f, -0.5f, -0.5f,

	//-0.5f,  0.5f, -0.5f,  
	//0.5f,  0.5f, -0.5f,  
	//0.5f,  0.5f,  0.5f,  
	//0.5f,  0.5f,  0.5f,  
	//-0.5f,  0.5f,  0.5f, 
	//-0.5f,  0.5f, -0.5f, 
};

void gen()
{	
	//vertices.push_back(0.0f); vertices.push_back(-100.0f); vertices.push_back(0.0f);
	//vertices.push_back(0.0f); vertices.push_back(100.0f); vertices.push_back(0.0f);
	//vertices.push_back(0.0f); vertices.push_back(-100.0f); vertices.push_back(0.0f);
	//vertices.push_back(0.0f); vertices.push_back(100.0f); vertices.push_back(0.0f);
	//for (int i = -100; i <= 100; i += 1)
	//{
	//	vertices.push_back(i);
	//	vertices.push_back(0.0f);
	//	vertices.push_back(-100.0f);

	//	vertices.push_back(i);
	//	vertices.push_back(0.0f);
	//	vertices.push_back(100.0f);

	//	vertices.push_back(-100.0f);
	//	vertices.push_back(0.0f);
	//	vertices.push_back(i);

	//	vertices.push_back(100.0f);
	//	vertices.push_back(0.0f);
	//	vertices.push_back(i);
	//}
	//vertices.push_back(0.0f);
	//vertices.push_back(-100.0f);
	//vertices.push_back(0.0f);

	//vertices.push_back(0.0f);
	//vertices.push_back(100.0f);
	//vertices.push_back(0.0f);


	//int j = 0;
	//for (int i = -100; i <= 100; i += 1)
	//{
	//	vertices[3 * j] = i;
	//	vertices[3 * j + 1] = 0.0f;
	//	vertices[3 * j + 2] = -100.0f;

	//	vertices[3 * (j + 1)] = i;
	//	vertices[3 * (j + 1) + 1] = 0.0f;
	//	vertices[3 * (j + 1) + 2] = 100.0f;

	//	vertices[3 * (j + 2)] = -100.0f;
	//	vertices[3 * (j + 2) + 1] = 0.0f;
	//	vertices[3 * (j + 2) + 2] = i;

	//	vertices[3 * (j + 3)] = 100.0f;
	//	vertices[3 * (j + 3) + 1] = 0.0f;
	//	vertices[3 * (j + 3) + 2] = i;
	//	j += 4;
	//}
	//cout << j;
	//vertices[3 * j] = 0.0f;
	//vertices[3 * j + 1] = -100.0f;
	//vertices[3 * j + 2] = 0.0f;

	//vertices[3 * (j + 1)] = 0.0f;
	//vertices[3 * (j + 1) + 1] = 100.0f;
	//vertices[3 * (j + 1) + 2] = 0.0f;
}

float b = 1;
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);
	mat4 model, mvp, view, projection;
	model.identity();
	view.identity();
	projection.identity();
	//model = model.rotate(1, b);
	//model = model.rotate(0, 2*b);
	//model = model.rotate(0, -15.0f);
	//model = model.rotate(1, 10.0f);
	model = model.rotate(b * 10.0f, vec4(0.5f, 1.0f, 0.0f));
	b += 0.05;
	view = view.translation(vec4(0.0f, 0.0f, -3.0f));
	projection = projection.perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
	
	glm::mat4 view1;
	/*view1 = glm::translate(view1, glm::vec3(0.0f, 0.0f, -3.0f));*/
	view1 = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 model1;
	model1 = glm::rotate(model1, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 projection1;
	projection1 = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	
	mat4 mvp1;
	//mvp = model * view * projection;
	mvp1 = (projection * view).transpose();
	//camera.move(vec4(0.0f, 0.0f, -0.04f));
	mvp = camera.get_mat();
	//mvp1 = (projection1 * view1); //* model1;
	//for (int i = 0; i < 4; ++i)
	//{
	//	for (int j = 0; j < 4; ++j)
	//	{
	//		cout << mvp1[i][j] << "|" << mvp[i][j] << "  ";
	//	}
	//	cout << endl;
	//}
	//cout << endl << endl;

	//glm::mat4 trans;
	//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

	//mvp = mvp.scale(vec4(0.5f, 0.5f, 0.5f));
	//mvp = mvp.rotate(2, b * 1);
	//b += 0.04;
	//mvp = mvp.translation(vec4(0, 0.25, 0));

	mvp_location = glGetUniformLocation(program, "mvp");

	//glm::mat4 trans;
	////trans = glm::rotate(trans, 90.0f, glm::vec3(0.0, 0.0, 1.0));
	//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

	glUniformMatrix4fv(mvp_location, 1, GL_FALSE, *(mvp.matrix));
	glDrawArrays(GL_LINES, 0, count_vertices);
	glUseProgram(0);
	glutSwapBuffers();
}

void PressKeys(unsigned char key, int x, int y)
{
	float speed = 0.5f;
	switch(key)
	{
		case 'w':
			camera.move(vec4(camera.dir.x, 0.0f, camera.dir.z) * speed);
			break;
		case 's':
			camera.move(vec4(camera.dir.x, 0.0f, camera.dir.z) * -speed);
			break;
		case 'd':
			camera.move(camera.right * -speed);
			break;
		case 'a':
			camera.move(camera.right * speed);
			break;
		case ' ':
			camera.move(vec4(0.0f, 1.0f * speed, 0.0f));
			break;
		case 'c':
			camera.move(vec4(0.0f, -1.0f * speed, 0.0f));
			break;
		case 'e':
			camera.rotate(15.0f * speed, vec4(0.0f, 1.0f, 0.0f));
			break;
		case 'q':
			camera.rotate(-15.0f * speed, vec4(0.0f, 1.0f, 0.0f));
			break;
		case 'r':
			camera.rotate(15.0f * speed, camera.right);//vec4(camera.right.x, 0.0f, camera.right.z));
			break;
		case 'f':
			camera.rotate(-15.0f * speed, camera.right);//vec4(camera.right.x, 0.0f, camera.right.z));
			break;
		default:
			glutPostRedisplay();
			break;
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
	gen();
	//for (int i = 0; i < 30/*3 * count_vertices + 3*/; i += 3)
	//{
	//	cout << vertices[i] << " " << vertices[i + 1] << " " << vertices[i + 2] << endl;
	//}
	//cout << vertices.size() / 3 << endl;
	//for (int i = 0; i < vertices.size(); ++i)
	//{
	//	cout << vertices[i] << " ";// << vertices[i + 1] << " " << vertices[i + 2] << endl;
	//}
	camera.look_at(vec4(0.0f, 0.0f, 3.0f),
				   vec4(0.0f, 0.0f, 0.0f),
				   vec4(0.0f, -1.0f, 0.0f));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitContextVersion(4, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("Test triangle");
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		printf("Error: %s.\n", glewGetErrorString(err));
		return 1;
	}
	glClearColor(0.12, 0.34, 0.35, 0);
	init_shader();
	glEnable(GL_DEPTH_TEST);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count_vertices * 3, &vertices, GL_STATIC_DRAW);

	attr_location = glGetAttribLocation(program, "position");
	glVertexAttribPointer(attr_location, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attr_location);
	glutDisplayFunc(render);
	glutKeyboardFunc(PressKeys);
	glutTimerFunc(40, timer, 0);
	glutMainLoop();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDisableVertexAttribArray(attr_location);
	return 0;
}