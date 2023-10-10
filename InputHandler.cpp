
#include <iostream>
#include <vector>
#include "glfw/glfw3.h"
#include "InputHandler.h"

namespace rocket_lab {

	InputHandler* InputHandler::instance;

	InputHandler::InputHandler(GLFWwindow* _window)
	{
		instance = this;
		window = _window;
		inDrag = false;
		dragStartX = 0;
		dragStartY = 0;

		glfwSetMouseButtonCallback(window, handleMouseButtonActionStatic);
	}

	InputHandler::~InputHandler()
	{
		glfwSetMouseButtonCallback(window, NULL);
	}

	void InputHandler::handleMouseButtonAction(GLFWwindow* window, int button, int action, int mods)
	{
		if (button != GLFW_MOUSE_BUTTON_LEFT)
			return;
		
		double x, y;
		int windowWidth, windowHeight;
		glfwGetCursorPos(window, &x, &y);
		glfwGetWindowSize(window, &windowWidth, &windowHeight);

		if (action == GLFW_PRESS) 
		{
			dragStartX = x;
			dragStartY = windowHeight - y;

			inDrag = true;
		}
		else if (action == GLFW_RELEASE && inDrag) 
		{
			short dragX = x - dragStartX;
			short dragY = windowHeight - y - dragStartY;

			for (int i = 0; i < listeners.size(); i++)
				listeners[i]->handleDrag(dragX, dragY);

			inDrag = false;
		}
	}

	void InputHandler::subscribeDragListener(DragListener* _listener) { listeners.push_back(_listener); }

	void InputHandler::unsubscribeDragListener(DragListener* _listener)
	{
		const auto iter = std::find(listeners.begin(), listeners.end(), _listener);
		if (iter != listeners.end())
			listeners.erase(iter);
	}
}