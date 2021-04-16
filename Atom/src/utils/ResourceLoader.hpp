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
