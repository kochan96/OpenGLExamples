#version 440 core
out vec4 color;

in vec2 v_TextureCoord;
uniform sampler2D u_TextureSampler;
uniform sampler2D u_TextureSampler2;

void main()
{
	color = mix(texture(u_TextureSampler, v_TextureCoord),
				texture(u_TextureSampler2, v_TextureCoord),
				0.2);
};