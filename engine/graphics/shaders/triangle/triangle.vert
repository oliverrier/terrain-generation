#version 430 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec2 texCoord;

uniform mat4 MVP;

out vec2 fragTexCoord;

void main()
{
	gl_Position = MVP * vPosition;
	fragTexCoord = texCoord;
}