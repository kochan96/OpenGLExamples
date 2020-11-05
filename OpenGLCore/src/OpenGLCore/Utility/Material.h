#pragma once
namespace OpenGLCore::Utility
{
	struct Material
	{
		unsigned int DiffuseTextureSlot;
		unsigned int SpecularTextureSlot;
		float Shininess;
	};
}