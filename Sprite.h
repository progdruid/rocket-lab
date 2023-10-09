#pragma once

#include <vector>
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

	static std::vector<uint16_t> generateIndexVector(int numSprites);

	Sprite(char* _texturePath, char* _uniformName, short _size, short* _windowWidth, short* _windowHeight);
	~Sprite();

	short getX() { return x; };
	short getY() { return y; };
	void setX(short _x) { x = _x; updateVertices(); };
	void setY(short _y) { y = _y; updateVertices(); };
	void setPos(short _x, short _y) { x = _x; y = _y; updateVertices(); };
	float getAngle() { return angle;  };
	void setAngle(float _angleInRad) { angle = _angleInRad; updateVertices(); };

	void setTextureToRender(uint8_t stage, uint32_t flags = UINT32_MAX) { bgfx::setTexture(stage, uniform, texture, flags); }
	std::vector<SpriteVertex> getMappedVertices() { return vertices; };

private:
	short x, y;
	float angle;
	short size;

	short *windowWidth, *windowHeight;

	std::vector<SpriteVertex> vertices;

	bgfx::TextureHandle texture;
	bgfx::UniformHandle uniform;

	void updateVertices();
};