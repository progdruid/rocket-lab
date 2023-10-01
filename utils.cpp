#include <iostream>
#include <fstream>
#include <vector>

#define _ITERATOR_DEBUG_LEVEL 0
#define BX_CONFIG_DEBUG 0;
#include "bx/bx.h"
#include "bx/readerwriter.h"
#include "bimg/bimg.h"
#include "bgfx/bgfx.h"

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
    const bgfx::Memory* shaderMemory = bgfx::makeRef(shaderData.data(), static_cast<uint32_t>(fileSize));

    // Create and return the shader handle
    return bgfx::createShader(shaderMemory);
}
