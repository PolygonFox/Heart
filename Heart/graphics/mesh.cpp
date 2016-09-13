#include "mesh.h"


#include <vector>
#include <stddef.h> // offsetof

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

namespace Heart {
	namespace Graphics {

		using namespace glm;

		struct Vertex {
			Vertex(vec3 position, vec3 normal) : position(position), normal(normal)
			{

			}

			vec3 position;
			vec3 normal;
		};

		Mesh::Mesh(const char* fileName, Shader* shader)
			: m_Shader(shader)
		{
			std::vector<Vertex> vertices;
			std::vector<GLuint> indices;

			// Assimp import object
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_GenSmoothNormals);
			if (!scene)
			{
				LOG(importer.GetErrorString());
			}

			const aiMesh* mesh = scene->mMeshes[0];

			for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				vertices.push_back(
					Vertex(
						vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z),

						vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z)
						)
					);
			}

			for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			{

				indices.push_back(mesh->mFaces[i].mIndices[0]);
				indices.push_back(mesh->mFaces[i].mIndices[1]);
				indices.push_back(mesh->mFaces[i].mIndices[2]);
			}

			GLuint VAO, VBO, IBO;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &IBO);

			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::position));
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::normal));
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);

			glBindVertexArray(0);

			m_VAO = VAO;
			m_numIndices = indices.size();
		}

		Mesh::~Mesh() {

		}

		void Mesh::draw()
		{
			m_Shader->use();
			glBindVertexArray(m_VAO);
			glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

	}
}