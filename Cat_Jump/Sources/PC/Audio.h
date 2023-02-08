#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "Frog.h"
#include "MenuState.h"
#include "FrogMath.h"
#include <Array>
#include "Cats.h"

namespace Webfoot{

	class Audio{
	public:
		Audio();
		virtual void Init();
		virtual void Deinit();

		virtual void Update(unsigned int dt, Cats* cat);
	protected:

	};
}

#endif