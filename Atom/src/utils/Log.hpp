/*
* @file		Log.hpp
* @author	Abhikalp Unakal
* @brief	Class for Logging functionality
* @date		2021-01-16
*/

#ifndef LOG_HPP
#define LOG_HPP

#include <Pch.hpp>
#include "core/Types.hpp"
#include "lib/spdlog/include/spdlog/spdlog.h"
#include "lib/spdlog/include/spdlog/sinks/stdout_color_sinks.h"

class Log {
public:
	static std::shared_ptr<spdlog::logger>& getLogger() {
		return mLogger;
	}
	static void init(const string& name="Atom", const string& format= "%^[%T] %n: %v%$") {
		spdlog::set_pattern(format);
		mLogger = spdlog::stdout_color_mt(name);
		mLogger->set_level(spdlog::level::trace);
	}
private:
	static std::shared_ptr<spdlog::logger> mLogger;
};

#ifndef SILENT
	#define ATOM_ERROR(...)	Log::getLogger()->error(__VA_ARGS__);
	#define ATOM_WARN(...)	Log::getLogger()->warn(__VA_ARGS__);
	#define ATOM_INFO(...)	Log::getLogger()->info(__VA_ARGS__);
	#define ATOM_TRACE(...)	Log::getLogger()->trace(__VA_ARGS__);
#endif


#ifdef SILENT
	#define LM_ERROR(...)
	#define LM_WARN(...)
	#define LM_INFO(...)
	#define LM_TRACE(...)
	#define LM_FATAL(...)
#endif

#endif