#pragma once

namespace rocket_lab {
	class DragListener
	{
	public:
		virtual void handleDrag(short dragX, short dragY) = 0;
	};
}