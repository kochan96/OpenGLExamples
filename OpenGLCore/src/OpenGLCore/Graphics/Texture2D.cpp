#include "Texture2D.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace OpenGLCore::Graphics
{
	static unsigned int DataFormatToOpenGLDataFormat(DataFormat internalFormat)
	{
		switch (internalFormat)
		{
			case DataFormat::RGB:	return GL_RGB;
			case DataFormat::RGB8:	return GL_RGB8;
			case DataFormat::RGBA:	return GL_RGBA;
			case DataFormat::RGBA8:	return GL_RGBA8;
		}

		LOG_CORE_ERROR("DataFormatToOpenGLDataFormat: Not supported enum {}", internalFormat);
		return 0;
	}

	static unsigned int DataTypeToOpenGLDataType(DataType dataType)
	{
		switch (dataType)
		{
			case DataType::Byte:return GL_BYTE;
			case DataType::Double:return GL_DOUBLE;
			case DataType::Float: return GL_FLOAT;
			case DataType::Int: return GL_INT;
			case DataType::Short: return GL_SHORT;
			case DataType::UnsignedByte: return GL_UNSIGNED_BYTE;
			case DataType::UnsignedInt: return GL_UNSIGNED_INT;
			case DataType::UnsignedShort: return GL_UNSIGNED_SHORT;
		}

		LOG_CORE_ERROR("DataTypeToOpenGLDataType: Not supported enum {}", dataType);
		return 0;
	}

	static unsigned int WrapModeToOpenGLWrapMode(WrapMode mode)
	{
		switch (mode)
		{
			case WrapMode::Repeat: return GL_REPEAT;
			case WrapMode::MirroredRepeat: return GL_MIRRORED_REPEAT;
			case WrapMode::ClampToEdge: return GL_CLAMP_TO_EDGE;
			case WrapMode::ClampToBorder:	return GL_CLAMP_TO_BORDER;
		}

		LOG_CORE_ERROR("WrapModeToOpenGLWrapMode: Invalid enum {}", mode);
		return 0;
	}

	static unsigned int FilteringModeToOpenGLFilteringMode(FilteringMode mode)
	{
		switch (mode)
		{
			case FilteringMode::Nearest: return GL_NEAREST;
			case FilteringMode::Linear: return GL_LINEAR;
			case FilteringMode::NearestMipmapNearest: return GL_NEAREST_MIPMAP_NEAREST;
			case FilteringMode::NearestMipmapLinear: return GL_NEAREST_MIPMAP_LINEAR;
			case FilteringMode::LinearMipmapNearest: return GL_LINEAR_MIPMAP_NEAREST;
			case FilteringMode::LinearMipmapLinear: return GL_LINEAR_MIPMAP_LINEAR;
		}

		LOG_CORE_ERROR("FilteringModeToOpenGLFilteringMode: Invalid enum {}", mode);
		return 0;
	}

	Texture2D::Texture2D(const std::string& filePath)
	{
		stbi_set_flip_vertically_on_load(true);

		glGenTextures(1, &m_Id);
		glBindTexture(GL_TEXTURE_2D, m_Id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

		m_DataFormat = DataFormat::RGB8;
		m_InternalFormat = DataFormat::RGB;
		m_DataType = DataType::UnsignedByte;

		m_Width = width;
		m_Height = height;

		if (data)
		{
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				DataFormatToOpenGLDataFormat(m_DataFormat),
				width,
				height,
				0,
				DataFormatToOpenGLDataFormat(m_InternalFormat),
				DataTypeToOpenGLDataType(m_DataType),
				data);
		}
		else
		{
			LOG_CORE_ERROR("Failed to load texture {}", filePath);
		}

		stbi_image_free(data);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D::Texture2D(
		unsigned int width,
		unsigned int height,
		DataType dataType,
		DataFormat internalFormat,
		DataFormat dataFormat)
		:m_Width(width), m_Height(height),
		m_DataType(dataType), m_DataFormat(dataFormat), m_InternalFormat(internalFormat)
	{
		glGenTextures(1, &m_Id);
		glBindTexture(GL_TEXTURE_2D, m_Id);

		glTexStorage2D(
			GL_TEXTURE_2D,
			1,
			DataFormatToOpenGLDataFormat(m_InternalFormat),
			m_Width,
			m_Height);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_Id);
	}

	void Texture2D::SetData(void* data, unsigned int size)
	{
		glBindTexture(GL_TEXTURE_2D, m_Id);
		glTexSubImage2D(
			GL_TEXTURE_2D,
			0,
			0,
			0,
			m_Width,
			m_Height,
			DataFormatToOpenGLDataFormat(m_DataFormat),
			DataTypeToOpenGLDataType(m_DataType),
			data);
	}

	void Texture2D::Bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_Id);
	}

	void Texture2D::SetWrappingS(WrapMode mode) const
	{
		glBindTexture(GL_TEXTURE_2D, m_Id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapModeToOpenGLWrapMode(mode));
	}

	void Texture2D::SetWrappingT(WrapMode mode) const
	{
		glBindTexture(GL_TEXTURE_2D, m_Id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapModeToOpenGLWrapMode(mode));
	}

	void Texture2D::SetMinFilter(FilteringMode filteringMode) const
	{
		glBindTexture(GL_TEXTURE_2D, m_Id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilteringModeToOpenGLFilteringMode(filteringMode));

	}

	void Texture2D::SetMagFilter(FilteringMode filteringMode) const
	{
		glBindTexture(GL_TEXTURE_2D, m_Id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilteringModeToOpenGLFilteringMode(filteringMode));
	}

	void Texture2D::GenerateMipMaps() const
	{
		glBindTexture(GL_TEXTURE_2D, m_Id);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}