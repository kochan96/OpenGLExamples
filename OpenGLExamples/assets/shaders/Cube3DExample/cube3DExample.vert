#version 440 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TextureCoord;
	
out vec2 v_TextureCoord;

uniform mat4 u_ModelViewProjection;

void main()
{
	v_TextureCoord = a_TextureCoord;
	gl_Position = u_ModelViewProjection * vec4(a_Position, 1.0);
};