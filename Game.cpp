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

		rocketSprites[0] = new Sprite(50, &windowWidth, &windowHeight);
		rocketSprites[1] = new Sprite(50, &windowWidth, &windowHeight);
		rocketSprites[0]->setAnchors(0.0f, 1.0f, 1.0f, 0.0f);
		rocketSprites[1]->setAnchors(0.0f, 1.0f, 1.0f, 0.0f);
		rocketSprites[0]->setPos(-200, 0);
		rocketSprites[1]->setPos(-300, 100);
		rocketBodies[0] = new Rigidbody(rocketSprites[0], 40.0f, &windowWidth, &windowHeight);
		rocketBodies[1] = new Rigidbody(rocketSprites[1], 40.0f, &windowWidth, &windowHeight);
		rocketBodies[0]->setVelocity(150, 120);
		rocketBodies[1]->setVelocity(-150, 120);

		//create layout
		layout.begin(bgfx::RendererType::Direct3D12)
			.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();
		
		//create buffers
		rocketSprites[0]->appendVerticesToVector(vertexVector);
		rocketSprites[1]->appendVerticesToVector(vertexVector);
		vertexBuffer = bgfx::createDynamicVertexBuffer(
			bgfx::copy(vertexVector.data(), vertexVector.size() * sizeof(Sprite::SpriteVertex)),
			layout);

		indexVector = Sprite::generateIndexVector(2);
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
		delete rocketBodies[0];
		delete rocketBodies[1];
		delete rocketSprites[0];
		delete rocketSprites[1];
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
		rocketBodies[0]->runPhysics((double)(now - lastUpdateTime) / CLOCKS_PER_SEC);
		rocketBodies[1]->runPhysics((double)(now - lastUpdateTime) / CLOCKS_PER_SEC);
		lastUpdateTime = now;
		textureRenderer->setToRender(0);

		vertexVector.clear();
		rocketSprites[0]->appendVerticesToVector(vertexVector);
		rocketSprites[1]->appendVerticesToVector(vertexVector);
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
		rocketBodies[0]->addVelocity(dragX, dragY);
		rocketBodies[1]->addVelocity(dragX, dragY);
		std::cout << dragX << " " << dragY << std::endl;
	}
}