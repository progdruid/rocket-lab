#pragma once

#include "bgfx/bgfx.h"

namespace rocket_lab {
	class TextureRenderer
	{
	public:
		TextureRenderer(const char* texturePath,const char* uniformName);
		~TextureRenderer();

		void setToRender(uint8_t stage, uint32_t flags = UINT32_MAX);

	private:
		bgfx::TextureHandle texture;
		bgfx::UniformHandle uniform;
	};
}
