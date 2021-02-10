/*
* @file		Pch.hpp
* @author	Abhikalp Unakal
* @brief	PreCompiled Header
* @date		2021-01-12
*/

#ifndef PCH_HPP
#define PCH_HPP

#include <cassert>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <bitset>
#include <memory>
#include <functional>
#include <any>
#include <set>
#include <queue>
#include <list>
#include <vector>
#include <array>
#include <deque>
#include <unordered_map>
#include <chrono>
#include <limits>
#include <sstream>
#include <stack>
#include <stdint.h>
#include <random>

// only include very rarely changing headers here
// frequently changing headers increase compile times due to recompilation of .pch stores
// libraries that are already tested and working and wont change much are good candidates
#include "lib/nlohmann/json.hpp"
#include "lib/glm/glm/glm.hpp"
#include "fmod_studio.hpp"
#include "fmod.hpp"
#include "fmod_common.h"
#include "fmod_errors.h"
#endif