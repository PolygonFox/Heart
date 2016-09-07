#include "shader.h"


#include <string>

namespace Heart {
	namespace Graphics {
		Shader::Shader(const char* vertexSourcePath, const char* fragmentSourcePath)
		{
			// Create shader
			GLchar infoLog[512];
			GLint success;

			std::string rawVertexSource = FileUtils::read_file(vertexSourcePath);
			const char* vertexSource = rawVertexSource.c_str();

			std::string rawFragmentSource = FileUtils::read_file(fragmentSourcePath);
			const char* fragmentSource = rawFragmentSource.c_str();

			GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShader, 1, &vertexSource, NULL);
			glCompileShader(vertexShader);

			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
				LOG(printf("Vertex Shader (%s):\n%s", vertexSourcePath, infoLog));
			}

			GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
			glCompileShader(fragmentShader);

			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
				LOG(printf("Fragment Shader (%s):\n%s", fragmentSourcePath, infoLog));
			}

			GLuint program = glCreateProgram();
			glAttachShader(program, vertexShader);
			glAttachShader(program, fragmentShader);
			glLinkProgram(program);
			glGetProgramiv(program, GL_LINK_STATUS, &success);

			if (!success)
			{
				glGetProgramInfoLog(program, 512, NULL, infoLog);
				LOG(infoLog);
			}

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			m_Program = program;
		}

		Shader::~Shader()
		{

		}

		void Shader::use()
		{
			glUseProgram(m_Program);
		}

		GLuint Shader::getUniformLocation(char* name)
		{
			return glGetUniformLocation(m_Program, name);
		}
	}
}
