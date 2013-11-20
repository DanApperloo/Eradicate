//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#include "InputManagement/InputManager.h"
#include "QueueManagement\MessageManager.h"


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
STATUS InputManager::postActivate()
{
    InputManagerMessage message;
    MessageManager<InputManagerMessage> messageManager;
    
    message.major_type = INPUT_ACTIVATE;
    messageManager.postMessage(InputManager::queue_id, 
                               message, 
                               QUEUE_TIMEOUT_INFINITE);
    
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
STATUS InputManager::postTransitionToShutdown()
{
    InputManagerMessage message;
    MessageManager<InputManagerMessage> messageManager;
    
    message.major_type = INPUT_TRANSITION_TO_SHUTDOWN;
    messageManager.postMessage(InputManager::queue_id, 
                               message, 
                               QUEUE_TIMEOUT_INFINITE);
    
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
STATUS InputManager::postShutdown()
{
    InputManagerMessage message;
    MessageManager<InputManagerMessage> messageManager;
    
    message.major_type = INPUT_SHUTDOWN;
    messageManager.postMessage(InputManager::queue_id,
                               message, 
                               QUEUE_TIMEOUT_INFINITE);
    
    return STATUS_SUCCESS;
}