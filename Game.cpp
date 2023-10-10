#include <iostream>

#include "bgfx/bgfx.h"
#include "utils.h"
#include "Game.h"

namespace rocket_lab
{
	
	Game::Game(short _windowWidth, short _windowHeight) 
	{
		windowWidth = _windowWidth;
		windowHeight = _windowHeight;

		//create layout
		layout.begin(bgfx::RendererType::Direct3D12)
			.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();

		rocket = new Sprite((char*)("res/rocket.png"), (char*)("s_texture"), 100, &windowWidth, &windowHeight);
		rocket->setAngle(1.5f);
		
		//create buffers
		std::vector<Sprite::SpriteVertex> vertexVector = rocket->getMappedVertices();
		vertexBuffer = bgfx::createDynamicVertexBuffer(
			bgfx::copy(vertexVector.data(), vertexVector.size() * sizeof(Sprite::SpriteVertex)),
			layout);

		indexVector = Sprite::generateIndexVector(1);
		indexBuffer = bgfx::createIndexBuffer(
			bgfx::copy(indexVector.data(), indexVector.size() * sizeof(uint16_t)));


		//load shaders
		vertexShader = createShaderFromFile("shaders/vertexShader.bin");
		fragmentShader = createShaderFromFile("shaders/fragmentShader.bin");

		//print some debug info
		std::cout << "VertexBuffer: " << bgfx::isValid(vertexBuffer) << std::endl;
		std::cout << "IndexBuffer: " << bgfx::isValid(indexBuffer) << std::endl;
		std::cout << "Shaders: " << bgfx::isValid(vertexShader) << " " << bgfx::isValid(fragmentShader) << std::endl;

		//create a program
		program = bgfx::createProgram(vertexShader, fragmentShader, true);
	}

	Game::~Game() 
	{
		//bgfx::destroy(texture);
		//bgfx::destroy(textureUniform);
		bgfx::destroy(vertexBuffer);
		bgfx::destroy(indexBuffer);
		bgfx::destroy(program);
	}

	int Game::update()
	{
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x1e2952ff, 1.0f, 0);
		bgfx::setState(BGFX_STATE_DEFAULT | BGFX_STATE_BLEND_ALPHA);

		rocket->setTextureToRender(0);

		auto vertexVector = rocket->getMappedVertices();
		bgfx::update(vertexBuffer, 0, bgfx::copy(vertexVector.data(), vertexVector.size() * sizeof(Sprite::SpriteVertex)));
		bgfx::setVertexBuffer(0, vertexBuffer);
		bgfx::setIndexBuffer(indexBuffer);

		bgfx::submit(0, program, 1.0, BGFX_DISCARD_NONE);
		bgfx::touch(0);
		bgfx::frame();

		return 0;
	}

	void Game::updateWindowSizeInfo(short _windowWidth, short _windowHeight)
	{
		windowWidth = _windowWidth;
		windowHeight = _windowHeight;
	}
}