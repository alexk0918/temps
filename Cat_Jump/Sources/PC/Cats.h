#ifndef __CATS_H__
#define __CATS_H__

#include "Frog.h"
#include "MenuState.h"
#include "FrogMath.h"
#include <Array>


namespace Webfoot{
	class Cats{
	public:
		Cats();
		virtual ~Cats() {};

		virtual void Init();
		virtual void Deinit();

		virtual void Update(unsigned int dt, bool grounded, bool bonked);
		virtual void Draw();
		
		void PositionSet(float x, float y);
		Point2F PositionGet() { return position; }

		void VelocitySet(float x, float y);
		Point2F VelocityGet(){ return velocity; }



		bool directionFacing(){ return faceRight; }

	protected:

		void AnimationHandler(int catimation, bool faceRight);

		bool inAir;
		bool faceRight;
		bool moving;

		//int for thw switch
		int catimation;

		Point2F gravity;
		Point2F position;
		Point2F jumpPower;
		Point2F velocity;


		Sprite* cat;
	};

}


#endif