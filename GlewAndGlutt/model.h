#pragma once
#include <iostream>
#include <glew.h>
#include <vector>
#include <vector_matrix.h>
#include <mesh.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>

class Model
{
	public:
		vector <Mesh> meshes;
		Model() {};
		Model(string path)
		{
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_SplitLargeMeshes);
			if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
				return;
			}
			process_node(scene->mRootNode, scene);
		}
	
		void draw(GLuint mvp_loc, GLuint model_loc, mat4 &mvp, mat4 &model)
		{
			for (int i = 0; i < meshes.size(); ++i)
				meshes[i].draw(mvp_loc, model_loc, mvp, model);
		}
	
	private:	
		void process_node(aiNode* node, const aiScene* scene)
		{
			for (GLuint i = 0; i < node->mNumMeshes; ++i)
			{
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				meshes.push_back(process_mesh(mesh, scene));
			}
			for (GLuint i = 0; i < node->mNumChildren; ++i)
			{
				process_node(node->mChildren[i], scene);
			}
	
		}
	
		Mesh process_mesh(aiMesh* mesh, const aiScene* scene)
		{
			vector <Vertex> vertices;
			vector <GLuint> indices;
			cout << mesh->mNumVertices << endl << flush;
			for (GLuint i = 0; i < mesh->mNumVertices; ++i)
			{
				Vertex vertex;
				vertex.pos = vec4(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
				vertex.normal = vec4(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
				vertices.push_back(vertex);
			}
			for (GLuint i = 0; i < mesh->mNumFaces; ++i)
			{
				aiFace face = mesh->mFaces[i];
				for (GLuint j = 0; j < face.mNumIndices; ++j)
					indices.push_back(face.mIndices[j]);
			}
			return Mesh(vertices, indices);
		}
};