#include "GraphicsEngine/Factories/AnimeComponentFactory.h"
#include "GraphicsEngine/Factories/OverlayPanelFactory.h"

//---------------------------------------------------------------------
/*
	Default Constructor.
*/
AnimeComponentFactory::AnimeComponentFactory()
{
}
//---------------------------------------------------------------------
/*
	Destructor.
*/
AnimeComponentFactory::~AnimeComponentFactory(void) {
}
//---------------------------------------------------------------------
ImageOverlay AnimeComponentFactory::createTestImage(Ogre::String name, 
									 Ogre::Vector2 position, 
									 Ogre::Vector2 dimensions,
									 int zOrder,
									 Ogre::GuiMetricsMode gmm,
									 Ogre::String imageName) 
{
	Ogre::OverlayContainer* panel = OverlayPanelFactory().createBasicPanel(name, position, dimensions, gmm, imageName);
	return ImageOverlay(panel, zOrder);
}
//-----------------------------------------------------