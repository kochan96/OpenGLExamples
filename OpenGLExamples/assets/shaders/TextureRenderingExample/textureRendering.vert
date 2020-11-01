#version 440 core
layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_TextureCoord;
	
out vec2 v_TextureCoord;

void main()
{
	v_TextureCoord = a_TextureCoord;
	gl_Position = vec4(a_Position.x, a_Position.y, 0.0f, 1.0);
};