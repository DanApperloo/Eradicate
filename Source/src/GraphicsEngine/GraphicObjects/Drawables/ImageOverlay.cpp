#include "GraphicsEngine/GraphicObjects/Drawables/ImageOverlay.h"

//---------------------------------------------------------------------
/*
	Default Constructor.
*/
ImageOverlay::ImageOverlay()
	: mOverlay(0),
	  mName(Ogre::String()),
	  mPosition(Ogre::Vector2()),
	  mDimensions(Ogre::Vector2()),
	  mImageName(Ogre::String())
{
}
//---------------------------------------------------------------------
/*
	Used Constructor.
*/
ImageOverlay::ImageOverlay(Ogre::OverlayContainer* panel,
					 int zOrder)
{
	mName = panel->getName();
	mOverlay = Ogre::OverlayManager::getSingletonPtr()->create(mName);
	mPosition = Ogre::Vector2(panel->getLeft(), panel->getTop());
	mDimensions = Ogre::Vector2(panel->getWidth(), panel->getHeight());
	mImageName = panel->getMaterialName();
	mOverlay->setZOrder(zOrder);
	mOverlay->add2D(panel);
}
//---------------------------------------------------------------------
/*
	Destructor.
*/
ImageOverlay::~ImageOverlay(void) {
}
//---------------------------------------------------------------------
Ogre::String ImageOverlay::getName() {
	return mName;
}
//---------------------------------------------------------------------
void ImageOverlay::show() {
	mOverlay->show();
}
//---------------------------------------------------------------------
void ImageOverlay::hide() {
	mOverlay->hide();
}
//---------------------------------------------------------------------
void ImageOverlay::setZOrder(int zOrder) {
	mOverlay->setZOrder(zOrder);
}
//---------------------------------------------------------------------
int ImageOverlay::getZOrder() {
	return mOverlay->getZOrder();
}
//---------------------------------------------------------------------