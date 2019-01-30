#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 v_uv;
layout (location = 2) in vec3 v_norm;
layout (location = 3) uniform mat4 viewMatrix;
layout (location = 4) uniform mat4 camMatrix;


out vec3 texCoord;

void main()
{
	texCoord = position;
	gl_Position = camMatrix * viewMatrix * vec4(position, 1);
}