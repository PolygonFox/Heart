#include "application.h"

namespace Heart {
	Application::Application()
	{
		this->init();
		while (!m_Window->shouldWindowClose())
		{
			m_Window->clear();
			this->tick();
			m_Window->update();
		}
	}

	Application::~Application()
	{
		delete m_ActiveCamera;
		delete m_ActiveScene;
		delete m_Window;
	}

	void Application::tick()
	{
		this->draw();
	}

	void Application::init()
	{
		Window* window = new Window("Game", SCREEN_WIDTH, SCREEN_HEIGHT);

		Shader* basicShader = new Shader("assets/shaders/shader.vert", "assets/shaders/shader.frag");

		Mesh* mesh = new Mesh("assets/meshes/susan.blend", &*basicShader);
		mesh->setPosition(vec3(0, 0, -1));

		Scene* scene = new Scene();
		scene->add(*mesh);

		Camera* camera = new Camera(45.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);
		camera->setPosition(0, 0, -2);

		m_ActiveScene = scene;
		m_ActiveCamera = camera;
		m_Window = window;
	}

	void Application::draw()
	{
		m_ActiveScene->draw(m_ActiveCamera);
	}
}