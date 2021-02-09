#include "Pch.hpp"
#include "ResourceLoader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/glew.h>
#include "utils/Log.hpp"
#include "core/AtomEngine.hpp"

extern AtomEngine ae;


// AUDIO
void loadResource(AudioSample& asd, string filename) {
    FMOD_ERROR(ae.mAudioManager->mCoreSystem->createSound(filename.c_str(), asd.mode, asd.exinfo, &asd.sound));
}

void unloadResource(AudioSample& asd) {
    FMOD_ERROR(asd.sound->release());
}



// TEXTURE 
void loadResource(unsigned int& id, string filename) {

    // enable gamma correction
    bool gamma = true;
    stbi_set_flip_vertically_on_load(true);
    glGenTextures(1, &id);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum internalFormat;
        GLenum dataFormat;
        if (nrComponents == 1)
        {
            internalFormat = dataFormat = GL_RED;
        }
        else if (nrComponents == 3)
        {
            internalFormat = gamma ? GL_SRGB : GL_RGB;
            dataFormat = GL_RGB;
        }
        else if (nrComponents == 4)
        {
            internalFormat = gamma ? GL_SRGB_ALPHA : GL_RGBA;
            dataFormat = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
        ATOM_ERROR(" loaded successfully.")
    }
    else
    {
        ATOM_ERROR("Texture failed to load at path: {}", filename);
        stbi_image_free(data);
    }
}


void unloadResource(unsigned int& id) {

}



