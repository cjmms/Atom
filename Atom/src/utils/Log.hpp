/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
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
	static void init(const string& name=APPNAME, const string& format= "%^[%T] %n: %v%$") {
		spdlog::set_pattern(format);
		mLogger = spdlog::stdout_color_mt(name);
		mLogger->set_level(spdlog::level::trace);
	}
	static void shutdown() {
		mLogger.reset();
	}
private:
	static std::shared_ptr<spdlog::logger> mLogger;
};

#ifdef DEBUG
	#define ATOM_ERROR(...)	Log::getLogger()->error(__VA_ARGS__);
	#define ATOM_WARN(...)	Log::getLogger()->warn(__VA_ARGS__);
	#define ATOM_INFO(...)	Log::getLogger()->info(__VA_ARGS__);
	#define ATOM_TRACE(...)	Log::getLogger()->trace(__VA_ARGS__);
#endif


#ifndef DEBUG
	#define ATOM_ERROR(...)
	#define ATOM_WARN(...)
	#define ATOM_INFO(...)
	#define ATOM_TRACE(...)
#endif

#endif