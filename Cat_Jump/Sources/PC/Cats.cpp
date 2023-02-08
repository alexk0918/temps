#include "Frog.h"
#include "MenuState.h"
#include "FrogMath.h"
#include <Array>
#include "Cats.h"

using namespace Webfoot;

Cats::Cats(){
	cat = NULL;
}

void Cats::Init(){
	//sprite stuff
	cat = frog_new Sprite();
	cat->Init("Sprites/Sprites", "Cat");

	// Cat be in the middle of the screen
	position = Point2F::Create(theScreen->SizeGet()/ 2);

	//movement I guess
	gravity.Set(0.0f, 30.0f);
	velocity.Set(0.0f, 0.0f);

	//i dont think i do anything with this... oops
	cat->PositionSet(position - (cat->SizeGet(1) / 2));

	//stuff that i dont know how to describe :D
	DebugPrintf("%7.2lf, %7.2lf \n", position.x, position.y);
	jumpPower.Set(0.0f, 0.0f);
	inAir = TRUE;
	faceRight = FALSE;
}

void Cats::Deinit(){
	//stuff goes bye bye
	if (cat){
		SmartDeinitDelete(cat);
	}
}

void Cats::Update(unsigned int dt, bool grounded, bool bonked){
	//update the sprites
	cat->Update(dt);
	float dtSeconds = (float)dt / 1000.f;

	//make position move
	position += velocity *dtSeconds;


	//Sprites
	cat->PositionSet(position);

	//put at top of screen
	if (position.y >= theScreen->SizeGet().y){
		position.y = 0;
	}
	//bottom screen
	if (position.y <= 0){
		position.y = theScreen->SizeGet().y;
	}
	if (bonked == TRUE){
		velocity.x *= -1;
	}

	if (velocity.x > 0){ faceRight = TRUE; }
	else if (velocity.x < 0){ faceRight = FALSE; }

	//checks the bool
	switch (grounded)
	{
	default:
		//should be falling
		inAir = TRUE;


		//movement
		velocity += gravity;

		//not fall to fast
		if (velocity.y >= 350){
			velocity.y = 350;
		}
		//make it so if youre falling y would be positive
		if (velocity.y > 0){
			if (catimation != 3){
				catimation = 3;
				AnimationHandler(catimation, faceRight);
				cat->PlayTypeSet(SpriteAnimation::PlayType(1));
			}
			
		}
		if (velocity.y < 0){
			if (catimation != 2){
				catimation = 2;
				AnimationHandler(catimation, faceRight);
				cat->PlayTypeSet(SpriteAnimation::PlayType(1));
			}
			
			
		}
		break;
	case TRUE:
		//crouching getting ready to jump
		if ((theKeyboard->KeyPressed(KEY_A)) && (theKeyboard->KeyPressed(KEY_SPACE) != TRUE)){
			velocity.x = -100.0f;
			if (faceRight != FALSE){ catimation = 6; }
			faceRight = FALSE;
			moving = TRUE;
		}
		if ((theKeyboard->KeyJustPressed(KEY_D))&& (theKeyboard->KeyPressed(KEY_SPACE) != TRUE)){
			velocity.x = 100.0f;
			
			if (faceRight != TRUE){ catimation = 6; }
			faceRight = TRUE;
			moving = TRUE;
		}

		if ((theKeyboard->KeyPressed(KEY_SPACE))&&(moving == FALSE)){
			if (catimation != 1){
				catimation = 1;
				AnimationHandler(catimation, faceRight);
			}
			
			//DebugPrintf("R: %6d, G: %6d, B: %6d", crouching->ColorGet().red, crouching->ColorGet().green, crouching->ColorGet().blue);
			jumpPower.y -= 10.0f;
			jumpPower.x += 10.0f;
			if (jumpPower.x > 500.0f){
				jumpPower.x = 500.0f;
			}
			//trys to make sure the power doesnt go to high... 20 is def to high but im lazy
			if (jumpPower.y < -1250.0f){
				DebugPrintf("power %7.2lf \n",jumpPower.y);
				jumpPower.y = -1250.0f;
			}
		}
		else
		{
			//makes sure they are set to 0 only once
			if (inAir == TRUE){
				jumpPower.Set(0, 0);
				velocity.Set(0, 0);
				inAir = FALSE;
			}
			//change sprites
			if (catimation != 0){
				//makes it face right or left
				catimation = 0;
				AnimationHandler(catimation, faceRight);
			}
		}
		//once space is released
		if ((theKeyboard->KeyJustReleased(KEY_SPACE)) && (moving == FALSE)){
			DebugPrintf("space unpressed"); 
			if (faceRight == FALSE){
				jumpPower.x *= -1;
			}
			velocity = jumpPower;
			position.y -= .2f;
		}

		//stop movement after key released
		if ((theKeyboard->KeyJustReleased(KEY_A)) || (theKeyboard->KeyJustReleased(KEY_D))){
			velocity.x = 0.0f;
			moving = FALSE;
		}
		//gravity.Set(0.0f, 0.0f);
	}
	//screen stuff
	if ((position.x >= theScreen->SizeGet().x)&&(velocity.x >0)){
		velocity.x *= -1;
	}
	if ((position.x <= 0) && (velocity.x <0)){
		velocity.x *= -1;
	}

//	if (theKeyboard->KeyPressed(KEY_W)){
//		velocity.Set(0, -200);
//		if (theKeyboard->KeyPressed(KEY_D)){
//			velocity.x += 200;
//		}
//		if (theKeyboard->KeyJustPressed(KEY_A)){
//			velocity.x += -200;
	//	}
//	}

}

void Cats::Draw(){
	cat->Draw();
}

void Cats::PositionSet(float x, float y){
	position.Set(x,y);
}

void Cats::VelocitySet(float x, float y){
	x *= -1;
	velocity.Set(x, y);
}

void Cats::AnimationHandler(int catimation, bool faceRight){
	if (faceRight == TRUE){
		switch (catimation)
		{
			//facing right
		case 0:
			cat->AnimationSet("Sprites/Sprites", "Cat");
			
			break;

		case 1:
			cat->AnimationSet("Sprites/Sprites", "Crouch");
			break;

		case 2:
			cat->AnimationSet("Sprites/Sprites", "Jump");
			cat->PlayTypeSet(SpriteAnimation::PlayType(1));
			break;

		case 3:
			cat->AnimationSet("Sprites/Sprites", "Fall");
			cat->PlayTypeSet(SpriteAnimation::PlayType(1));
			break;

		default:
			break;
		}
	}
	//facing left
	else
	{
		switch (catimation)
		{
		case 0:
			cat->AnimationSet("Sprites/Sprites", "CatL");
			
			break;

		case 1:
			
			cat->AnimationSet("Sprites/Sprites", "CrouchL");
			break;

		case 2:
			
			cat->AnimationSet("Sprites/Sprites", "JumpL");
			cat->PlayTypeSet(SpriteAnimation::PlayType(1));
			break;

		case 3:
			cat->AnimationSet("Sprites/Sprites", "FallL");
			cat->PlayTypeSet(SpriteAnimation::PlayType(1));
			break;

		default:
			break;
		}
	}
}

