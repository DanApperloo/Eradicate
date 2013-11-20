#include "GraphicsEngine/Factories/OverlayPanelFactory.h"

//---------------------------------------------------------------------
/*
	Default Constructor.
*/
OverlayPanelFactory::OverlayPanelFactory()
{
}
//---------------------------------------------------------------------
/*
	Destructor.
*/
OverlayPanelFactory::~OverlayPanelFactory(void) {
}
//---------------------------------------------------------------------
Ogre::OverlayContainer* OverlayPanelFactory::createBasicPanel(Ogre::String name, 
									 Ogre::Vector2 position, 
									 Ogre::Vector2 dimensions,
									 Ogre::GuiMetricsMode gmm,
									 Ogre::String imageName) 
{
	Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(Ogre::OverlayManager::getSingletonPtr()->createOverlayElement("Panel", name));
	panel->setMetricsMode(gmm); // Default is relative sizing: GMM_RELATIVE. Specified is GMM_PIXELS
	panel->setPosition(position[0], position[1]);
	panel->setDimensions(dimensions[0], dimensions[1]);
	panel->setMaterialName(imageName);
	return panel;
}
//-----------------------------------------------------