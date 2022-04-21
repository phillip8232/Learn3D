#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;

out vec2 TexCoord;
uniform mat4 model; //local space to world space
uniform mat4 view; //World space to viewspace
uniform mat4 projection; //Setup prespective



void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);

	TexCoord = texCoord;
}

