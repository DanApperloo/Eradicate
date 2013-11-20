#ifndef __AnimeManager_h_
#define __AnimeManager_h_

#include <stdafx.h>
#include <map>
#include <OgreOverlayManager.h>
#include "GraphicsEngine/GraphicObjects/Drawables/ImageOverlay.h"

class AnimeManager
{
	// Public Access
	public:
		AnimeManager();
		~AnimeManager(void);
		ImageOverlay* getOverlayByName(Ogre::String name);
		void showAllOverlays();
		void hideAllOverlays();
		void showOverlayByName(Ogre::String name);
		void hideOverlayByName(Ogre::String name);
		void setOverlayZOrderByName(Ogre::String name, int zOrder);
		void addOverlay(ImageOverlay imageOverlay);
		void removeOverlayByName(Ogre::String name);
		void removeAllOverlays(Ogre::String name);
		/* Required functions: 
							   get ImageOverlays at specified z level
							   set ImageOverlay z level by name
		*/

	private:
		Ogre::OverlayManager* mOverlayManager;
		std::map<Ogre::String, ImageOverlay> mImageOverlayMap;

};
#endif // #ifndef __AnimeManager_h_