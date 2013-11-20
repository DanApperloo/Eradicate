#include <CEGUIUDim.h>
#include "GraphicsEngine/GraphicObjects/Entities/StaticBackground.h"

//---------------------------------------------------------------------
/*
	Default Constructor.
*/
StaticBackground::StaticBackground(Ogre::String imageName, Ogre::String attachToModeName)
{
	mImageName = imageName;
	mAttachTo = attachToModeName;
	mBackground = CEGUI::WindowManager::getSingletonPtr()->createWindow("TaharezLook/StaticImage", mAttachTo + "/backgroundWND");
	mBackground->setPosition(CEGUI::UVector2(ceguiRealDim(0), ceguiRealDim(0)));
	mBackground->setSize(CEGUI::UVector2(ceguiRealDim(1), ceguiRealDim(1)));
	mBackground->setProperty("FrameEnabled", "false");
	mBackground->setProperty("BackgroundEnabled", "false");
	mBackground->setProperty("Image", "set:" + mImageName + " image:full_image");
}
//---------------------------------------------------------------------
/*
	Destructor.
*/
StaticBackground::~StaticBackground(void) {
	//CEGUI::WindowManager::getSingletonPtr()->destroyWindow(mBackground);
}
//---------------------------------------------------------------------
CEGUI::Window* StaticBackground::getBackground(void) {
	return mBackground;
}
//---------------------------------------------------------------------
CEGUI::UDim StaticBackground::ceguiRealDim(float value) {
	return CEGUI::UDim((value), 0);
}
//---------------------------------------------------------------------