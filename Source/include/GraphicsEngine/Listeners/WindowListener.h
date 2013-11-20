//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef __WindowListener_h_
#define __WindowListener_h_

// Includes
#include <stdafx.h>

// Namespaces
using namespace Eradicate;

class WindowListener : public Ogre::WindowEventListener 
{
	// Public Access
	public:
		WindowListener(Ogre::RenderWindow* window);
		~WindowListener(void);
		STATUS initialize();

	private:
		// Methods
		// Shutdown Ogre::WindowEventListener Functions
		virtual void windowResized(Ogre::RenderWindow* rw);
		virtual void windowClosed(Ogre::RenderWindow* rw);

		// Members
		Ogre::RenderWindow*		mWindow;
};
#endif // #ifndef __WindowListener_h_