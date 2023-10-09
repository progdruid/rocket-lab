#pragma once

#include "bgfx/bgfx.h"

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

	Sprite(char* _texturePath, short _size, short& _windowWidth, short& _windowHeight);
	~Sprite();

	short getX() { return x; };
	short getY() { return y; };
	void setX(short _x) { x = _x; updateVertices(); };
	void setY(short _y) { y = _y; updateVertices(); };
	float getAngle() { return angle;  };
	void setAngle(float _angleInRad) { angle = _angleInRad; updateVertices(); };

	void getMappedVertices(SpriteVertex*& arr, int& number) { arr = vectices; number = 4; };
	bgfx::VertexLayout getLayout() { return layout; }

private:
	short x, y;
	float angle;
	short size;

	SpriteVertex vectices[4];
	bgfx::VertexLayout layout;

	void updateVertices();
};