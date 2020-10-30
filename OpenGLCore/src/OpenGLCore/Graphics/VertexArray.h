#pragma once
#include <memory>
#include "Buffer.h"

namespace OpenGLCore
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		void UnBind() const;

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);

		const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const
		{
			return m_VertexBuffers;
		}

	private:
		unsigned int m_Id;
		unsigned int m_VertexBufferIndex = 0;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
	};
}