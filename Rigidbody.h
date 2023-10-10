#pragma once

#include "Sprite.h"

namespace rocket_lab {

	class Rigidbody
	{
	public:
		Rigidbody(Sprite* _sprite, float _colliderRad, short* _fieldWidth, short* _fieldHeight);
		~Rigidbody();

		void toggleGravity(bool value) { gravityEnabled = value; };
		void setVelocity(float _velX, float _velY) { velX = _velX; velY = _velY; };
		void addVelocity(float _dvelX, float _dvelY) { velX += _dvelX; velY += _dvelY; }
		void setAcceleration(float _accX, float _accY) { accX = _accX; accY = _accY; };

		void runPhysics(double dt);

	private:
		Sprite* sprite;

		short *fieldWidth, *fieldHeight;
		float colliderRad;

		float velX, velY;
		float accX, accY;
		float x, y;

		bool gravityEnabled = true;
		const float gravity = 9.8f * 80;
		const float airResRate = 0.1f; //%
	};
}
