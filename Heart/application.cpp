#include "application.h"
#include <glm\gtc\matrix_transform.hpp>

#include "input.h"
#include "resourcemanager.h"

namespace Heart {

	Geometry generateRail(const std::vector<vec3> &curvePoints, const Geometry &sourceGeo, vec3 offset, float scale)
	{
		// Get points
		float step = 0.005f;
		std::vector<vec3> points;
		for (float i = 0.0f; i < 1.0f + step; i += step)
		{
			vec3 point = glm::pow(1 - i, 3) * curvePoints[0] + 3 * glm::pow(1 - i, 2)*i*curvePoints[1] + 3 * (1 - i)*glm::pow(i, 2) * curvePoints[2] + glm::pow(i, 3) * curvePoints[3];
			points.push_back(point);
		}

		// Generate Geometry
		Geometry geo;



		int numVertices = sourceGeo.vertices.size();
		int numIndices = sourceGeo.indices.size();

		for (int j = 0; j < points.size(); j++)
		{
			// Create new vertices
			for (int i = 0; i < sourceGeo.vertices.size(); i++)
			{
				mat4 mat;
				vec3 dir;

				// Start punt 
				if (j - 1 < 0)
				{
					dir = glm::normalize(points[j + 1] - points[j]);
					mat = glm::lookAt(points[j + 1], points[j], vec3(0, 1, 0));
				}
				else
				{
					dir = glm::normalize(points[j] - points[j - 1]);
					mat = glm::lookAt(points[j], points[j - 1], vec3(0, 1, 0));
				}

				vec3 right = glm::normalize(glm::cross(dir, vec3(0, 1, 0)));
				
				vec3 offset2;
				offset2 = right*offset.x + vec3(0, 1, 0) * offset.y + dir * offset.z;
				
				vec3 pos = vec3(vec4(sourceGeo.vertices[i].position*scale, 1.0f) * mat);

				geo.vertices.push_back(
					Vertex(pos + points[j] + offset2, vec3(vec4(sourceGeo.vertices[i].position, 1.0) * mat), vec2(sourceGeo.vertices[i].texcoord.x, sourceGeo.vertices[i].texcoord.y + j * sourceGeo.vertices[i].texcoord.y))
					);
			}


			// Faces for first and last one
			if (j == points.size() - 1 || j == 0)
			{
				for (int i = 0; i < numIndices; i++)
				{
					geo.indices.push_back(
						sourceGeo.indices[i] + geo.vertices.size() - numIndices + 2
						);
				}
			}

			if (j != 0)
			{
				// Bridge
				int numVertices2 = geo.vertices.size() - 1;

				// Bovenkant
				geo.indices.push_back(numVertices2 - 0);
				geo.indices.push_back(numVertices2 - 5);
				geo.indices.push_back(numVertices2 - 4);

				geo.indices.push_back(numVertices2 - 0);
				geo.indices.push_back(numVertices2 - 5);
				geo.indices.push_back(numVertices2 - 1);

				// Links
				geo.indices.push_back(numVertices2 - 7);
				geo.indices.push_back(numVertices2 - 3);
				geo.indices.push_back(numVertices2 - 0);

				geo.indices.push_back(numVertices2 - 4);
				geo.indices.push_back(numVertices2 - 0);
				geo.indices.push_back(numVertices2 - 7);

				// Rechts
				geo.indices.push_back(numVertices2 - 5);
				geo.indices.push_back(numVertices2 - 6);
				geo.indices.push_back(numVertices2 - 1);

				geo.indices.push_back(numVertices2 - 6);
				geo.indices.push_back(numVertices2 - 1);
				geo.indices.push_back(numVertices2 - 2);
			}


		}

		return geo;
	}

	Application* Application::instance = nullptr;

	Application::Application()
	{
		instance = this;
		m_Window = new Window("Game", SCREEN_WIDTH, SCREEN_HEIGHT);
		m_Scene = Scene();

		Input::initialise();
		ResourceManager::initialise();

		this->init(&m_Scene);
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
		delete m_Window;
		m_Scene.~Scene();
	}

	void Application::tick()
	{
		m_time += 1;
		this->draw();
		Input::update();
	}

	void Application::init(Scene* scene)
	{
		Mesh torusMesh = Mesh("assets/meshes/torus.blend", ResourceManager::getMaterial(0));

		Geometry sourceGeo = Mesh::getGeometry("assets/meshes/rail.blend");

		std::vector<vec3> curvePoints;
		curvePoints.push_back(vec3(-5,  0,  0));
		curvePoints.push_back(vec3(-5,  5,  5));
		curvePoints.push_back(vec3( 5,  5,  5));
		curvePoints.push_back(vec3( 5,  0,  0));

		Geometry geo = generateRail(curvePoints, sourceGeo, vec3(.5, 0, 0), 1);
		geo.add(generateRail(curvePoints, sourceGeo, vec3(-.5, 0, 0), 1));
		geo.add(generateRail(curvePoints, sourceGeo, vec3(0, 0, 0), .25f));

		Mesh mesh = Mesh(geo, ResourceManager::getMaterial(0));

		mesh.rotateX(90);

		//scene->add(mesh);
		scene->add(torusMesh);
		Camera* camera = new Camera(45.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);
		camera->setPosition(0, 0, -10);

		m_ActiveCamera = camera;
	}

	void Application::draw()
	{
		m_Scene.draw(m_ActiveCamera);
	}
}