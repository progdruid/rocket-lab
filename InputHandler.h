#pragma once

#include <vector>
#include "glfw/glfw3.h"
#include "DragListener.h"

namespace rocket_lab {

	class InputHandler
	{
	public:
		InputHandler(GLFWwindow* _window);
		~InputHandler();

		void subscribeDragListener(DragListener* _listener);
		void unsubscribeDragListener(DragListener* _listener);

	private:
		static InputHandler* instance;
		static void handleMouseButtonActionStatic(GLFWwindow* window, int button, int action, int mods) 
		{ instance->handleMouseButtonAction(window, button, action, mods); };
		void handleMouseButtonAction(GLFWwindow* window, int button, int action, int mods);

		std::vector<DragListener*> listeners;

		GLFWwindow* window;
		bool inDrag;
		short dragStartX, dragStartY;
	};
}