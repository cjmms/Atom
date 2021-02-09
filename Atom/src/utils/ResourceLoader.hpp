#ifndef RESOURCELOADER_HPP
#define RESOURCELOADER_HPP
#include "Pch.hpp"
#include "core/Types.hpp"

// textures
void loadResource(unsigned int& id, string filename);
void unloadResource(unsigned int& id);

void loadResource(AudioSample& asd, string filename);
void unloadResource(AudioSample& asd);

#endif // !RESOURCELOADER_HPP
