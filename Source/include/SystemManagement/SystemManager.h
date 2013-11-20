//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef __SystemManager_h_
#define __SystemManager_h_

// Includes
#include <stdafx.h>
#include "SystemManagement\SystemManagerMessages.h"
#include "SystemManagement\SystemManagerFsm.h"
#include "GraphicsEngine/GraphicEngine.h"
#include "InputManagement/InputManager.h"

// Namespaces
using namespace Eradicate;

class SystemManager
{
	// Public Access
	public:
		SystemManager(void);
		~SystemManager(void);
		
		STATUS initializeManagers(void);
		STATUS systemLoop(void);
		STATUS initializeLogManager(void);
		STATUS shutdownLogManager(void);

		// Callbacks
		static STATUS triggerShutdown(void);

	private:
		// Read-only After Init Members
		static ULONG			queue_id;

		// Methods
		STATUS initializeGameEngine(void);
		STATUS initializeGraphicsEngine(void);
		STATUS initializeInputManager(void);

		STATUS initProcessing(SystemManagerMessage message);
		STATUS activeProcessing(SystemManagerMessage message);
		STATUS shutdownProcessing(SystemManagerMessage message);

		// Members
		SYSTEM_MANAGER_STATE	mState;
		Ogre::RenderWindow*		mWindow;
		boost::thread_group     mThreadGroup;
		boost::thread*			mLoggingThread;
};
#endif // #ifndef __SystemManager_h_