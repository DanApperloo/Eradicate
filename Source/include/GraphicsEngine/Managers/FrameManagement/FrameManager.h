#ifndef __FrameManager_h_
#define __FrameManager_h_

#include <stdafx.h>

class FrameManager : public Ogre::FrameListener
{
	// Public Access
	public:
		FrameManager(Ogre::RenderWindow* window);
		~FrameManager(void);
		bool initialize();
		// Ogre::FrameListener Functions
		virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	private:
		Ogre::RenderWindow* mWindow;
};
#endif // #ifndef __FrameManager_h_