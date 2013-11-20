//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef __InputManager_h_
#define __InputManager_h_

// Includes
#include <stdafx.h>
#include "InputManagement/InputManagerFsm.h"
#include "InputManagement/InputManagerMessages.h"
#include "InputManagement/Listeners/InputBroker.h"

// Namespaces
using namespace Eradicate;

class InputManager
{
	// Public Access
	public:
		static void threadEntry(InputManager* manager);

		InputManager(ULONG queueId,
					 Ogre::RenderWindow* window);
		~InputManager(void);
		STATUS setupInputSystem(void);

		// Callbacks
		STATUS setShutdownCallback(callback call);

		// API
		static STATUS postActivate(void);
		static STATUS postTransitionToShutdown(void);
		static STATUS postShutdown(void);

	private:
		// Read-only After Init Members
		static ULONG			queue_id;

		// Local Functions
		STATUS captureInput(void);
		STATUS initProcessing(InputManagerMessage message);
		STATUS acceptProcessing(InputManagerMessage message);
		STATUS shutdownProcessing(InputManagerMessage message);

		// Local Members
		Ogre::RenderWindow*		mWindow;
		InputBroker*			mInputBroker;
		OIS::InputManager*		mInputManager;
		INPUT_MANAGER_STATE		mState;
};
#endif // #ifndef __InputManager_h_