#version 420

in vec3 _normal;
in vec3 _position;

out vec4 color;

void main()
{
	vec3 diffuseColor = vec3(1.0f, 0.5f, 0.5f);
	vec3 lightPosition = vec3(1.0f, 1.0f, 0.0f);

    color = vec4(_normal*2, 1.0f);
} 