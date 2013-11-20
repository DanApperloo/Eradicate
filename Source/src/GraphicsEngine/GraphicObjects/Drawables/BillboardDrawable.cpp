#include "GraphicsEngine/GraphicObjects/Drawables/BillboardDrawable.h"

//---------------------------------------------------------------------
/*
	Default Constructor.
*/
BillboardDrawable::BillboardDrawable(Ogre::SceneManager* sceneManager, 
							   Ogre::SceneNode* parentNode,
							   Ogre::String name,
							   Ogre::String resourceName,
							   Ogre::Vector3 position) 
	: Drawable(sceneManager, parentNode, name)
{
	mResourceName = resourceName;
	mBillboardSet = mSceneManager->createBillboardSet(1);
	mBillboard = mBillboardSet->createBillboard(position);
	mBillboardSet->setBillboardType(Ogre::BillboardType::BBT_POINT);
	mBillboardSet->setBillboardOrigin(Ogre::BillboardOrigin::BBO_BOTTOM_CENTER);
	mBillboardSet->setCastShadows(false);
	mBillboardSet->setDefaultDimensions(2.5, 2.5);
	mBillboardSet->setMaterialName("Examples/OgreParade");
	attachObject(mBillboardSet);
	setVisible(false);
}
//---------------------------------------------------------------------
/*
	Destructor.
*/
BillboardDrawable::~BillboardDrawable(void) {
	//mSceneManager->destroyEntity(mEntity);
}
//---------------------------------------------------------------------