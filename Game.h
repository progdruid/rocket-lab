#pragma once

#include <vector>
#include "Sprite.h"
#include "Rigidbody.h"
#include "DragListener.h"

namespace rocket_lab
{
	class Game : public DragListener
	{
	public:
		Game(short _windowWidth, short _windowHeight);
		~Game();
		
		int update();
		
		void updateWindowSizeInfo(short _windowWidth, short _windowHeight);
		void handleDrag(short dragX, short dragY);

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
	};
}