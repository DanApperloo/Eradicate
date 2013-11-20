#ifndef __PlaneDrawable_h_
#define __PlaneDrawable_h_

#include <stdafx.h>
#include "GraphicsEngine/GraphicObjects/Drawables/Drawable.h"


// 2d Objects in space
class PlaneDrawable : public Drawable
{
	// Public Access
	public:
		PlaneDrawable(Ogre::SceneManager* sceneManager, 
					   Ogre::SceneNode* parentNode,
					   Ogre::String name,
					   Ogre::String resourceName,
					   Ogre::Real width,
					   Ogre::Real height);
		~PlaneDrawable(void);

	protected:
		Ogre::Entity* mPlane;
		Ogre::String mResourceName;
};
#endif // #ifndef __PlaneDrawable_h_