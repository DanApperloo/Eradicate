#ifndef __Drawable_h_
#define __Drawable_h_

#include <stdafx.h>

class Drawable
{
	// Public Access
	public:
		Drawable(Ogre::SceneManager* sceneManager, 
				 Ogre::SceneNode* parentNode,
				 Ogre::String name);
		~Drawable(void);
		// Ogre::SceneNode Functions
		bool attachObject(Ogre::MovableObject* attach);
		// Getters and setters
		void setPosition(Ogre::Vector3 position);
		Ogre::Vector3 getPosition();
		Ogre::SceneNode* getNode();
		Ogre::SceneNode* getParentNode();
		Ogre::String getName();
		bool isVisible();
		void setVisible(bool visible);
		void show(void);
		void hide(void);

	protected:
		Ogre::SceneManager* mSceneManager;
		Ogre::SceneNode* mParentNode;
		Ogre::SceneNode* mNode;
		Ogre::String mName;
};
#endif // #ifndef __Drawable_h_