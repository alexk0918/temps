#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Frog.h"
#include "MenuState.h"
#include "FrogMath.h"
#include <Array>

namespace Webfoot{

	/*
	class Camera{
	public:
		Camera();
		virtual void Init();
		virtual void Deinit();

		virtual void Update(unsigned int dt, Point2F catPosition);
		virtual void Draw();
	protected:
		Point2F position;
		float offsetX;
		float offsetY;

	};
	*/
	class Camera
	{
	public:
		Camera();
		void update(float playerX, float playerY);
		float x, y, offsetX, offsetY;
	};
}

#endif