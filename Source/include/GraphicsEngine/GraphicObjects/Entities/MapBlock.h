#ifndef __MapBlock_h_
#define __MapBlock_h_

#include <stdafx.h>
#include "GraphicsEngine/GraphicObjects/Drawables/EntityDrawable.h"

class MapBlock : public EntityDrawable
{
	// Public Access
	public:
		MapBlock(Ogre::SceneManager* sceneManager, 
				 Ogre::SceneNode* parentNode,
			     Ogre::String name,
			     Ogre::String resourceName,
				 Ogre::Vector3 vPosition,
				 Ogre::Vector3 sPosition);
		~MapBlock(void);
		// Getters and Setters
		Ogre::Vector3 getStaticPosition(void);

	protected:
		Ogre::Vector3 mStaticPosition;
		std::list<Ogre::MaterialPtr> mWorkingMaterials;

	private:
		std::list<Ogre::MaterialPtr> cloneMaterials();
};
#endif // #ifndef __MapBlock_h_