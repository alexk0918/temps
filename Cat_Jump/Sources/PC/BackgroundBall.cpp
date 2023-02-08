#include "BackgroundBall.h"

using namespace Webfoot;

BackgroundBall::BackgroundBall()
{
	// Initialize pointers to NULL for safety.
	image = NULL;
}

//------------------------------------------------------------------------------

void BackgroundBall::Init()
{
	// Load the image of the ball.
	image = theImages->Load("background");

	// Start the ball in the middle of the screen.
	position = Point2F::Create(-500, -500);
}

//------------------------------------------------------------------------------

void BackgroundBall::Deinit()
{
	// Unload the image of the ball.
	if (image)
	{
		theImages->Unload(image);
		image = NULL;
	}
}

//------------------------------------------------------------------------------


void BackgroundBall::Update(unsigned int dt)
{
	position.Set(position.x, position.y);
}


//------------------------------------------------------------------------------

void BackgroundBall::Draw(float cameraX, float cameraY)
{
	image->Draw(Point2F::Create((position.x + cameraX), (position.y + cameraY)));
}