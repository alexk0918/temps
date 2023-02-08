#ifndef __MIDDLEGROUND_H__
#define __MIDDLEGROUND_H__

#include "Frog.h"
#include "MenuState.h"
#include "FrogMath.h"
#include <Array>
#include "Cats.h"


namespace Webfoot{
	class TestLevel{
	public:

		TestLevel();

		virtual void Init();
		virtual void Deinit();

		virtual void Update(unsigned int dt, Cats* player);
		virtual void Draw();
		void FloorDetection(Point2F catPosition, Point2F catVelocity);

		bool getHitDetection(){ return onGround; }
		bool bonkDetection(){ return bonk; }

	protected:

		Point2F playerPos;
		Point2F playerVelocity;

		Point2F floorPos;
		Image* floor;

		Point2F leftWallPos;
		Image* leftWall;

		Point2F tileOnePosition;
		Image* tileOne;
		Image* cliff;

		bool onGround;
		bool bonk;
		bool catFalling;

		//to check if on ground for certain fields
		bool groundCheck;

	};
}

#endif