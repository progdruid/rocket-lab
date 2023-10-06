#include <iostream>
#include <fstream>
#include <vector>

#define _ITERATOR_DEBUG_LEVEL 0
#define BX_CONFIG_DEBUG 0;
#include "bx/bx.h"
#include "bx/readerwriter.h"
#include "bimg/bimg.h"
#include "bgfx/bgfx.h"

#include "stb_image.h"

bgfx::ShaderHandle createShaderFromFile(const char* filePath)
{
    // Open the shader file
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        return BGFX_INVALID_HANDLE;
    }

    // Get the size of the file
    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Read the shader source code into a vector
    std::vector<char> shaderData(static_cast<size_t>(fileSize));
    if (!file.read(shaderData.data(), fileSize))
    {
        std::cerr << "Failed to read shader file: " << filePath << std::endl;
        return BGFX_INVALID_HANDLE;
    }

    // Close the file
    file.close();

    // Create a BGFX memory reference from the shader source code
    const bgfx::Memory* shaderMemory = bgfx::copy(shaderData.data(), static_cast<uint32_t>(fileSize));

    // Create and return the shader handle
    return bgfx::createShader(shaderMemory);
}

bgfx::TextureHandle loadTexture(const char* filePath)
{
    int width, height, numChannels;
    stbi_uc* textureRaw = stbi_load(filePath, &width, &height, &numChannels, STBI_rgb_alpha);
    
    const bgfx::Memory* textureMem = bgfx::copy(textureRaw, width * height * STBI_rgb_alpha);
    bgfx::TextureHandle texture = bgfx::createTexture2D(width, height, false, 1, bgfx::TextureFormat::RGBA8, 0, textureMem);
    
    stbi_image_free(textureRaw);
    return texture;
}
