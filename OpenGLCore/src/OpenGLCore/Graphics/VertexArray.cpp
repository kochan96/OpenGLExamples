#include "VertexArray.h"
#include "VertexArray.h"
#include "glad/glad.h"

#include "OpenGLCore/Core/Logger.h"

namespace OpenGLCore::Graphics
{
	static GLenum ShaderDataTypeToOpenGLType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return GL_FLOAT;
			case ShaderDataType::Float2:   return GL_FLOAT;
			case ShaderDataType::Float3:   return GL_FLOAT;
			case ShaderDataType::Float4:   return GL_FLOAT;
			case ShaderDataType::Mat3:     return GL_FLOAT;
			case ShaderDataType::Mat4:     return GL_FLOAT;
			case ShaderDataType::Int:      return GL_INT;
			case ShaderDataType::Int2:     return GL_INT;
			case ShaderDataType::Int3:     return GL_INT;
			case ShaderDataType::Int4:     return GL_INT;
			case ShaderDataType::Bool:     return GL_BOOL;
		}

		LOG_CORE_ERROR("VertexArray: Invalid shader data type");
		return 0;
	}

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_Id);
		glBindVertexArray(m_Id);
	}

	VertexArray::~VertexArray()
	{
		for (int i = 0; i < m_VertexBufferIndex; i++)
		{
			glDisableVertexAttribArray(i);
		}
		glDeleteVertexArrays(1, &m_Id);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_Id);
	}

	void VertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_Id);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			switch (element.Type)
			{
				case ShaderDataType::Float:
				case ShaderDataType::Float2:
				case ShaderDataType::Float3:
				case ShaderDataType::Float4:
				case ShaderDataType::Int:
				case ShaderDataType::Int2:
				case ShaderDataType::Int3:
				case ShaderDataType::Int4:
				case ShaderDataType::Bool:
				{
					glEnableVertexAttribArray(m_VertexBufferIndex);
					glVertexAttribPointer(
						m_VertexBufferIndex,
						element.GetComponentCount(),
						ShaderDataTypeToOpenGLType(element.Type),
						element.Normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)element.Offset);
					m_VertexBufferIndex++;
					break;
				}
				case ShaderDataType::Mat3:
				case ShaderDataType::Mat4:
				{
					unsigned int count = element.GetComponentCount();
					for (unsigned int i = 0; i < count; i++)
					{
						glEnableVertexAttribArray(m_VertexBufferIndex);
						glVertexAttribPointer(
							m_VertexBufferIndex,
							count,
							ShaderDataTypeToOpenGLType(element.Type),
							element.Normalized ? GL_TRUE : GL_FALSE,
							layout.GetStride(),
							(const void*)(sizeof(float) * count * i));
						glVertexAttribDivisor(m_VertexBufferIndex, 1);
						m_VertexBufferIndex++;
					}
					break;
				}
				default:
					LOG_CORE_ERROR("Vertex Array AddVertexBuffer: Invalid Shader Data Type");
					break;
			}
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		Bind();
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
}
