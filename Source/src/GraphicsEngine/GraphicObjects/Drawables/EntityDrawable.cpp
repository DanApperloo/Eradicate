#include "GraphicsEngine/GraphicObjects/Drawables/EntityDrawable.h"

//---------------------------------------------------------------------
/*
	Default Constructor.
*/
EntityDrawable::EntityDrawable(Ogre::SceneManager* sceneManager, 
							   Ogre::SceneNode* parentNode,
							   Ogre::String name,
							   Ogre::String resourceName) 
	: Drawable(sceneManager, parentNode, name)
{
	mResourceName = resourceName;
	mEntity = mSceneManager->createEntity(name + " Entity", resourceName);
	attachObject(mEntity);
	setVisible(false);
}
//---------------------------------------------------------------------
/*
	Destructor.
*/
EntityDrawable::~EntityDrawable(void) {
	//mSceneManager->destroyEntity(mEntity);
}
//---------------------------------------------------------------------