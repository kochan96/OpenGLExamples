#include "RendererAPI.h"
#include "OpenGLCore/Core/Logger.h"
#include <glad/glad.h>

namespace OpenGLCore::Graphics
{
	RenderAPICapabilities RendererAPI::m_Capabilities;

	static void OpenGLLogMessage(
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam)
	{
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:
				LOG_CORE_ERROR("[OpenGL Debug HIGH] {0}", message);
				break;
			case GL_DEBUG_SEVERITY_MEDIUM:
				LOG_CORE_WARNING("[OpenGL Debug MEDIUM] {0}", message);
				break;
			case GL_DEBUG_SEVERITY_LOW:
				LOG_CORE_INFO("[OpenGL Debug LOW] {0}", message);
				break;
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				//LOG_CORE_TRACE("[OpenGL Debug NOTIFICATION] {0}", message);
				break;
		}
	}

	bool RendererAPI::Init()
	{
		glDebugMessageCallback(OpenGLLogMessage, nullptr);
		glEnable(GL_DEBUG_OUTPUT); //TODO maybe conditionally
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

		m_Capabilities.Vendor = (const char*)glGetString(GL_VENDOR);
		m_Capabilities.Renderer = (const char*)glGetString(GL_RENDERER);
		m_Capabilities.Version = (const char*)glGetString(GL_VERSION);

		glGetIntegerv(GL_MAX_SAMPLES, &m_Capabilities.MaxSamples);
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &m_Capabilities.MaxAnisotropy);

		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &m_Capabilities.MaxTextureUnits);

		GLenum error = glGetError();
		bool result = error == GL_NO_ERROR;

		while (error != GL_NO_ERROR)
		{
			LOG_CORE_ERROR("OpenGL Error {0}", error);
			error = glGetError();
		}

		return result;
	}

	void RendererAPI::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void RendererAPI::Clear(BufferBit bufferBit)
	{
		unsigned int openGLBufferBit = 0;
		if ((bufferBit & BufferBit::Color) != BufferBit::Unknown)
			openGLBufferBit |= GL_COLOR_BUFFER_BIT;
		if ((bufferBit & BufferBit::Depth) != BufferBit::Unknown)
			openGLBufferBit |= GL_DEPTH_BUFFER_BIT;
		if ((bufferBit & BufferBit::Stencil) != BufferBit::Unknown)
			openGLBufferBit |= GL_STENCIL_BUFFER_BIT;

		glClear(openGLBufferBit);
	}

	void RendererAPI::SetViewPort(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}

	static unsigned int PrimitiveTypeToOpenGLPrimitiveType(PrimitiveType type)
	{
		switch (type)
		{
			case PrimitiveType::Point: return GL_POINTS;
			case PrimitiveType::Lines: return GL_LINES;
			case PrimitiveType::LineLoop: return GL_LINE_LOOP;
			case PrimitiveType::LineStrip: return GL_LINE_STRIP;
			case PrimitiveType::Triangles: return GL_TRIANGLES;
			case PrimitiveType::TrianglesStrip: return GL_TRIANGLE_STRIP;
			case PrimitiveType::TrianglesFan: return GL_TRIANGLE_FAN;
		}

		LOG_CORE_ERROR("PrimitiveTypeToOpenGLPrimitiveType: Invalid enum");
		return GL_INVALID_ENUM;
	}

	static unsigned int IndexTypeToOpenGLIndexType(IndexType type)
	{
		switch (type)
		{
			case IndexType::UnsignedByte: return GL_UNSIGNED_BYTE;
			case IndexType::UnsignedInt:return GL_UNSIGNED_INT;
			case IndexType::UnsignedShort: return GL_UNSIGNED_SHORT;
		}

		LOG_CORE_ERROR("IndexTypeToOpenGLIndexType: InvalidEnum");
		return GL_INVALID_ENUM;
	}

	static unsigned long long IndexTypeToOpenGLIndexTypeSize(IndexType type)
	{
		switch (type)
		{
			case IndexType::UnsignedByte: return sizeof(char);
			case IndexType::UnsignedInt:return sizeof(unsigned int);
			case IndexType::UnsignedShort: return sizeof(unsigned short);
		}

		LOG_CORE_ERROR("IndexTypeToOpenGLIndexType: InvalidEnum");
		return GL_INVALID_ENUM;
	}

	void RendererAPI::DrawArrays(PrimitiveType primitiveType, unsigned int start, unsigned int count)
	{
		glDrawArrays(PrimitiveTypeToOpenGLPrimitiveType(primitiveType), start, count);
	}

	void RendererAPI::DrawIndexed(PrimitiveType primitiveType, IndexType indexType, unsigned int count, unsigned int offsetCount)
	{
		glDrawElements(
			PrimitiveTypeToOpenGLPrimitiveType(primitiveType),
			count,
			IndexTypeToOpenGLIndexType(indexType),
			(void*)(offsetCount * IndexTypeToOpenGLIndexTypeSize(indexType)));

	}
}
