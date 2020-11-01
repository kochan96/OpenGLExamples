#pragma once
#include "OpenGLCore/Core/Logger.h"

namespace OpenGLCore::Graphics
{
	enum class ShaderDataType
	{
		Float = 1,
		Float2 = 2,
		Float3 = 3,
		Float4 = 4,
		Mat3 = 5,
		Mat4 = 6,
		Int = 7,
		Int2 = 8,
		Int3 = 9,
		Int4 = 10,
		Bool = 11
	};

	enum class BufferUsage
	{
		StreamDraw = 1,
		StreamRead = 2,
		StreamCopy = 3,
		StaticDraw = 4,
		StaticRead = 5,
		StaticCopy = 6,
		DynamicDraw = 7,
		DynamicRead = 8,
		DynamicCopy = 9,
	};

	enum class PrimitiveType
	{
		Point = 1,
		Lines = 2,
		LineLoop = 3,
		LineStrip = 4,
		Triangles = 5,
		TrianglesStrip = 6,
		TrianglesFan = 7
	};

	enum class IndexType
	{
		UnsignedByte = 1,
		UnsignedShort = 2,
		UnsignedInt = 3,
	};

	enum class BufferBit
	{
		Unknown = 0,
		Color = 1 << 0,
		Depth = 1 << 1,
		Stencil = 1 << 2,
	};

	enum class WrapMode
	{
		Repeat = 1,
		MirroredRepeat = 2,
		ClampToEdge = 3,
		ClampToBorder = 4,
	};

	enum class FilteringMode
	{
		Nearest = 1,
		Linear = 2,
		NearestMipmapNearest = 3,
		NearestMipmapLinear = 4,
		LinearMipmapNearest = 5,
		LinearMipmapLinear = 6,
	};

	enum class DataFormat
	{
		RGBA8 = 1,
		RGBA = 2,
		RGB8 = 3,
		RGB = 4
	};

	enum class DataType
	{
		Byte = 1,
		UnsignedByte = 2,
		Short = 3,
		UnsignedShort = 4,
		Int = 5,
		UnsignedInt = 6,
		Float = 7,
		Double = 8,
	};

	inline BufferBit& operator |= (BufferBit& lhs, BufferBit rhs)
	{
		return (BufferBit&)((uint8_t&)(lhs) |= static_cast<uint8_t>(rhs));
	}

	inline BufferBit operator|(BufferBit lhs, BufferBit rhs)
	{
		return static_cast<BufferBit>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
	}

	inline BufferBit& operator &= (BufferBit& lhs, BufferBit rhs)
	{
		return (BufferBit&)((uint8_t&)(lhs) &= static_cast<uint8_t>(rhs));
	}

	inline BufferBit operator&(BufferBit lhs, BufferBit rhs)
	{
		return static_cast<BufferBit>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs));
	}
}
