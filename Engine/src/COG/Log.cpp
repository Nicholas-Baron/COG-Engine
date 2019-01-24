#include "precomp/precomp.h"

#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace COG {
	
	COG_API std::shared_ptr<spdlog::logger> Log::s_CoreLogger, Log::s_ClientLogger;

	void Log::init(const std::string& app_name) {
		
		using namespace spdlog;
		set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = stdout_color_mt("COG");
		s_CoreLogger->set_level(level::trace);

		s_ClientLogger = stdout_color_mt(app_name);
		s_ClientLogger->set_level(level::trace);
	}

}