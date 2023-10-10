
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Rigidbody.h"
#include "Sprite.h"

namespace rocket_lab {

	Rigidbody::Rigidbody(Sprite* _sprite, float _colliderRad, short* _fieldWidth, short* _fieldHeight)
	{
		sprite = _sprite;
		colliderRad = _colliderRad;
		fieldWidth = _fieldWidth;
		fieldHeight = _fieldHeight;

		accX = 0;
		accY = 0;
		velX = 0;
		velY = 0;
		x = sprite->getX();
		y = sprite->getY();
	}

	Rigidbody::~Rigidbody() 
	{
		delete fieldWidth;
		delete fieldHeight;
	}

	void Rigidbody::runPhysics(double dt) 
	{
		float totalAccX = accX, totalAccY = accY;

		if (gravityEnabled)
			totalAccY -= gravity;

		velX -= velX * airResRate * dt;
		velY -= velY * airResRate * dt;
		velX += totalAccX * dt;
		velY += totalAccY * dt;

		x += velX * dt;
		y += velY * dt;

		sprite->setPos(x, y);
		sprite->setAngle(atan(velY / velX) + M_PI * (velX<=0));

		float xDiff = abs(x) + colliderRad - *fieldWidth / 2;
		float yDiff = abs(y) + colliderRad - *fieldHeight / 2;
		if (xDiff > 0.0f)
		{
			x -= ((x > 0) - (x < 0)) * xDiff;
			velX = -velX;
			accX = -accX;
		}
		if (yDiff > 0.0f)
		{
			y -= ((y > 0) - (y < 0)) * yDiff;
			velY = -velY;
			accY = -accY;
		}
	}
}