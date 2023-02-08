#ifndef _BACKGROUNDBALL_H_
#define _BACKGROUNDBALL_H_

#include "Frog.h"
#include "MenuState.h"

namespace Webfoot {

	class BackgroundBall
	{
	public:
		BackgroundBall();

		/// Initialize the ball
		void Init();
		/// Clean up the ball
		void Deinit();

		/// Make any changes for the given frame.  'dt' is the amount of time that
		/// has passed since the last frame, in milliseconds.
		void Update(unsigned int dt);
		/// Draw the ball.
		void Draw(float cameraX, float cameraY);

	protected:
		/// Appearance of the ball.
		Image* image;
		/// Current position of the ball.
		Point2F position;
	};
}

#endif