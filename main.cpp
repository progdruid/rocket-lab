#define LAB_WIDTH 1200
#define LAB_HEIGHT 800

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

#include "Game.h"
#include "InputHandler.h"

int run()
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

	rocket_lab::InputHandler* inputHandler = new rocket_lab::InputHandler(window);
	rocket_lab::Game* game = new rocket_lab::Game(LAB_WIDTH, LAB_HEIGHT);
	inputHandler->subscribeDragListener(game);

	int windowWidth, windowHeight;
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
		game->updateWindowSizeInfo(windowWidth, windowHeight);

		game->update();
	}

	inputHandler->unsubscribeDragListener(game);
	delete game;
	delete inputHandler;
	bgfx::shutdown();
	glfwTerminate();

	return 0;
}

int main()
{
	int exitCode = 0;
	exitCode = run();
	return exitCode;
}