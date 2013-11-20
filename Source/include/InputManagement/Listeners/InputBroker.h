//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef __InputBroker_h_
#define __InputBroker_h_

// Includes
#include <stdafx.h>

// Namespaces
using namespace Eradicate;

class InputBroker : public OIS::KeyListener, public OIS::MouseListener 
{
	// Public Access
	public:
		InputBroker(OIS::InputManager* inputManager);
		~InputBroker(void);

		// Gather input
		STATUS captureInput();

		// Callbacks
		STATUS setShutdownCallback(callback call);

		// Ogre Windows Calls
		STATUS setWindowExtents(int width, int height);
		// OIS::KeyListener
		virtual bool keyPressed(const OIS::KeyEvent& evt);
		virtual bool keyReleased(const OIS::KeyEvent& evt);
		// OIS::MouseListener
		virtual bool mouseMoved(const OIS::MouseEvent& evt);
		virtual bool mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
		virtual bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id);

	private:
		callback				triggerShutdown;
		OIS::Mouse*				mMouse;
		OIS::Keyboard*			mKeyboard;
		CEGUI::System*			mCEGUISystem;
		OIS::InputManager*		mInputManager;
};
#endif // #ifndef __InputBroker_h_