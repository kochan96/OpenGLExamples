#pragma once

namespace OpenGLCore
{
	enum class BufferUsage
	{
		STREAM_DRAW = 1,
		STREAM_READ = 2,
		STREAM_COPY = 3,
		STATIC_DRAW = 4,
		STATIC_READ = 5,
		STATIC_COPY = 6,
		DYNAMIC_DRAW = 7,
		DYNAMIC_READ = 8,
		DYNAMIC_COPY = 9,
	};

	class VertexBuffer
	{
	public:
		VertexBuffer(float* data, unsigned int size, BufferUsage bufferusage = BufferUsage::STATIC_DRAW);
		~VertexBuffer();

		void Bind();
		void UnBind();

	private:
		VertexBuffer();

	private:
		unsigned int m_Id;
	};
}