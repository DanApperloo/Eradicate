#ifndef __EntityDrawable_h_
#define __EntityDrawable_h_

#include <stdafx.h>
#include "GraphicsEngine/GraphicObjects/Drawables/Drawable.h"

// 3d Objects in space
class EntityDrawable : public Drawable
{
	// Public Access
	public:
		EntityDrawable(Ogre::SceneManager* sceneManager, 
					   Ogre::SceneNode* parentNode,
					   Ogre::String name,
					   Ogre::String resourceName);
		~EntityDrawable(void);

	protected:
		Ogre::Entity* mEntity;
		Ogre::String mResourceName;
};
#endif // #ifndef __EntityDrawable_h_