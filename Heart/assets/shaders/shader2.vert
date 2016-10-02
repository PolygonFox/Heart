#version 420
  
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoord;

uniform mat4 mvp;
uniform float time;

out vec3 _normal;
out vec3 _position;
out vec2 _texcoord;


void main()
{
	_texcoord = texcoord;

    gl_Position = mvp * vec4(position, 1.0f);
}