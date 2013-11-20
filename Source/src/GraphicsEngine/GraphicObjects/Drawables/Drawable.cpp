#include "GraphicsEngine/GraphicObjects/Drawables/Drawable.h"

//---------------------------------------------------------------------
/*
	Default Constructor.
*/
Drawable::Drawable(Ogre::SceneManager* sceneManager, 
				   Ogre::SceneNode* parentNode,
				   Ogre::String name)
{
	mSceneManager = sceneManager;
	mParentNode = parentNode;
	mName = name;
	mNode = mParentNode->createChildSceneNode(mName);
	setPosition(Ogre::Vector3(0,0,0));
}
//---------------------------------------------------------------------
/*
	Destructor.
*/
Drawable::~Drawable(void) {
//	mSceneManager->destroySceneNode(mNode);
}
//---------------------------------------------------------------------
// Ogre::SceneNode Functions
bool Drawable::attachObject(Ogre::MovableObject* attach) {
	mNode->attachObject(attach);
	return true;
}
//---------------------------------------------------------------------
// Getters and setters
void Drawable::setPosition(Ogre::Vector3 position) {
	mNode->setPosition(position);
}
//---------------------------------------------------------------------
Ogre::Vector3 Drawable::getPosition() {
	return mNode->getPosition();
}
//---------------------------------------------------------------------
Ogre::SceneNode* Drawable::getNode() {
	return mNode;
}
//---------------------------------------------------------------------
Ogre::SceneNode* Drawable::getParentNode() {
	return mParentNode;
}
//---------------------------------------------------------------------
Ogre::String Drawable::getName() {
	return mName;
}
//---------------------------------------------------------------------
bool Drawable::isVisible() {
	return mNode->getAttachedObject(0)->isVisible();
}
//---------------------------------------------------------------------
void Drawable::setVisible(bool visible) {
	mNode->setVisible(visible);
}
//---------------------------------------------------------------------
void Drawable::show(void) {
	if(!isVisible()) setVisible(true);
}
//---------------------------------------------------------------------
void Drawable::hide(void) {
	if(isVisible()) setVisible(false);
}
//---------------------------------------------------------------------