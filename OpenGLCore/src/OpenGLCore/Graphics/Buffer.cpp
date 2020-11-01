#include "Buffer.h"
#include <glad/glad.h>

#include "OpenGLCore/Core/Logger.h"

namespace OpenGLCore::Graphics
{
	static GLenum BufferUsageToBufferHint(BufferUsage bufferUsage)
	{
		switch (bufferUsage)
		{
			case BufferUsage::DynamicCopy:
				return GL_DYNAMIC_COPY;
			case BufferUsage::DynamicDraw:
				return GL_DYNAMIC_DRAW;
			case BufferUsage::DynamicRead:
				return GL_DYNAMIC_READ;
			case BufferUsage::StaticCopy:
				return GL_STATIC_COPY;
			case BufferUsage::StaticDraw:
				return GL_STATIC_DRAW;
			case BufferUsage::StaticRead:
				return GL_STATIC_READ;
			case BufferUsage::StreamCopy:
				return GL_STREAM_COPY;
			case BufferUsage::StreamDraw:
				return GL_STREAM_DRAW;
			case BufferUsage::StreamRead:
				return GL_STREAM_READ;
		}

		LOG_CORE_ERROR("Invalid Buffer usage {}", bufferUsage);
		return GL_INVALID_ENUM;
	}

	/////////////////////////////////////////////////////////////////////////////
	// VertexBuffer /////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

	VertexBuffer::VertexBuffer(float* data, unsigned long long size, BufferUsage bufferUsage)
	{
		glGenBuffers(1, &m_Id);
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ARRAY_BUFFER, size, data, BufferUsageToBufferHint(bufferUsage));
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_Id);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
	}

	void VertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/////////////////////////////////////////////////////////////////////////////
	// IndexBuffer //////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

	IndexBuffer::IndexBuffer(unsigned char* indices, unsigned int count, BufferUsage bufferUsage)
		: m_IndexType(IndexType::UnsignedByte), m_Count(count)
	{
		glGenBuffers(1, &m_Id);
		// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
		// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state.
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(unsigned char), indices, BufferUsageToBufferHint(bufferUsage));
	}

	IndexBuffer::IndexBuffer(unsigned short* indices, unsigned int count, BufferUsage bufferUsage)
		: m_IndexType(IndexType::UnsignedByte), m_Count(count)
	{
		glGenBuffers(1, &m_Id);
		// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
		// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state.
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(unsigned short), indices, BufferUsageToBufferHint(bufferUsage));
	}

	IndexBuffer::IndexBuffer(unsigned int* indices, unsigned int count, BufferUsage bufferUsage)
		: m_IndexType(IndexType::UnsignedByte), m_Count(count)
	{
		glGenBuffers(1, &m_Id);
		// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
		// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state.
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(unsigned int), indices, BufferUsageToBufferHint(bufferUsage));
	}

	IndexBuffer::IndexBuffer(unsigned int count, IndexType indexType, BufferUsage bufferUsage)
		: m_IndexType(indexType), m_Count(count)
	{
		glGenBuffers(1, &m_Id);
		// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
		// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state.
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(unsigned int), nullptr, BufferUsageToBufferHint(bufferUsage));
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_Id);
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
	}

	void IndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
