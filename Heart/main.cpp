#include "general.h"

#include "graphics/window.h"
#include "graphics/shader.h"
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <vector>
#include <stddef.h> // offsetof

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

int main(int argc, char** args)
{
	using namespace Heart;
	using namespace Graphics;

	Window window;

	using namespace glm;

	struct Vertex {
		Vertex(vec3 position, vec3 normal) : position(position), normal(normal)
		{

		}

		vec3 position;
		vec3 normal;
	};

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	// Assimp import object
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile("assets/meshes/susan.blend", aiProcess_Triangulate | aiProcess_GenSmoothNormals);
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

	
	Shader basicShader = Shader("assets/shaders/shader.vert", "assets/shaders/shader.frag");
	
	mat4 model;

	mat4 projection;
	projection = glm::perspective(45.0f, (float)640 / 480, 0.1f, 100.0f);

	mat4 view;
	view = translate(view, vec3(0, 0, -1));

	while (!window.shouldWindowClose())
	{
		window.clear();
		mat4 mvp = projection * view * model;
		glUniformMatrix4fv(basicShader.getUniformLocation("mvp"), 1, GL_FALSE, glm::value_ptr(mvp));

		//model = translate(model, vec3(-0.1, 0, 0));
		model = rotate(model, 0.1f, vec3(1.0f, 1.0f, 0.0f));
		
		basicShader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		window.update();
	}
	
	return 0;
}