#pragma once
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>

namespace OpenGLCore::Graphics
{
	class Shader
	{
	public:
		Shader(
			const std::string& vertexShaderFile,
			const std::string& fragmentShaderFile);

		Shader(
			const std::string& vertexShaderFile,
			const std::string& fragmentShaderFile,
			const std::string& geometryShaderFile);

		~Shader();

		void Use() const;

		void SetBool(const std::string& name, bool value);

		void SetInt(const std::string& name, int value);
		void SetInt2(const std::string& name, const glm::ivec2& value);
		void SetInt3(const std::string& name, const glm::ivec3& value);
		void SetInt4(const std::string& name, const glm::ivec4& value);

		void SetFloat(const std::string& name, float value);
		void SetFloat2(const std::string& name, const glm::vec2& value);
		void SetFloat3(const std::string& name, const glm::vec3& value);
		void SetFloat4(const std::string& name, const glm::vec4& value);

		void SetMat3(const std::string& name, const glm::mat3& value);
		void SetMat4(const std::string& name, const glm::mat4& value);

	private:
		void Compile(const std::unordered_map<unsigned int, std::string>& shaderSources);
		std::string ReadFile(const std::string& filePath);
		unsigned int GetUniformLocation(const std::string& name);

	private:
		bool m_IsLinked = false;
		unsigned int m_Id = 0;
		std::string m_Name; //for debug

		std::unordered_map<std::string, unsigned int> m_UniformCache;
	};

}