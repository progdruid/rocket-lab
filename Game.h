#pragma once

#include <chrono>
#include <vector>
#include "Sprite.h"
#include "Rigidbody.h"

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

		Sprite* rocketSprite;
		Rigidbody* rocketBody;
		
		std::vector<uint16_t> indexVector;

		std::chrono::steady_clock::time_point lastTick;
	};

	int run();
}