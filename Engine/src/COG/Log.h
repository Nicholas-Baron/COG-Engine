#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

namespace COG {
	class Log {
		public:
		static void init(const std::string& appname);
		inline static std::shared_ptr<spdlog::logger> core_logger() noexcept { return s_CoreLogger; }
		COG_API inline static std::shared_ptr<spdlog::logger> client_logger() noexcept { return s_ClientLogger; }
		
		private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

	template<typename T>
	inline void debug_internal(const T& msg) {
		Log::core_logger()->debug(msg);
	}

	template<typename T>
	inline void info_internal(const T& msg) {
		Log::core_logger()->info(msg);
	}

	template<typename T>
	inline void warn_internal(const T& msg) {
		Log::core_logger()->warn(msg);
	}
	
	template<typename T>
	inline void error_internal(const T& msg) {
		Log::core_logger()->error(msg);
	}

#ifdef COG_ENABLE_ASSERTS
	inline void COG_ASSERT_INTERNAL(bool x, const std::string& msg = "") {
		if(!x) { 
			COG::error_internal("Internal Assert failed: " + msg); 
			__debugbreak();
		}
	}
#else
	inline void COG_ASSERT_INTERNAL(bool x, const std::string& msg = "") noexcept {}
#endif // COG_ENABLE_ASSERTS

}

//Suggestion: Make these inline void functions
#define debug(msg) COG::Log::client_logger()->debug(msg)
#define info(msg) COG::Log::client_logger()->info(msg)
#define warn(msg) COG::Log::client_logger()->warn(msg)
#define error(msg) COG::Log::client_logger()->error(msg)

#ifdef COG_ENABLE_ASSERTS
inline COG_API void COG_ASSERT(bool x, const std::string& msg = "") {
	if(!x) { error("Assert failed: " + msg); __debugbreak(); }
}
#else
inline COG_API void COG_ASSERT(bool x, const std::string& msg = "") noexcept {}
#endif // COG_ENABLE_ASSERTS
