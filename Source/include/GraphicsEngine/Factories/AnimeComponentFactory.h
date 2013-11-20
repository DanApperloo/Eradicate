#ifndef __AnimeComponentFactory_h_
#define __AnimeComponentFactory_h_

#include <stdafx.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>
#include <OgreFontManager.h>
#include <OgreTextAreaOverlayElement.h>
#include "GraphicsEngine/GraphicObjects/Drawables/ImageOverlay.h"

class AnimeComponentFactory
{
	// Public Access
	public:
		AnimeComponentFactory();
		~AnimeComponentFactory(void);
		ImageOverlay createTestImage(Ogre::String name, 
									 Ogre::Vector2 position, 
									 Ogre::Vector2 dimensions,
									 int zOrder,
									 Ogre::GuiMetricsMode gmm,
									 Ogre::String imageName);
};
#endif // #ifndef __AnimeComponentFactory_h_