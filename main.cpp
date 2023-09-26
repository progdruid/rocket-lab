#define LAB_WIDTH 800
#define LAB_HEIGHT 600

#include <iostream>

#define _ITERATOR_DEBUG_LEVEL 0
#define BX_CONFIG_DEBUG 1;
#include "bx/bx.h"
#include "bimg/bimg.h"
#include "bgfx/bgfx.h"
#include "bgfx/platform.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <Windows.h>
#include "glfw/glfw3.h"
#include "glfw/glfw3native.h"

int main()
{
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	
	GLFWwindow* window = glfwCreateWindow(LAB_WIDTH, LAB_HEIGHT, "Rocket Lab", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);

	bgfx::PlatformData pd;
	pd.type = bgfx::NativeWindowHandleType::Count;
	pd.context = GetDC(glfwGetWin32Window(window));
	pd.nwh = glfwGetWin32Window(window);

	bgfx::Init init;
	init.platformData = pd;
	init.type = bgfx::RendererType::Direct3D12;
	bgfx::init(init);

	int windowWidth, windowHeight;

	while (!glfwWindowShouldClose(window))
	{
		//glfwGetWindowSize(window, &windowWidth, &windowHeight);
		glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
		glfwPollEvents();

		//std::cout << windowWidth << " " << windowHeight << std::endl;
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x405030ff, 1.0f, 0);
		bgfx::setViewRect(0, 0, 0, uint16_t(windowWidth), uint16_t(windowHeight));
		//bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
		bgfx::touch(0);

		bgfx::frame();
	}

	bgfx::shutdown();
	glfwTerminate();

}