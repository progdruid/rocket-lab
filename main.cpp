#define LAB_WIDTH 800
#define LAB_HEIGHT 600

#include <iostream>
#include <cstring>

#define _ITERATOR_DEBUG_LEVEL 0
#define BX_CONFIG_DEBUG 0;
#include "bx/bx.h"
#include "bimg/bimg.h"
#include "bgfx/bgfx.h"
#include "bgfx/platform.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <Windows.h>
#include "glfw/glfw3.h"
#include "glfw/glfw3native.h"

#include "utils.h"

struct SpriteVertex
{
public:
	float x, y, z;
	float r, g, b;
};

int main()
{
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


	//create vertices
	SpriteVertex spriteVertices[4] =
	{
		{-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f}, // White quad
		{0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f},
		{0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f},
		{-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f}
	};

	const uint16_t vertexIndices[6] = { 0, 1, 2, 0, 2, 3 };


	//create layout
	bgfx::VertexLayout layout;
	layout.begin(bgfx::RendererType::Direct3D12)
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 3, bgfx::AttribType::Float)
		.end();


	//create buffers
	bgfx::DynamicVertexBufferHandle vertexBuffer = bgfx::createDynamicVertexBuffer(
		bgfx::makeRef(spriteVertices, sizeof(spriteVertices)), 
		layout);

	bgfx::IndexBufferHandle indexBuffer = bgfx::createIndexBuffer(
		bgfx::copy(vertexIndices, sizeof(vertexIndices)));


	//load shaders
	bgfx::ShaderHandle vertexShader = createShaderFromFile("shaders/vertexShader.bin");
	bgfx::ShaderHandle fragmentShader = createShaderFromFile("shaders/fragmentShader.bin");


	//print some debug info
	std::cout << "VertexBuffer: " << bgfx::isValid(vertexBuffer) << std::endl;
	std::cout << "IndexBuffer: " << bgfx::isValid(indexBuffer) << std::endl;
	std::cout << "Shaders: " << bgfx::isValid(vertexShader) << " " << bgfx::isValid(fragmentShader) << std::endl;


	//createa program
	bgfx::ProgramHandle program = bgfx::createProgram(vertexShader, fragmentShader, true);


	//main loop
	int windowWidth, windowHeight;
	while (!glfwWindowShouldClose(window))
	{
		glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
		glfwPollEvents();

		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x1e2952ff, 1.0f, 0);
		bgfx::setState(BGFX_STATE_DEFAULT);

		bgfx::update(vertexBuffer, 0, bgfx::makeRef(spriteVertices, sizeof(spriteVertices)));
		bgfx::setVertexBuffer(0, vertexBuffer);
		bgfx::setIndexBuffer(indexBuffer);

		bgfx::submit(0, program, 1.0, BGFX_DISCARD_NONE);
		bgfx::touch(0);
		bgfx::frame();
		
		//some fun
		spriteVertices[0].x -= 0.0001f;
	}


	//terminaion
	bgfx::destroy(vertexBuffer);
	bgfx::shutdown();
	glfwTerminate();

	return 0;
}