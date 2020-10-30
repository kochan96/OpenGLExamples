#include "Buffer.h"
#include <glad/glad.h>

namespace OpenGLCore
{
	static GLenum BufferUsageToBufferHint(BufferUsage bufferUsage)
	{
		switch (bufferUsage)
		{
			case BufferUsage::DYNAMIC_COPY:
				return GL_DYNAMIC_COPY;
			case BufferUsage::DYNAMIC_DRAW:
				return GL_DYNAMIC_DRAW;
			case BufferUsage::DYNAMIC_READ:
				return GL_DYNAMIC_READ;
			case BufferUsage::STATIC_COPY:
				return GL_STATIC_COPY;
			case BufferUsage::STATIC_DRAW:
				return GL_STATIC_DRAW;
			case BufferUsage::STATIC_READ:
				return GL_STATIC_READ;
			case BufferUsage::STREAM_COPY:
				return GL_STREAM_COPY;
			case BufferUsage::STREAM_DRAW:
				return GL_STREAM_DRAW;
			case BufferUsage::STREAM_READ:
				return GL_STREAM_READ;
			default:
				return GL_INVALID_ENUM;
		}
	}

	VertexBuffer::VertexBuffer(float* data, unsigned int size, BufferUsage bufferUsage)
	{
		glGenBuffers(1, &m_Id);
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ARRAY_BUFFER, size, data,BufferUsageToBufferHint(bufferUsage));
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_Id);
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
	}

	void VertexBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
