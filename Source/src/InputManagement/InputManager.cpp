//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#include "InputManagement/InputManager.h"
#include "QueueManagement\MessageManager.h"
#include "LoggingManagement\LogManager.h"


// Initialize static member variables
ULONG       InputManager::queue_id = 0;


//
///     NAME
//
///     SHORT DESCRIPTION
//
///     Description:
///         LONG DESCRIPTION
///
///     Return
///         VALUE and DESCRIPTION
//
InputManager::InputManager(
    ULONG               queueId,
    Ogre::RenderWindow* window
    )
    : mInputBroker(0),	// Initialize the InputListener pointer to null
      mInputManager(0) // Initialize the OIS::InputManager pointer to null
{
    mWindow = window;
    queue_id = queueId;
    mState = INPUT_MANAGER_INIT;
}


//
///     NAME
//
///     SHORT DESCRIPTION
//
///     Description:
///         LONG DESCRIPTION
///
///     Return
///         VALUE and DESCRIPTION
//
InputManager::~InputManager(void) 
{
    mWindow = 0;

    // Delete InputBroker to destroy InputObjects
    if(mInputBroker)
    {
        delete mInputBroker;
    }

    // Unattach OIS before window shutdown
    if(mInputManager) {
        OIS::InputManager::destroyInputSystem(mInputManager);
        mInputManager = 0;
    }
}


//
///     NAME
//
///     SHORT DESCRIPTION
//
///     Description:
///         LONG DESCRIPTION
///
///     Return
///         VALUE and DESCRIPTION
//
STATUS InputManager::setupInputSystem(void) 
{
    // LOG EVENT USING INTERNAL LOGGING
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
    
    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
    
    mInputManager = OIS::InputManager::createInputSystem(pl);
    
    mInputBroker = new InputBroker(mInputManager);
    
    return STATUS_SUCCESS;
}


//
///     NAME
//
///     SHORT DESCRIPTION
//
///     Description:
///         LONG DESCRIPTION
///
///     Return
///         VALUE and DESCRIPTION
//
STATUS InputManager::captureInput(void)
{
    return mInputBroker->captureInput();
}


//
///     NAME
//
///     SHORT DESCRIPTION
//
///     Description:
///         LONG DESCRIPTION
///
///     Return
///         VALUE and DESCRIPTION
//
STATUS InputManager::setShutdownCallback(
    callback call
    )
{
    return mInputBroker->setShutdownCallback(call);
}


//
///     NAME
//
///     SHORT DESCRIPTION
//
///     Description:
///         LONG DESCRIPTION
///
///     Return
///         VALUE and DESCRIPTION
//
STATUS InputManager::initProcessing(
    InputManagerMessage message
    )
{
    switch(message.major_type)
    {
        case INPUT_ACTIVATE:
            mState = INPUT_MANAGER_ACCEPT;
            return STATUS_SUCCESS;

        default:
            return STATUS_INVALID_MESSAGE;
    }
}


//
///     NAME
//
///     SHORT DESCRIPTION
//
///     Description:
///         LONG DESCRIPTION
///
///     Return
///         VALUE and DESCRIPTION
//
STATUS InputManager::acceptProcessing(
    InputManagerMessage message
    )
{
    switch(message.major_type)
    {
        case INPUT_WINDOW_RESIZED:
            return mInputBroker->setWindowExtents(message.params.window_resized.width, 
                                                  message.params.window_resized.height);
        
        case INPUT_TRANSITION_TO_SHUTDOWN:
            mState = INPUT_MANAGER_SHUTDOWN;
            return STATUS_SUCCESS;
        
        default:
            return STATUS_INVALID_MESSAGE;
    }
}


//
///     NAME
//
///     SHORT DESCRIPTION
//
///     Description:
///         LONG DESCRIPTION
///
///     Return
///         VALUE and DESCRIPTION
//
STATUS InputManager::shutdownProcessing(
    InputManagerMessage message
    )
{
    switch(message.major_type)
    {
        case INPUT_SHUTDOWN:
            return STATUS_SHUTDOWN_SUCCESS;
    
        default:
            return STATUS_INVALID_MESSAGE;
    }
}


//
///     NAME
//
///     SHORT DESCRIPTION
//
///     Description:
///         LONG DESCRIPTION
///
///     Return
///         VALUE and DESCRIPTION
//
void InputManager::threadEntry(
    InputManager* manager
    )
{
    InputManager*                       inputManager = manager;
    MessageManager<InputManagerMessage> messageManager;
    InputManagerMessage                 message;
    STATUS                              status = STATUS_FAILURE;
    
    while(1)
    {
        status = messageManager.getMessage(InputManager::queue_id,
                                           message,
                                           QUEUE_TIMEOUT_DEFAULT);
    
        if(status == STATUS_SUCCESS)
        {
            LogManager::logMessage(MODULE_INPUT_MANAGER,
                                   DEBUG_LEVEL,
                                   NULL,
                                   "Received Message, Major Type: %lu",
                                   message.major_type);
        }
        
        switch(inputManager->mState)
        {
            case INPUT_MANAGER_INIT:
                if(status == STATUS_SUCCESS)
                {
                    status = inputManager->initProcessing(message);
                }
                break;
            
            case INPUT_MANAGER_ACCEPT:
                if(status == STATUS_SUCCESS)
                {
                    status = inputManager->acceptProcessing(message);
                }
                inputManager->captureInput();
                break;
            
            case INPUT_MANAGER_IGNORE:
                break;
            
            case INPUT_MANAGER_SHUTDOWN:
                if(status == STATUS_SUCCESS)
                {
                    status = inputManager->shutdownProcessing(message);
                }
                break;
        
            default:
                break;
        }
        
        if(status == STATUS_SHUTDOWN_SUCCESS)
        {
            break;
        }
    }
    
    LogManager::logMessage(MODULE_INPUT_MANAGER,
                           DEBUG_LEVEL,
                           NULL,
                           "Successfully transitioned to SHUTDOWN");
    
    // Ensure Cleanup
    delete inputManager;
}