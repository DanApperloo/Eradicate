#include "GraphicsEngine/Managers/FrameManagement/FrameManager.h"

//---------------------------------------------------------------------
FrameManager::FrameManager(Ogre::RenderWindow* window)
{
	mWindow = window;
	// Register as a Ogre::FrameListener
	Ogre::Root::getSingletonPtr()->addFrameListener(this);
}
//---------------------------------------------------------------------
/*
	Destructor.
*/
FrameManager::~FrameManager(void) {
	Ogre::Root::getSingletonPtr()->removeFrameListener(this);
}
//---------------------------------------------------------------------
bool FrameManager::frameRenderingQueued(const Ogre::FrameEvent& evt) {
    return true;
}
//---------------------------------------------------------------------