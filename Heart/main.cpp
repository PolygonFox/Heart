#include "general.h"

#include "graphics/window.h"
#include "graphics/shader.h"
#include "graphics/mesh.h"

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>

int main(int argc, char** args)
{
	using namespace Heart;
	using namespace Graphics;

	Window window;

	using namespace glm;

	
	Shader basicShader = Shader("assets/shaders/shader.vert", "assets/shaders/shader.frag");
	
	Mesh mesh = Mesh("assets/meshes/susan.blend", &basicShader);

	mat4 model;

	mat4 projection;
	projection = glm::perspective(45.0f, (float)640 / 480, 0.1f, 100.0f);

	mat4 view;
	view = translate(view, vec3(0, 0, -1));

	while (!window.shouldWindowClose())
	{
		window.clear();
		
		// Calculate MVP
		mat4 MVP = projection * view * model;

		glUniformMatrix4fv(basicShader.getUniformLocation("mvp"), 1, GL_FALSE, glm::value_ptr(MVP));

		model = rotate(model, 0.1f, vec3(1.0f, 1.0f, 0.0f));
		
		mesh.draw();
		

		window.update();
	}
	
	return 0;
}