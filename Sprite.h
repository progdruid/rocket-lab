#pragma once

#include <vector>
#include "bgfx/bgfx.h"

namespace rocket_lab {

	class Sprite
	{
	public:
		struct SpriteVertex
		{
			//should be private
		public:
			float x, y;
			float u, v;
		};

		static std::vector<uint16_t> generateIndexVector(const size_t numSprites);

		Sprite(short _size, short* _windowWidth, short* _windowHeight);
		~Sprite();

		short getX() { return x; };
		short getY() { return y; };
		void setX(short _x) { x = _x; updateVertices(); };
		void setY(short _y) { y = _y; updateVertices(); };
		void setPos(short _x, short _y) { x = _x; y = _y; updateVertices(); };
		void setTranform(short _x, short _y, float _angleInRad) { x = _x; y = _y; angle = _angleInRad; updateVertices(); }
		float getAngle() { return angle; };
		void setAngle(float _angleInRad) { angle = _angleInRad; updateVertices(); };

		std::vector<SpriteVertex> getMappedVertices() { return vertices; };

	private:
		short x, y;
		float angle;
		short size;

		short* windowWidth, * windowHeight;

		std::vector<SpriteVertex> vertices;

		void updateVertices();
	};
}