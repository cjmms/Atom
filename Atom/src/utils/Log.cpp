/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
*
* @file		Log.cpp
* @author	Abhikalp Unakal
* @brief	Class for Logging functionality
* @date		2021-01-16
*/

#include <Pch.hpp>
#include "utils/Log.hpp"

// defining static members outside class and outside header(to prevent multiple definitions)
std::shared_ptr<spdlog::logger> Log::mLogger;