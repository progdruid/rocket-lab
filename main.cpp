#define BX_CONFIG_DEBUG 0;

#include <iostream>

#include "bx/bx.h"
#include "bimg/bimg.h"
#include "bgfx/bgfx.h"
#include "glfw/glfw3.h"

int main()
{
	bx::debugPrintf("test");
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	glfwCreateWindow(100, 100, "Title", NULL, NULL);
	int m;
	std::cin >> m;
	return 0;
}