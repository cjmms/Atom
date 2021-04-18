/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
*
* @file		ResourceLoader.hpp
* @author	Xingyu Wang
* @brief	load texture
* @date		2021-01-16
*/

#ifndef RESOURCELOADER_HPP
#define RESOURCELOADER_HPP
#include "Pch.hpp"
#include "core/Types.hpp"

// textures
void loadResource(unsigned int& id, string filename);
void unloadResource(unsigned int& id);

//void loadResource(Grid& tilemap, string filename);
//void unloadResource(Grid& tilemap);

#endif // !RESOURCELOADER_HPP
