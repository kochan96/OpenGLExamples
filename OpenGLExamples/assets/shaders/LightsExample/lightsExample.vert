#version 440 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TextureCoord;
	
out vec2 v_TextureCoord;
out vec3 v_Normal;
out vec3 v_FragPos;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

void main()
{
	v_FragPos = vec3(u_ModelMatrix * vec4(a_Position,1.0f));
	v_Normal = mat3(transpose(inverse(u_ModelMatrix))) * a_Normal;
	v_TextureCoord = a_TextureCoord;

	gl_Position = u_ProjectionMatrix*u_ViewMatrix * vec4(v_FragPos, 1.0);
};