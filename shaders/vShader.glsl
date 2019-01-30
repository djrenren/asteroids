#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 v_uv;
layout (location = 2) in vec3 v_norm;
layout (location = 3) uniform mat4 viewMatrix;
layout (location = 4) uniform mat4 camMatrix;
layout (location = 5) uniform vec3 lightLoc;


out vec2 uv;
out vec3 norm;
out vec3 loc;
out vec3 f_cameraLoc;
out vec3 f_lightLoc;


void main()
{
	gl_Position = camMatrix * viewMatrix * vec4(position, 1);
	uv = v_uv;
	vec4 pos4 = viewMatrix * vec4(position, 1.0);
	loc = pos4.xyz / pos4.w;
    norm = (inverse(transpose(viewMatrix)) * vec4(v_norm, 0)).xyz;
	f_lightLoc = lightLoc;
	f_cameraLoc = lightLoc;
}