#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <glew.h>
#include <vector_matrix.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <SOIL.h>


struct Vertex {
	vec4 pos;
	vec4 normal;
	float tex_x, tex_y;
	Vertex(vec4 pos, vec4 normal, float tex_x, float tex_y) : pos(pos), normal(normal), tex_x(tex_x), tex_y(tex_y) {}
	Vertex() {};
};

struct Texture {
	GLuint id;
	string type;
	aiString path;
	Texture(GLuint id, string type, aiString path) : id(id), type(type), path(path) {}
	Texture() {};
	Texture(string directory, string texture_name, string texture_type)
	{
		string filename;
		filename = directory + "\\\\" + texture_name;
		cout << filename << endl;
		GLuint texture_id;
		glGenTextures(1, &texture_id);
		int width, height;
		unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		SOIL_free_image_data(image);
		id = texture_id;
		type = texture_type;
		path = texture_name;
	}
};


class Mesh {
	public:
		vector <Vertex> vertices;
		vector <GLuint> indices;
		vector <Texture> textures;
		Mesh() {};
		Mesh(vector <Vertex> Vertices, vector <GLuint> Indices, vector <Texture> Textures)
		{
			vertices = Vertices;
			indices = Indices;
			textures = Textures;


			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, 10 * sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), 0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (GLvoid*)(4 * sizeof(float)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (GLvoid*)(8 * sizeof(float)));

			glBindVertexArray(0);
		}
		void draw(GLuint program, GLuint mvp_loc, GLuint model_loc, mat4 &mvp, mat4 &model)
		{
			GLuint diffuse_count = 1;
			GLuint specular_count = 1;
			for (GLuint i = 0; i < textures.size(); ++i)
			{
				glActiveTexture(GL_TEXTURE0 + i); 
				stringstream ss;
				string number;
				string name = textures[i].type;
				if (name == "texture_diffuse")
					ss << diffuse_count++; 
				else if (name == "texture_specular")
					ss << specular_count++; 
				number = ss.str();
				glUniform1i(glGetUniformLocation(program, (name + number).c_str()), i);
				//cout << (name + number) << endl;
				glBindTexture(GL_TEXTURE_2D, textures[i].id);
			}

			glBindVertexArray(VAO);
			glUniformMatrix4fv(mvp_loc, 1, GL_TRUE, *((mvp * model).matrix));
			glUniformMatrix4fv(model_loc, 1, GL_TRUE, *(model.matrix));
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			for (GLuint i = 0; i < textures.size(); ++i)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

		void load_texture(string directory, string dif_tex, string spec_tex)
		{
			for (int i = 0; i < textures.size(); ++i)
			{
				glDeleteTextures(1, &textures[i].id);
			}
			textures.resize(0);
			textures.push_back(Texture(directory, dif_tex, "texture_diffuse"));
			textures.push_back(Texture(directory, spec_tex, "texture_specular"));
		}

	private:
		GLuint VAO, VBO, EBO;
};

