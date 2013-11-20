#ifndef __StaticBackground_h_
#define __StaticBackground_h_

#include <stdafx.h>

class StaticBackground
{
	// Public Access
	public:
		StaticBackground(Ogre::String imageName, Ogre::String attachToModeName);
		~StaticBackground(void);
		// Getters and Setters
		CEGUI::Window* getBackground(void);

	private:
		Ogre::String mImageName;
		Ogre::String mAttachTo;
		CEGUI::Window* mBackground;
		CEGUI::UDim ceguiRealDim(float value);
};
#endif // #ifndef __StaticBackground_h_