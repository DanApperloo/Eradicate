#ifndef __Sprite_h_
#define __Sprite_h_

#include <stdafx.h>
#include "GraphicsEngine/GraphicObjects/Drawables/PlaneDrawable.h"

class Sprite : public PlaneDrawable
{
	// Public Access
	public:
		Sprite(Ogre::SceneManager* sceneManager, 
				 Ogre::SceneNode* parentNode,
			     Ogre::String name,
			     Ogre::String resourceName,
				 Ogre::Real width,
				 Ogre::Real height,
				 Ogre::Vector2 vPosition,
				 int level);
		~Sprite(void);
		Ogre::Real setLevel(int level);
};
#endif // #ifndef __Sprite_h_