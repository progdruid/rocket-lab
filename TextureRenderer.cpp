#include "TextureRenderer.h"
#include "utils.h"

namespace rocket_lab {
	TextureRenderer::TextureRenderer(const char* texturePath, const char* uniformName)
	{
		texture = loadTexture(texturePath);
		uniform = bgfx::createUniform(uniformName, bgfx::UniformType::Sampler, 1);
	}

	TextureRenderer::~TextureRenderer()
	{
		bgfx::destroy(texture);
		bgfx::destroy(uniform);
	}

	void TextureRenderer::setToRender(uint8_t stage, uint32_t flags)
	{
		bgfx::setTexture(stage, uniform, texture, flags);
	}
}