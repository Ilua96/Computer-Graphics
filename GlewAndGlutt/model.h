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
#include <SOIL.h>

class Model
{
	public:
		Model() {};
		Model(string path)
		{
			cout << endl << "Begin load - " << path << endl;
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals);
			if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
				return;
			}
			directory = path.substr(0, path.find_last_of('\\'));
			process_node(scene->mRootNode, scene);
			cout << "END." << endl << endl;
		}

		void load_texture(string dif_tex, string spec_tex, string normal_map = "")
		{
			for (int i = 0; i < meshes.size(); ++i)
			{
				meshes[i].load_texture(directory, dif_tex, spec_tex, normal_map);
			}
		}
	
		void draw(GLuint program, GLuint mvp_loc, GLuint model_loc, mat4 &mvp, mat4 &model)
		{
			for (int i = 0; i < meshes.size(); ++i)
				meshes[i].draw(program, mvp_loc, model_loc, mvp, model);
		}
	
	private:	
		vector <Mesh> meshes;
		string directory;
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
			vector <Texture> textures;
			cout << "Load vertices";
			for (GLuint i = 0; i < mesh->mNumVertices; ++i)
			{
				Vertex vertex;
				vertex.pos = vec4(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
				vertex.normal = vec4(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
				if (mesh->mTextureCoords[0]) 
				{
					vertex.tex_x = mesh->mTextureCoords[0][i].x;
					vertex.tex_y = mesh->mTextureCoords[0][i].y;
				}
				else
				{
					vertex.tex_x = 0.0f;
					vertex.tex_y = 0.0f;
				}
				vertices.push_back(vertex);
			}
			cout << "end" << endl;
			cout << "Load indices ";
			for (GLuint i = 0; i < mesh->mNumFaces; ++i)
			{
				aiFace face = mesh->mFaces[i];
				for (GLuint j = 0; j < face.mNumIndices; ++j)
					indices.push_back(face.mIndices[j]);
			}
			cout << "end" << endl;
			if (mesh->mMaterialIndex >= 0)
			{
				aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
				vector <Texture> diffuse_maps = load_material_textures(material, aiTextureType_DIFFUSE, "texture_diffuse");
				textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());
				vector <Texture> specular_maps = load_material_textures(material, aiTextureType_SPECULAR, "texture_specular");
				textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());
			}
			return Mesh(vertices, indices, textures);
		}

		vector<Texture> load_material_textures(aiMaterial* mat, aiTextureType type, string type_name)
		{
			vector <Texture> textures;
			for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
			{
				aiString str;
				mat->GetTexture(type, i, &str);
				Texture texture;
				
				const char* path = str.C_Str();
				string filename = string(path);
				textures.push_back(Texture(directory, filename, type_name));
			}
			return textures;
		}
};


