#pragma once
#include <memory>
#include <spdlog/spdlog.h>

namespace OpenGLCore
{
	class Logger
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return m_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> m_CoreLogger;
		static std::shared_ptr<spdlog::logger> m_ClientLogger;
	};


#define LOG_CORE_TRACE(...) OpenGLCore::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_INFO(...) OpenGLCore::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARNING(...) OpenGLCore::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_ERROR(...) OpenGLCore::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_CRITICAL(...) OpenGLCore::Logger::GetCoreLogger()->critical(__VA_ARGS__)

#define LOG_CLIENT_TRACE(...) OpenGLCore::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_CLIENT_INFO(...) OpenGLCore::Logger::GetClientLogger()->info(__VA_ARGS__)
#define LOG_CLIENT_WARNING(...) OpenGLCore::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_CLIENT_ERROR(...) OpenGLCore::Logger::GetClientLogger()->error(__VA_ARGS__)
#define LOG_CLIENT_CRITICAL(...) OpenGLCore::Logger::GetClientLogger()->critical(__VA_ARGS__)

}