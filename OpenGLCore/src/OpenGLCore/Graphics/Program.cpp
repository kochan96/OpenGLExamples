#include "Program.h"
#include <glad/glad.h>
#include <vector>
#include <fstream>

#include "OpenGLCore/Core/Logger.h"

namespace OpenGLCore::Graphics
{
	static GLenum ShaderTypeToOpenGLShaderType(ShaderType type)
	{
		switch (type)
		{
			case OpenGLCore::Graphics::ShaderType::Vertex:
				return GL_VERTEX_SHADER;
			case OpenGLCore::Graphics::ShaderType::Fragment:
				return GL_FRAGMENT_SHADER;
		}

		LOG_CORE_ERROR("Invalid or not supported shader type");
		return GL_INVALID_ENUM;
	}

	Shader::Shader(const ShaderSource& shaderSource, const std::string& name)
	{
		m_ShaderType = shaderSource.Type;
		m_Name = name;
		m_Id = glCreateShader(ShaderTypeToOpenGLShaderType(m_ShaderType));

		auto source = shaderSource.SourceCode.c_str();
		glShaderSource(m_Id, 1, &source, NULL);
	}

	Shader::Shader(const std::string& filePath, ShaderType shaderType, const std::string& name)
	{
		m_ShaderType = shaderType;
		m_Name = name;
		m_Id = glCreateShader(ShaderTypeToOpenGLShaderType(m_ShaderType));

		auto fileContent = ReadFile(filePath);
		auto source = fileContent.c_str();
		glShaderSource(m_Id, 1, &source, NULL);
	}

	std::string Shader::ReadFile(const std::string& filePath)
	{
		std::string result;
		std::ifstream in(filePath, std::ios::in, std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
				in.close();
			}
			else
			{
				LOG_CORE_ERROR("Could not read from file '{0}'", filePath);
			}
		}
		else
		{
			LOG_CORE_ERROR("Could not open file '{0}'", filePath);
		}

		return result;
	}

	Shader::~Shader()
	{
		glDeleteShader(m_Id);
	}

	bool Shader::Compile()
	{
		glCompileShader(m_Id);
		GLint isCompiled = 0;
		glGetShaderiv(m_Id, GL_COMPILE_STATUS, &isCompiled);
		m_IsCompiled = (bool)isCompiled;
		if (!m_IsCompiled)
		{
			auto infoLog = GetInfoLog();
			LOG_CORE_ERROR(infoLog.c_str());
			LOG_CORE_ERROR("Shader compilation failure {}", m_Name);

			glDeleteShader(m_Id);
			m_Id = 0;
		}

		return m_IsCompiled;
	}

	std::string Shader::GetInfoLog()
	{
		GLint maxLength = 0;
		glGetShaderiv(m_Id, GL_INFO_LOG_LENGTH, &maxLength);
		if (maxLength > 0)
		{
			std::string infoLog(maxLength, 0);
			glGetShaderInfoLog(m_Id, maxLength, &maxLength, &infoLog[0]);
			return infoLog;
		}

		return "";
	}

	Program::Program(const std::string& name)
		:m_Name(name)
	{
		m_Id = glCreateProgram();
	}

	Program::~Program()
	{
		glDeleteProgram(m_Id);
	}

	bool Program::Create(std::vector<Shader> shaders)
	{
		for (auto& shader : shaders)
		{
			if (!shader.GetIsCompiled())
			{
				if (!shader.Compile())
				{
					break;
				}
			}

			glAttachShader(m_Id, shader.m_Id);
		}

		glLinkProgram(m_Id);

		GLint isLinked = 0;
		glGetProgramiv(m_Id, GL_LINK_STATUS, &isLinked);
		m_IsLinked = (bool)isLinked;

		if (!m_IsLinked)
		{
			auto infoLog = GetInfoLog();
			LOG_CORE_ERROR(infoLog.c_str());
			LOG_CORE_ERROR("Progrma link failure {}", m_Name);

			glDeleteProgram(m_Id);

			return false;
		}

		for (auto& shader : shaders)
		{
			glDetachShader(m_Id, shader.m_Id);
		}

		return true;
	}

	std::string Program::GetInfoLog()
	{
		GLint maxLength = 0;
		glGetProgramiv(m_Id, GL_INFO_LOG_LENGTH, &maxLength);

		if (maxLength > 0)
		{
			std::string infoLog(maxLength, 0);
			glGetProgramInfoLog(m_Id, maxLength, &maxLength, &infoLog[0]);
			return infoLog;
		}

		return "";
	}

	void Program::Use() const
	{
		glUseProgram(m_Id);
	}

	void Program::SetBool(const std::string& name, bool value)
	{
		auto location = GetUniformLocation(name);
		glUniform1i(location, value ? 1 : 0);
	}

	void Program::SetInt(const std::string& name, int value)
	{
		auto location = GetUniformLocation(name);
		glUniform1i(location, value);
	}

	void Program::SetFloat(const std::string& name, int value)
	{
		auto location = GetUniformLocation(name);
		glUniform1f(location, value);
	}

	unsigned int Program::GetUniformLocation(const std::string& name)
	{
		auto it = m_UniformCache.find(name);
		if (it == m_UniformCache.end())
		{
			auto location = glGetUniformLocation(m_Id, name.c_str());
			if (location == -1)
				LOG_CORE_ERROR("Could not find uniform {} in {}", name, m_Name);

			m_UniformCache[name] = location;
			return location;
		}

		return it->second;
	}
}
