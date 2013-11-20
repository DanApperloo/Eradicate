#ifndef __BillboardDrawable_h_
#define __BillboardDrawable_h_

#include <stdafx.h>
#include <OGRE/OgreBillboardSet.h>
#include <OGRE/OgreBillboard.h>
#include "GraphicsEngine/GraphicObjects/Drawables/Drawable.h"

// Used for Animations and images that are placed in space, but always face the screen
class BillboardDrawable : public Drawable
{
	// Public Access
	public:
		BillboardDrawable(Ogre::SceneManager* sceneManager, 
					   Ogre::SceneNode* parentNode,
					   Ogre::String name,
					   Ogre::String resourceName,
					   Ogre::Vector3 position);
		~BillboardDrawable(void);

	protected:
		Ogre::BillboardSet* mBillboardSet;
		Ogre::Billboard* mBillboard;
		Ogre::String mResourceName;
};
#endif // #ifndef __BillboardDrawable_h_