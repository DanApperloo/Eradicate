//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#include "SystemManagement\SystemManager.h"


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
STATUS SystemManager::initProcessing(
    SystemManagerMessage message
    )
{
    switch (message.major_type)
    {
        case SYSTEM_ACTIVATE:
            // Send activate to all child managers
            GraphicEngine::postActivate();
            InputManager::postActivate();
            
            mState = SYSTEM_MANAGER_ACTIVE;
            return STATUS_SUCCESS;
    
        case SYSTEM_TRANSITION_TO_SHUTDOWN:
            // Send shutdown transition to all child managers
            GraphicEngine::postTransitionToShutdown();
            InputManager::postTransitionToShutdown();
            
            mState = SYSTEM_MANAGER_SHUTDOWN;
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
STATUS SystemManager::activeProcessing(
    SystemManagerMessage message
    )
{
    switch (message.major_type)
    {
        case SYSTEM_TRANSITION_TO_SHUTDOWN:
            // Send shutdown transition to all child managers
            GraphicEngine::postTransitionToShutdown();
            InputManager::postTransitionToShutdown();
    
            mState = SYSTEM_MANAGER_SHUTDOWN;
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
STATUS SystemManager::shutdownProcessing(
    SystemManagerMessage message
    )
{
    switch (message.major_type)
    {
        case SYSTEM_SHUTDOWN:
            // Send shutdown to all child managers
            GraphicEngine::postShutdown();
            InputManager::postShutdown();
        
            return STATUS_SHUTDOWN_SUCCESS;
        
        default:
            return STATUS_INVALID_MESSAGE;
    }
}