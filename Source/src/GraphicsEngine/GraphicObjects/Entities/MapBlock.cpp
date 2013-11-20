#include <stdio.h> 
#include <OgreSubEntity.h>
#include "GraphicsEngine/GraphicObjects/Entities/MapBlock.h"

//---------------------------------------------------------------------
/*
	Default Constructor.
*/
MapBlock::MapBlock(Ogre::SceneManager* sceneManager, 
				   Ogre::SceneNode* parentNode,
			       Ogre::String name,
			       Ogre::String resourceName,
				   Ogre::Vector3 vPosition,
				   Ogre::Vector3 sPosition) 
	: EntityDrawable(sceneManager, parentNode, name, resourceName)
{
	mStaticPosition = sPosition;
	setPosition(vPosition);
	mWorkingMaterials = cloneMaterials();
}
//---------------------------------------------------------------------
/*
	Destructor.
*/
MapBlock::~MapBlock(void) {
}
//---------------------------------------------------------------------
Ogre::Vector3 MapBlock::getStaticPosition(void) {
	return mStaticPosition;
}
//---------------------------------------------------------------------
std::list<Ogre::MaterialPtr> MapBlock::cloneMaterials(void) {
	std::list<Ogre::MaterialPtr> clones;
	for(unsigned int i=0; i < mEntity->getNumSubEntities(); i++) {
		Ogre::MaterialPtr realMaterial = mEntity->getSubEntity(i)->getMaterial();
		std::stringstream nameStream;
		nameStream << realMaterial->getName() << " " << mStaticPosition[0] << ":" << mStaticPosition[1];
		Ogre::MaterialPtr newMaterial = realMaterial->clone(nameStream.str());
		newMaterial->load();
		mEntity->getSubEntity(i)->setMaterial(newMaterial);
		clones.push_back(newMaterial);
	}
	return clones;
}
//---------------------------------------------------------------------