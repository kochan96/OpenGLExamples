#version 440 core
layout (location = 0) in vec2 a_Position;
	
void main()
{
	gl_Position = vec4(a_Position.x, a_Position.y, 0.0f, 1.0);
};