#pragma once
#include <string>
#include <memory>
#include <vector>

namespace OpenGLCore::Graphics
{
	enum class ShaderType
	{
		Vertex = 0,
		Fragment = 1,
	};

	struct ShaderSource
	{
		ShaderSource()
			:Type(ShaderType::Vertex), SourceCode("") {}

		ShaderSource(ShaderType type, const std::string& sourceCode)
			:Type(type), SourceCode(sourceCode) {}

		std::string SourceCode;
		ShaderType Type;
	};


	class Shader
	{
	public:
		Shader(const ShaderSource& shaderSource);
		Shader(const std::string& filePath, ShaderType shaderType);
		~Shader();

		bool Compile();
		std::string GetInfoLog();
		ShaderType GetType() const { return m_ShaderType; }

		bool GetIsCompiled() const { return m_IsCompiled; }

	private:
		std::string ReadFile(const std::string& filePath);

	private:
		unsigned int m_Id;
		ShaderType m_ShaderType;

		bool m_IsCompiled = false;
		friend class Program;
	};

	class Program
	{
	public:
		Program(const std::string& name = "Program");
		~Program();

		bool Create(std::vector<Shader> shaders);
		std::string GetInfoLog();

		void Use() const;

	private:
		bool m_IsLinked = false;
		unsigned int m_Id = 0;
		std::string m_Name; //for debug
	};

}