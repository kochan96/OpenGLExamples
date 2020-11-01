#version 440 core
out vec4 color;

in vec2 v_TextureCoord;
uniform sampler2D u_TextureSampler;

void main()
{
	vec3 textureColor = texture(u_TextureSampler, v_TextureCoord).rgb;
	color = vec4(textureColor, 1.0f);
};