#pragma once

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include "bgfx/bgfx.h"
#include "Sprite.h"
#include "utils.h"

namespace rocket_lab {

	Sprite::Sprite(char* _texturePath, char* _uniformName, short _size, short* _windowWidth, short* _windowHeight)
	{
		windowWidth = _windowWidth;
		windowHeight = _windowHeight;

		texture = rocket_lab::loadTexture(_texturePath);
		uniform = bgfx::createUniform(_uniformName, bgfx::UniformType::Sampler, 1);

		size = _size;
		x = 0; y = 0;
		angle = 0.0f;

		vertices.push_back({ -0.5f, -0.5f, 0.0f, 1.0f });
		vertices.push_back({ 0.5f, -0.5f, 1.0f, 1.0f });
		vertices.push_back({ 0.5f,  0.5f, 1.0f, 0.0f });
		vertices.push_back({ -0.5f,  0.5f, 0.0f, 0.0f });

		updateVertices();
	}

	Sprite::~Sprite()
	{
		delete windowWidth;
		delete windowHeight;
		bgfx::destroy(texture);
		bgfx::destroy(uniform);
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

		std::cout << vertices[0].x * vertices[1].x + vertices[0].y * vertices[1].y << std::endl;
	}

	std::vector<uint16_t> Sprite::generateIndexVector(const int numSprites)
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