#pragma once

#include <iostream>
#include <string>
#include <glm\glm.hpp>

#define SCREEN_WIDTH  1366
#define SCREEN_HEIGHT 768

// 1 = Debug mode, 2 = Release mode
#define DEBUG 1

// Debug functions
#if DEBUG == 1
#define LOG(text) { std::cout << text << std::endl; }
#else
#define LOG
#endif


class FileUtils {
public:
	static std::string read_file(const char* filepath)
	{
		FILE* file = fopen(filepath, "rt"); // read only and text file
		fseek(file, 0, SEEK_END);
		unsigned long length = ftell(file);
		char* data = new char[length + 1];
		memset(data, 0, length + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);

		std::string result(data);
		delete[] data;
		return result;
	}
};

struct Vertex {
	Vertex() {}

	Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texcoord)
		: position(position), normal(normal), texcoord(texcoord)
	{

	}

	Vertex(glm::vec3 position, glm::vec3 normal) 
		: position(position), normal(normal)
	{

	}
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texcoord;
};


