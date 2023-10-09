#pragma once

#include "Sprite.h"

namespace rocket_lab
{
	class Game 
	{
	public:
		Game();
		~Game();

		int update();
		
		void updateWindowSizeInfo(short _windowWidth, short _windowHeight);

	private:
		short windowWidth, windowHeight;

		//bgfx
		bgfx::ProgramHandle program;
		bgfx::ShaderHandle vertexShader;
		bgfx::ShaderHandle fragmentShader;

		bgfx::VertexLayout layout;
		bgfx::DynamicVertexBufferHandle vertexBuffer;
		bgfx::IndexBufferHandle indexBuffer;

		bgfx::TextureHandle texture;
		bgfx::UniformHandle textureUniform;

		Sprite::SpriteVertex spriteVertices[4] = {
			{-0.5f, -0.5f, 0.0f, 1.0f}, // sprite
			{0.5f, -0.5f, 1.0f, 1.0f},
			{0.5f, 0.5f, 1.0f, 0.0f},
			{-0.5f, 0.5f, 0.0f, 0.0f}
		};
		const uint16_t vertexIndices[6] = { 0, 1, 2, 0, 2, 3 };
	};

	int run();
}