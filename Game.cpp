#include <iostream>

#include "bgfx/bgfx.h"
#include "utils.h"
#include "Game.h"

namespace rocket_lab
{
	
	Game::Game() 
	{
		windowWidth = 0;
		windowHeight = 0;

		//create layout
		layout.begin(bgfx::RendererType::Direct3D12)
			.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();

		//create buffers
		vertexBuffer = bgfx::createDynamicVertexBuffer(
			bgfx::makeRef(spriteVertices, sizeof(spriteVertices)),
			layout);

		indexBuffer = bgfx::createIndexBuffer(
			bgfx::copy(vertexIndices, sizeof(vertexIndices)));

		//load textures
		texture = loadTexture("res/rocket.png");
		textureUniform = bgfx::createUniform("s_texture", bgfx::UniformType::Sampler, 1);

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
		bgfx::destroy(texture);
		bgfx::destroy(textureUniform);
		bgfx::destroy(vertexBuffer);
		bgfx::destroy(indexBuffer);
		bgfx::destroy(program);
	}

	int Game::update()
	{
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x1e2952ff, 1.0f, 0);
		bgfx::setState(BGFX_STATE_DEFAULT | BGFX_STATE_BLEND_ALPHA);

		bgfx::setTexture(0, textureUniform, texture);

		bgfx::update(vertexBuffer, 0, bgfx::makeRef(spriteVertices, sizeof(spriteVertices)));
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

	/*
	struct SpriteVertex
	{
	public:
		float x, y;
		float u, v;
	};

	int run()
	{
		const float PI = 3.14159f;

		//init glfw, stop execution in case of an error
		if (!glfwInit())
			return -1;

		//create glfw window
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		GLFWwindow* window = glfwCreateWindow(LAB_WIDTH, LAB_HEIGHT, "Rocket Lab", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);


		//init bgfx platform data
		bgfx::PlatformData pd;
		pd.type = bgfx::NativeWindowHandleType::Count;
		pd.context = GetDC(glfwGetWin32Window(window));
		pd.nwh = glfwGetWin32Window(window);


		//init bgfx
		bgfx::Init init;
		init.platformData = pd;
		init.type = bgfx::RendererType::Direct3D12;
		bgfx::init(init);
		bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);



		//create vertex layout
		bgfx::VertexLayout layout;
		layout.begin(bgfx::RendererType::Direct3D12)
			.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();

		//create vertices
		SpriteVertex spriteVertices[4] =
		{
			{-0.5f, -0.5f, 0.0f, 1.0f}, // sprite
			{0.5f, -0.5f, 1.0f, 1.0f},
			{0.5f, 0.5f, 1.0f, 0.0f},
			{-0.5f, 0.5f, 0.0f, 0.0f}
		};

		const uint16_t vertexIndices[6] = { 0, 1, 2, 0, 2, 3 };



		//create buffers
		bgfx::DynamicVertexBufferHandle vertexBuffer = bgfx::createDynamicVertexBuffer(
			bgfx::makeRef(spriteVertices, sizeof(spriteVertices)),
			layout);

		bgfx::IndexBufferHandle indexBuffer = bgfx::createIndexBuffer(
			bgfx::copy(vertexIndices, sizeof(vertexIndices)));



		//texture loading
		bgfx::TextureHandle texture = loadTexture("res/rocket.png");
		bgfx::UniformHandle textureUniform = bgfx::createUniform("s_texture", bgfx::UniformType::Sampler, 1);

		//load shaders
		bgfx::ShaderHandle vertexShader = createShaderFromFile("shaders/vertexShader.bin");
		bgfx::ShaderHandle fragmentShader = createShaderFromFile("shaders/fragmentShader.bin");


		//print some debug info
		std::cout << "VertexBuffer: " << bgfx::isValid(vertexBuffer) << std::endl;
		std::cout << "IndexBuffer: " << bgfx::isValid(indexBuffer) << std::endl;
		std::cout << "Shaders: " << bgfx::isValid(vertexShader) << " " << bgfx::isValid(fragmentShader) << std::endl;


		//create a program
		bgfx::ProgramHandle program = bgfx::createProgram(vertexShader, fragmentShader, true);


		//main loop
		const auto startTime = std::chrono::high_resolution_clock::now();
		int windowWidth, windowHeight;
		while (!glfwWindowShouldClose(window))
		{
			glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
			glfwPollEvents();

			bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x1e2952ff, 1.0f, 0);
			bgfx::setState(BGFX_STATE_DEFAULT | BGFX_STATE_BLEND_ALPHA);

			bgfx::setTexture(0, textureUniform, texture);

			bgfx::update(vertexBuffer, 0, bgfx::makeRef(spriteVertices, sizeof(spriteVertices)));
			bgfx::setVertexBuffer(0, vertexBuffer);
			bgfx::setIndexBuffer(indexBuffer);

			bgfx::submit(0, program, 1.0, BGFX_DISCARD_NONE);
			bgfx::touch(0);
			bgfx::frame();

			//some fun
			const auto timePassed = std::chrono::high_resolution_clock::now() - startTime;
			const float t = std::chrono::duration_cast<std::chrono::milliseconds>(timePassed).count() / 1000.0f;

			spriteVertices[0].x = -0.5f + OSCILLATION_RAD * cos(t);
			spriteVertices[0].y = -0.5f + OSCILLATION_RAD * sin(t);
			spriteVertices[1].x = +0.5f + OSCILLATION_RAD * cos(t + PI / 2.0f);
			spriteVertices[1].y = -0.5f + OSCILLATION_RAD * sin(t + PI / 2.0f);
			spriteVertices[2].x = +0.5f + OSCILLATION_RAD * cos(t + PI);
			spriteVertices[2].y = +0.5f + OSCILLATION_RAD * sin(t + PI);
			spriteVertices[3].x = -0.5f + OSCILLATION_RAD * cos(t + PI * 3 / 2.0f);
			spriteVertices[3].y = +0.5f + OSCILLATION_RAD * sin(t + PI * 3 / 2.0f);
		}


		//terminaion
		bgfx::destroy(texture);
		bgfx::destroy(textureUniform);
		bgfx::destroy(vertexBuffer);
		bgfx::destroy(indexBuffer);
		bgfx::destroy(program);
		bgfx::shutdown();
		glfwTerminate();

		return 0;
	}
	*/
}