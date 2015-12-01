#pragma once
#include <glew.h>
#include <vector>
#include <vector_matrix.h>

struct Vertex {
	vec4 pos;
	vec4 normal;
};

class Mesh {
	public:
		vector <float> vertices;
		vector <GLuint> indices;
		GLuint VAO, VBO, EBO;
		Mesh() {};
		Mesh(vector <float> Vertices, vector <GLuint> Indices)
		{
			vertices = Vertices;
			indices = Indices;
			setup();
		}
		void draw(GLuint program)
		{
			//glUniform1f(glGetUniformLocation(program, "material.shininess"), 16.0f);
			glBindVertexArray(VAO);
			//glDrawArrays(GL_TRIANGLES, 0, 6);
			glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

	private:
		
		void setup()
		{
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
		
			glBindVertexArray(0);

			//glGenVertexArrays(1, &plane_VAO);
			//glGenBuffers(1, &plane_VBO);
			//glBindBuffer(GL_ARRAY_BUFFER, plane_VBO);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * plane_vertices.size(), &plane_vertices[0], GL_STATIC_DRAW);
			//glBindVertexArray(plane_VAO);
			//glBindBuffer(GL_ARRAY_BUFFER, plane_VBO);
			////glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
			////attr_location = glGetAttribLocation(main_program, "position");
			//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
			//glEnableVertexAttribArray(0);
			////attr_location = glGetAttribLocation(main_program, "normal");
			//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
			//glEnableVertexAttribArray(1);
			////glEnableVertexAttribArray(0);
			//glBindVertexArray(0);
		}
};