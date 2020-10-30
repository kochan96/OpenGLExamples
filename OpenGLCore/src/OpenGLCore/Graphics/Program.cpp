#include "Program.h"
#include <glad/glad.h>
#include <vector>
#include <fstream>

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

		//TODO LOG;
		return GL_INVALID_ENUM;
	}

	Shader::Shader(const ShaderSource& shaderSource)
	{
		m_ShaderType = shaderSource.Type;
		m_Id = glCreateShader(ShaderTypeToOpenGLShaderType(m_ShaderType));

		auto source = shaderSource.SourceCode.c_str();
		glShaderSource(m_Id, 1, &source, NULL);
	}

	Shader::Shader(const std::string& filePath, ShaderType shaderType)
	{
		m_ShaderType = shaderType;
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
				//TODO log
			}
		}
		else
		{
			//TODO log
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
			//TODO LOG;
			
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
			//TODO log;
			auto infoLog = GetInfoLog();

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
}
