#include <Pch.hpp>
#include "utils/Log.hpp"

// defining static members outside class and outside header(to prevent multiple definitions)
std::shared_ptr<spdlog::logger> Log::mLogger;