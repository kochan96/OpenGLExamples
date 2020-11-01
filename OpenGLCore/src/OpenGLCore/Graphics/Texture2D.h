#pragma once
#include <string>
#include "Enums.h"

namespace OpenGLCore::Graphics
{
	class Texture2D
	{
	public:
		Texture2D(const std::string& filePath);
		Texture2D(
			unsigned int width,
			unsigned int height,
			DataType dataType = DataType::Byte,
			DataFormat internalFormat = DataFormat::RGBA8,
			DataFormat dataFormat = DataFormat::RGBA);
		~Texture2D();

		unsigned int GetWidth() const { return m_Width; }
		unsigned int GetHeight() const { return m_Height; }

		void SetData(void* data, unsigned int size);

		void Bind(unsigned int slot = 0) const;

		void SetWrappingS(WrapMode mode) const;
		void SetWrappingT(WrapMode mode) const;
		void SetMinFilter(FilteringMode filteringMode) const;
		void SetMagFilter(FilteringMode filteringMode) const;

		void GenerateMipMaps() const;

		bool operator==(const Texture2D& other) const
		{
			return m_Id == other.m_Id;
		}

	private:
		unsigned int m_Id;
		unsigned int m_Width, m_Height;

		DataType m_DataType;
		DataFormat m_InternalFormat;
		DataFormat m_DataFormat;
	};
}