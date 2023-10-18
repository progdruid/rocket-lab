#include <iostream>
#include <time.h>
#include "bgfx/bgfx.h"
#include "utils.h"
#include "Game.h"

namespace rocket_lab
{
	
	Game::Game(short _windowWidth, short _windowHeight) 
	{
		windowWidth = _windowWidth;
		windowHeight = _windowHeight;

		textureRenderer = new TextureRenderer("res/rocket.png", "s_texture");

		rocketSprite = new Sprite(50, &windowWidth, &windowHeight);
		rocketSprite->setAnchors(0.0f, 1.0f, 1.0f, 0.0f);
		rocketSprite->setPos(-200, 0);
		rocketBody = new Rigidbody(rocketSprite, 40.0f, &windowWidth, &windowHeight);
		rocketBody->setVelocity(150, 120);

		//create layout
		layout.begin(bgfx::RendererType::Direct3D12)
			.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();
		
		//create buffers
		rocketSprite->appendVerticesToVector(vertexVector);
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

		lastUpdateTime = clock();
	}

	Game::~Game() 
	{
		delete rocketBody;
		delete rocketSprite;
		delete textureRenderer;

		bgfx::destroy(vertexBuffer);
		bgfx::destroy(indexBuffer);
		bgfx::destroy(program);
	}

	int Game::update()
	{
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x121619ff, 1.0f, 0);
		bgfx::setState(BGFX_STATE_DEFAULT | BGFX_STATE_BLEND_ALPHA);

		clock_t now = clock();
		rocketBody->runPhysics((double)(now - lastUpdateTime)/CLOCKS_PER_SEC);
		lastUpdateTime = now;
		textureRenderer->setToRender(0);

		vertexVector.clear();
		rocketSprite->appendVerticesToVector(vertexVector);
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

	void Game::handleDrag(short dragX, short dragY)
	{
		rocketBody->addVelocity(dragX, dragY);
		std::cout << dragX << " " << dragY << std::endl;
	}
}