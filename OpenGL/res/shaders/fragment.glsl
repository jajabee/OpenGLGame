#version 330 core

in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 fragmentColor;

void main()
{
	fragmentColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2);
}