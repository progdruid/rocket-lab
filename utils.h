#pragma once

#include "bgfx/bgfx.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace rocket_lab {

	bgfx::ShaderHandle createShaderFromFile(const char* filePath);
	bgfx::TextureHandle loadTexture(const char* filePath);
}