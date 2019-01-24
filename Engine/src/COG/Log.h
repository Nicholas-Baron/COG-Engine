#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

namespace COG {
	class COG_API Log {
		public:
		static void init(const std::string& app_name);
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
		
		private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

	template<typename T>
	inline void debug_internal(const T& msg) {
		Log::GetCoreLogger()->debug(msg);
	}

	template<typename T>
	inline void info_internal(const T& msg) {
		Log::GetCoreLogger()->info(msg);
	}

	template<typename T>
	inline void warn_internal(const T& msg) {
		Log::GetCoreLogger()->warn(msg);
	}
	
	template<typename T>
	inline void error_internal(const T& msg) {
		Log::GetCoreLogger()->error(msg);
	}
}

#define debug(msg) COG::Log::GetClientLogger()->debug(msg)
#define info(msg) COG::Log::GetClientLogger()->info(msg)
#define warn(msg) COG::Log::GetClientLogger()->warn(msg)
#define error(msg) COG::Log::GetClientLogger()->error(msg)