#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Croc 
{
	class CROC_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger;  }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

}


// Core log macros
#define CROC_CORE_TRACE(...)     ::Croc::Log::GetCoreLogger()->trace(__VA_ARGS__) 
#define CROC_CORE_INFO(...)      ::Croc::Log::GetCoreLogger()->info(__VA_ARGS__) 
#define CROC_CORE_WARN(...)      ::Croc::Log::GetCoreLogger()->warn(__VA_ARGS__) 
#define CROC_CORE_ERROR(...)     ::Croc::Log::GetCoreLogger()->error(__VA_ARGS__) 
#define CROC_CORE_FATAL(...)     ::Croc::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define CROC_TRACE(...)          ::Croc::Log::GetClientLogger()->trace(__VA_ARGS__) 
#define CROC_INFO(...)           ::Croc::Log::GetClientLogger()->info(__VA_ARGS__) 
#define CROC_WARN(...)           ::Croc::Log::GetClientLogger()->warn(__VA_ARGS__) 
#define CROC_ERROR(...)          ::Croc::Log::GetClientLogger()->error(__VA_ARGS__) 
#define CROC_FATAL(...)          ::Croc::Log::GetClientLogger()->fatal(__VA_ARGS__)