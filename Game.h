#pragma once

#include <vector>
#include "Sprite.h"

namespace rocket_lab
{
	class Game 
	{
	public:
		Game(short _windowWidth, short _windowHeight);
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

		Sprite* rocket;
		
		std::vector<uint16_t> indexVector;
	};

	int run();
}