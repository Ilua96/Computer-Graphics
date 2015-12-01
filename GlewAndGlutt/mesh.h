#pragma once
#include <glew.h>
#include <vector>
#include <vector_matrix.h>

struct Vertex {
	//float pos_x, pos_y, pos_z, nor_x, nor_y, nor_z;
	vec4 pos;
	vec4 normal;
	Vertex(vec4 pos, vec4 normal) : pos(pos), normal(normal) {}
	Vertex() {};
};

class Mesh {
	public:
		vector <Vertex> vertices;
		vector <GLuint> indices;
		Mesh() {};
		Mesh(vector <Vertex> Vertices, vector <GLuint> Indices)
		{
			vertices = Vertices;
			indices = Indices;
			setup();
		}
		void draw(GLuint program)
		{
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

	private:
		GLuint VAO, VBO, EBO;
		void setup()
		{
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(4 * sizeof(float)));
		
			glBindVertexArray(0);
		}
};