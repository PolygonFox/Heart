#version 420

in vec2 _texcoord;

out vec4 color;

uniform sampler2D diffuse_tex;

void main()
{
	vec4 diffuseColor = texture(diffuse_tex, _texcoord);

    color = diffuseColor;
} 