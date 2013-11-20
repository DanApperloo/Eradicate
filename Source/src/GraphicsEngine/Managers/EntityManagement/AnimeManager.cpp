#include "GraphicsEngine/Managers/EntityManagement/AnimeManager.h"

typedef std::map<Ogre::String, ImageOverlay>::iterator ImageOverlayMapIterator;

//---------------------------------------------------------------------
/*
	Default Constructor.
*/
AnimeManager::AnimeManager()
{
	mOverlayManager = Ogre::OverlayManager::getSingletonPtr();
}
//---------------------------------------------------------------------
/*
	Destructor.
*/
AnimeManager::~AnimeManager(void) {
}
//---------------------------------------------------------------------
void AnimeManager::showAllOverlays() {
	// Iterate over map and show all
	for(ImageOverlayMapIterator iter = mImageOverlayMap.begin(); iter != mImageOverlayMap.end(); iter++) {
		iter->second.show(); // Use show() on the value stored, which is the ImageOverlay*
	} 
}
//---------------------------------------------------------------------
void AnimeManager::hideAllOverlays() {
	// Iterate over map and hide all
	for(ImageOverlayMapIterator iter = mImageOverlayMap.begin(); iter != mImageOverlayMap.end(); iter++) {
		iter->second.hide(); // Use hide() on the value stored, which is the ImageOverlay*
	}
}
//---------------------------------------------------------------------
ImageOverlay* AnimeManager::getOverlayByName(Ogre::String name) {
	return &mImageOverlayMap[name];
}
//---------------------------------------------------------------------
void AnimeManager::showOverlayByName(Ogre::String name) {
	// Find ImageOverlay in stored list, and show it
	mImageOverlayMap[name].show();
}
//---------------------------------------------------------------------
void AnimeManager::hideOverlayByName(Ogre::String name) {
	// Find ImageOverlay in stored list, and hide it
	mImageOverlayMap[name].hide();
}
//---------------------------------------------------------------------
void AnimeManager::setOverlayZOrderByName(Ogre::String name, int zOrder) {
	mImageOverlayMap[name].setZOrder(zOrder);
}
//---------------------------------------------------------------------
void AnimeManager::addOverlay(ImageOverlay imageOverlay) 
{
	// Create a new ImageOverlay element and store it in the keep list
	mImageOverlayMap[imageOverlay.getName()] = imageOverlay;
}
//---------------------------------------------------------------------
void AnimeManager::removeOverlayByName(Ogre::String name) {

}
//---------------------------------------------------------------------
void AnimeManager::removeAllOverlays(Ogre::String name) {

}
//---------------------------------------------------------------------