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
		void init();
		void draw();

	private:
		char* m_Name = "Test Application!";
		Scene* m_ActiveScene;
		Window* m_Window;
		Camera* m_ActiveCamera;
	};

}