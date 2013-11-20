#ifndef __OverlayPanelFactory_h_
#define __OverlayPanelFactory_h_

#include <stdafx.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>
#include <OgreFontManager.h>
#include <OgreTextAreaOverlayElement.h>

class OverlayPanelFactory
{
	// Public Access
	public:
		OverlayPanelFactory();
		~OverlayPanelFactory(void);
		Ogre::OverlayContainer* createBasicPanel(Ogre::String name, 
									 Ogre::Vector2 position, 
									 Ogre::Vector2 dimensions,
									 Ogre::GuiMetricsMode gmm,
									 Ogre::String imageName);
};
#endif // #ifndef __OverlayPanelFactory_h_