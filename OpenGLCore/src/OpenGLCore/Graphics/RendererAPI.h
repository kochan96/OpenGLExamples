#pragma once
#include "Enums.h"
#include <string>

namespace OpenGLCore::Graphics
{
	struct RenderAPICapabilities
	{
		std::string Vendor;
		std::string Renderer;
		std::string Version;

		int MaxSamples = 0;
		float MaxAnisotropy = 0.0f;
		int MaxTextureUnits;
	};

	class RendererAPI
	{
	public:
		static bool Init();

		static void SetClearColor(float r, float g, float b, float a);
		static void Clear(BufferBit bufferBit);

		static void SetViewPort(int x, int y, int width, int height);

		static void DrawArrays(PrimitiveType primitiveType, unsigned int start, unsigned int count);
		static void DrawIndexed(PrimitiveType primitiveType, IndexType indexType, unsigned int count, unsigned int offsetCount = 0);

		static const RenderAPICapabilities& GetCapabilities()
		{
			return m_Capabilities;
		}

	private:
		static RenderAPICapabilities m_Capabilities;
	};
}