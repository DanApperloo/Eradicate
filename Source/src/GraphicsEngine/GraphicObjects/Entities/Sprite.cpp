#include <stdio.h> 
#include <OgreSubEntity.h>
#include "GraphicsEngine/GraphicObjects/Entities/Sprite.h"

//---------------------------------------------------------------------
/*
	Default Constructor.
*/
Sprite::Sprite(Ogre::SceneManager* sceneManager, 
				   Ogre::SceneNode* parentNode,
			       Ogre::String name,
			       Ogre::String resourceName,
				   Ogre::Real width,
				   Ogre::Real height,
				   Ogre::Vector2 vPosition,
				   int level) 
	: PlaneDrawable(sceneManager, parentNode, name, resourceName, width, height)
{
	setPosition(Ogre::Vector3(vPosition[0], vPosition[1], Ogre::Real(level)));
}
//---------------------------------------------------------------------
/*
	Destructor.d
*/
Sprite::~Sprite(void) {
}
//---------------------------------------------------------------------
Ogre::Real Sprite::setLevel(int level) {
	Ogre::Vector3 oldPosition = getPosition();
	setPosition(Ogre::Vector3(oldPosition[0], oldPosition[1], Ogre::Real(level)));
	return getPosition()[2];
}
//---------------------------------------------------------------------