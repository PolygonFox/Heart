#version 420
  
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 mvp;
out vec3 _normal;
out vec3 _position;

void main()
{
	_normal = normal;
	_position = position;
    gl_Position = vec4(position, 1.0) * mvp;
}