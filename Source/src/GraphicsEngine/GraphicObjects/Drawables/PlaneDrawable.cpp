#include <OGRE/OgreMeshManager.h>
#include "GraphicsEngine/GraphicObjects/Drawables/PlaneDrawable.h"

//---------------------------------------------------------------------
/*
	Default Constructor.
*/
PlaneDrawable::PlaneDrawable(Ogre::SceneManager* sceneManager, 
							   Ogre::SceneNode* parentNode,
							   Ogre::String name,
							   Ogre::String resourceName,
							   Ogre::Real width, 
							   Ogre::Real height) 
	: Drawable(sceneManager, parentNode, name)
{
	mResourceName = resourceName;
	Ogre::MeshPtr planePtr = Ogre::MeshManager::getSingleton().createPlane(name + " Mesh", 
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::Plane(Ogre::Vector3::UNIT_Z, 0), 
		width, height, 1, 1, true, 1, 1, 1, Ogre::Vector3::UNIT_Y);
	mPlane = mSceneManager->createEntity(planePtr);
	mPlane->setMaterialName(mResourceName);
	mNode->setScale(1, 1, 1);
	attachObject(mPlane);
	setVisible(false);
}
//---------------------------------------------------------------------
/*
	Destructor.
*/
PlaneDrawable::~PlaneDrawable(void) {
	//mSceneManager->destroyEntity(mEntity);
}
//---------------------------------------------------------------------