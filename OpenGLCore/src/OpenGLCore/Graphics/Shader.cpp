#include "Shader.h"

#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <vector>
#include <fstream>

#include "OpenGLCore/Core/Logger.h"

namespace OpenGLCore::Graphics
{
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

	Shader::Shader(
		const std::string& vertexShaderFile,
		const std::string& fragmentShaderFile)
	{
		auto vertexSource = ReadFile(vertexShaderFile);
		auto fragmentSource = ReadFile(fragmentShaderFile);

		std::unordered_map<unsigned int, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSource;
		sources[GL_FRAGMENT_SHADER] = fragmentSource;
		Compile(sources);
	}

	Shader::Shader(
		const std::string& vertexShaderFile,
		const std::string& fragmentShaderFile,
		const std::string& geometryShaderFile)
	{
		auto vertexSource = ReadFile(vertexShaderFile);
		auto fragmentSource = ReadFile(fragmentShaderFile);
		auto geometrySource = ReadFile(geometryShaderFile);

		std::unordered_map<unsigned int, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSource;
		sources[GL_FRAGMENT_SHADER] = fragmentSource;
		sources[GL_GEOMETRY_SHADER] = geometrySource;
		Compile(sources);
	}

	void Shader::Compile(const std::unordered_map<unsigned int, std::string>& shaderSources)
	{
		m_Id = glCreateProgram();

		auto size = shaderSources.size();
		std::vector<GLenum> glShaderIDs(size);
		int glShaderIdIndex = 0;

		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);
			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				LOG_CORE_ERROR("{0}", infoLog.data());
				LOG_CORE_ERROR("Shader compilation failure!");
				break;
			}

			glAttachShader(m_Id, shader);
			glShaderIDs[glShaderIdIndex++] = shader;
		}

		glLinkProgram(m_Id);

		GLint isLinked = 0;
		glGetProgramiv(m_Id, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_Id, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_Id, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_Id);

			for (auto id : glShaderIDs)
				glDeleteShader(id);

			LOG_CORE_ERROR("{0}", infoLog.data());
			LOG_CORE_ERROR("Shader link failure!");
			return;
		}

		for (auto id : glShaderIDs)
		{
			glDetachShader(m_Id, id);
			glDeleteShader(id);
		}
	}

	Shader::~Shader()
	{
		glUseProgram(0);
		glDeleteProgram(m_Id);
	}

	void Shader::Use() const
	{
		glUseProgram(m_Id);
	}

	void Shader::SetBool(const std::string& name, bool value)
	{
		auto location = GetUniformLocation(name);
		glUniform1i(location, value ? 1 : 0);
	}

	void Shader::SetInt(const std::string& name, int value)
	{
		auto location = GetUniformLocation(name);
		glUniform1i(location, value);
	}

	void Shader::SetInt2(const std::string& name, const glm::ivec2& value)
	{
		auto location = GetUniformLocation(name);
		glUniform2i(location, value.x, value.y);
	}

	void Shader::SetInt3(const std::string& name, const glm::ivec3& value)
	{
		auto location = GetUniformLocation(name);
		glUniform3i(location, value.x, value.y, value.z);
	}

	void Shader::SetInt4(const std::string& name, const glm::ivec4& value)
	{
		auto location = GetUniformLocation(name);
		glUniform4i(location, value.x, value.y, value.z, value.w);
	}

	void Shader::SetFloat(const std::string& name, int value)
	{
		auto location = GetUniformLocation(name);
		glUniform1f(location, value);
	}

	void Shader::SetFloat2(const std::string& name, const glm::vec2& value)
	{
		auto location = GetUniformLocation(name);
		glUniform2f(location, value.x, value.y);
	}

	void Shader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		auto location = GetUniformLocation(name);
		glUniform3f(location, value.x, value.y, value.z);
	}

	void Shader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		auto location = GetUniformLocation(name);
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void Shader::SetMat3(const std::string& name, const glm::mat3& value)
	{
		auto location = GetUniformLocation(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		auto location = GetUniformLocation(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	unsigned int Shader::GetUniformLocation(const std::string& name)
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
