#define STB_IMAGE_IMPLEMENTATION
#include "Resources/texture.h"
#include "Resources/stb_image.h"
#include "Core/Debug/debug.h"
#include "Core/Debug/loader.h"

REGISTER_MODULE();

Texture::Texture()
{
}

Texture::~Texture()
{
    Unload();
}

bool Texture::Load(const std::string& path)
{
    glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        std::string debug_message = "Successfully loaded image: '" + path + "'\n";
        Debug::g_Log.Print(debug_message.c_str());
        stbi_image_free(data);
        return true;
    }
    else
    {
        Debug::g_Log.Print("Failed to open file: '", path.c_str(),"'");
        return false;
    }
}

void Texture::Unload()
{

}
