#pragma once

#include "scene.h"
#include "camera.h"

#include "graphics\window.h"


// Forward declaration
class Window;

namespace Heart {

	using namespace Graphics;

	class Application {
	public:
		Application();
		~Application();
		void tick();
		void init(Scene* scene);
		void draw();
		static Application* instance;
		static Camera* getActiveCamera() {
			return Application::instance->m_ActiveCamera;
		}
		static int getTime()
		{
			return Application::instance->m_time;
		}

	private:
		char* m_Name = "Test Application!";
		Scene m_Scene;
		Window* m_Window;
		Camera* m_ActiveCamera;
		int m_time;
	
	};

}