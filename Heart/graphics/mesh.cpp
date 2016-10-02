#include "mesh.h"
#include "../general.h"

#include <iostream>
#include <vector>
#include <stddef.h> // offsetof

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

namespace Heart {
	namespace Graphics {

		using namespace glm;

	
		Mesh::Mesh(const char* fileName, Material* material)
			: m_material(material)
		{
			Geometry geometry = Mesh::getGeometry(fileName);

			GLuint VAO, VBO, IBO;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &IBO);

			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * geometry.vertices.size(), &geometry.vertices[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, geometry.indices.size() * sizeof(GLuint), &geometry.indices[0], GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::position));
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::normal));
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::texcoord));

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			glBindVertexArray(0);

			m_VAO = VAO;
			m_numIndices = geometry.indices.size();
		}

		Mesh::Mesh(Geometry& geometry, Material* material)
			: m_material(material)
		{
			GLuint VAO, VBO, IBO;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &IBO);

			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * geometry.vertices.size(), &geometry.vertices[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, geometry.indices.size() * sizeof(GLuint), &geometry.indices[0], GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::position));
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::normal));
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::texcoord));

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			glBindVertexArray(0);

			m_VAO = VAO;
			m_numIndices = geometry.indices.size();
		}

		Geometry Mesh::getGeometry(const char* fileName)
		{
			std::vector<Vertex> vertices;
			std::vector<GLuint> indices;

			// Assimp import object
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
			if (!scene)
			{
				LOG(importer.GetErrorString());
			}

			const aiMesh* mesh = scene->mMeshes[0];

			// Load texture?
			aiString path;
			scene->mMaterials[0]->GetTexture(aiTextureType_DIFFUSE, 0, &path);

			LOG(path.C_Str());

			for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				Vertex v;
				v.position = vec3(mesh->mVertices[i].x, mesh->mVertices[i].z, mesh->mVertices[i].y); // Z up
				v.normal = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

				if (mesh->HasTextureCoords(0)) {
					v.texcoord = vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
				}

				vertices.push_back(v);
			}

			for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			{

				indices.push_back(mesh->mFaces[i].mIndices[0]);
				indices.push_back(mesh->mFaces[i].mIndices[1]);
				indices.push_back(mesh->mFaces[i].mIndices[2]);
			}



			return Geometry(vertices, indices);
		}

		Mesh::~Mesh() {

		}

		void Mesh::draw()
		{
			
			m_material->use(getMatrix());
			glBindVertexArray(m_VAO);
				glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

		Material* Mesh::getMaterial()
		{
			return m_material;
		}

	}
}