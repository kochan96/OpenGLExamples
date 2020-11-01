#pragma once
#include <string>
#include <vector>

#include "OpenGLCore/Core/Logger.h"
#include "Enums.h"

namespace OpenGLCore::Graphics
{
	static unsigned int ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return 4;
			case ShaderDataType::Float2:   return 4 * 2;
			case ShaderDataType::Float3:   return 4 * 3;
			case ShaderDataType::Float4:   return 4 * 4;
			case ShaderDataType::Mat3:     return 4 * 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4 * 4;
			case ShaderDataType::Int:      return 4;
			case ShaderDataType::Int2:     return 4 * 2;
			case ShaderDataType::Int3:     return 4 * 3;
			case ShaderDataType::Int4:     return 4 * 4;
			case ShaderDataType::Bool:     return 1;
		}

		LOG_CORE_ERROR("ShaderDataTypeSize: Invalid shader data type {}", type);
		return 0;
	}

	static unsigned int ShaderDataTypeToComponentCount(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:   return 1;
			case ShaderDataType::Float2:  return 2;
			case ShaderDataType::Float3:  return 3;
			case ShaderDataType::Float4:  return 4;
			case ShaderDataType::Mat3:    return 3; // 3* float3
			case ShaderDataType::Mat4:    return 4; // 4* float4
			case ShaderDataType::Int:     return 1;
			case ShaderDataType::Int2:    return 2;
			case ShaderDataType::Int3:    return 3;
			case ShaderDataType::Int4:    return 4;
			case ShaderDataType::Bool:    return 1;
		}

		LOG_CORE_ERROR("ShaderDataTypeToComponentCount: Invalid shader data type {}", type);
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		unsigned int Size;
		unsigned __int64 Offset;
		bool Normalized;

		BufferElement() = default;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			:Name(name), Type(type), Normalized(normalized), Offset(0), Size(ShaderDataTypeSize(type))
		{
		}

		unsigned int GetComponentCount() const { return ShaderDataTypeToComponentCount(Type); }
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			:m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		unsigned int GetStride() const { return m_Stride; }

		const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateOffsetsAndStride()
		{
			unsigned int offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

	private:
		std::vector<BufferElement> m_Elements;
		unsigned int m_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		VertexBuffer(float* data, unsigned long long size, BufferUsage bufferusage = BufferUsage::StaticDraw);
		~VertexBuffer();

		void Bind() const;
		void UnBind() const;

		const BufferLayout& GetLayout() const { return m_Layout; }
		void SetLayout(const BufferLayout& layout) { m_Layout = layout; }

	private:
		VertexBuffer();

	private:
		unsigned int m_Id;
		BufferLayout m_Layout;
	};

	class IndexBuffer
	{
	public:
		IndexBuffer(unsigned char* indices, unsigned int count, BufferUsage bufferUsage = BufferUsage::StaticDraw);
		IndexBuffer(unsigned short* indices, unsigned int count, BufferUsage bufferUsage = BufferUsage::StaticDraw);
		IndexBuffer(unsigned int* indices, unsigned int count, BufferUsage bufferUsage = BufferUsage::StaticDraw);

		IndexBuffer(unsigned int count, IndexType indexType = IndexType::UnsignedInt, BufferUsage bufferUsage = BufferUsage::DynamicDraw);

		~IndexBuffer();

		void Bind() const;
		void UnBind() const;

		unsigned int GetCount() const { return m_Count; }
		IndexType GetIndexType() const { return m_IndexType; }

	private:
		unsigned int m_Id;
		unsigned int m_Count;
		IndexType m_IndexType;
	};
}