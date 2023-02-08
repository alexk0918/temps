#ifndef __GROUNDTILES_H__
#define __GROUNDTILES_H__

#include "Frog.h"
#include "MenuState.h"
#include "FrogMath.h"
#include <Array>

namespace Webfoot{
	class Tiles{
	public:
		Tiles();

		virtual void Init(int tile);
		virtual void Deinit();

		virtual void Update();
		virtual void Draw();

	protected:

		Image* tileImage;

		Point2F position;
	};
}


#endif