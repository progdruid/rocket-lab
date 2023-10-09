#pragma once

#include "bgfx/bgfx.h"
#include "stb_image.h"

namespace rocket_lab {

	bgfx::ShaderHandle createShaderFromFile(const char* filePath);
	bgfx::TextureHandle loadTexture(const char* filePath);
}