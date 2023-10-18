#pragma once

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include "bgfx/bgfx.h"
#include "Sprite.h"
#include "utils.h"

namespace rocket_lab {

	Sprite::Sprite(short _size, short* _windowWidth, short* _windowHeight)
	{
		windowWidth = _windowWidth;
		windowHeight = _windowHeight;

		size = _size;
		x = 0; y = 0;
		angle = 0.0f;

		vertices.resize(4);
		updateVertices();
	}

	Sprite::~Sprite() {}

	void Sprite::setAnchors(float leftX, float rightX, float botY, float topY)
	{
		vertices[0].u = leftX; vertices[0].v = botY;
		vertices[1].u = rightX; vertices[1].v = botY;
		vertices[2].u = rightX; vertices[2].v = topY;
		vertices[3].u = leftX; vertices[3].v = topY;
	}

	void Sprite::updateVertices()
	{
		float sinVal = size * sin(angle);
		float cosVal = size * cos(angle);

		//add angle calculations
		vertices[0] = { (x - cosVal + sinVal)*2/(float)*windowWidth, (y - sinVal - cosVal)*2/(float)*windowHeight, vertices[0].u, vertices[0].v};
		vertices[1] = { (x + cosVal + sinVal)*2/(float)*windowWidth, (y + sinVal - cosVal)*2/(float)*windowHeight, vertices[1].u, vertices[1].v};
		vertices[2] = { (x + cosVal - sinVal)*2/(float)*windowWidth, (y + sinVal + cosVal)*2/(float)*windowHeight, vertices[2].u, vertices[2].v};
		vertices[3] = { (x - cosVal - sinVal)*2/(float)*windowWidth, (y - sinVal + cosVal)*2/(float)*windowHeight, vertices[3].u, vertices[3].v};
		
	}

	std::vector<uint16_t> Sprite::generateIndexVector(const size_t numSprites)
	{
		std::vector<uint16_t> indices;
		indices.resize(numSprites * 6);
		for (int i = 0; i < numSprites; i++)
		{
			indices[i * 6] = i * 4;
			indices[i * 6 + 1] = i * 4 + 1;
			indices[i * 6 + 2] = i * 4 + 2;
			indices[i * 6 + 3] = i * 4;
			indices[i * 6 + 4] = i * 4 + 2;
			indices[i * 6 + 5] = i * 4 + 3;
		}

		return indices;
	}
}