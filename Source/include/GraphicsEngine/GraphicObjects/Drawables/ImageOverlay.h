#ifndef __ImageOverlay_h_
#define __ImageOverlay_h_

#include <stdafx.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>
#include <OgreFontManager.h>
#include <OgreTextAreaOverlayElement.h>

class ImageOverlay
{
	// Public Access
	public:
		ImageOverlay();
		ImageOverlay(Ogre::OverlayContainer* panel,
					 int zOrder);
		~ImageOverlay(void);
		Ogre::String getName();
		void show();
		void hide();
		void setZOrder(int zOrder);
		int getZOrder();

	private:
		Ogre::String mName;
		Ogre::Vector2 mPosition;
		Ogre::Vector2 mDimensions;
		Ogre::String mImageName;
		Ogre::Overlay* mOverlay;

};
#endif // #ifndef __ImageOverlay_h_