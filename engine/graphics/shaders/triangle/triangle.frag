#version 430 core

out vec4 fragColor;

in vec2 fragTexCoord;

uniform vec4 mySuperColor;

uniform sampler2D texture1;

void main()
{
	fragColor = texture(texture1, fragTexCoord);
}