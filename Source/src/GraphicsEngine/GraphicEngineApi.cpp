//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#include "GraphicsEngine/GraphicEngine.h"
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
STATUS GraphicEngine::postActivate()
{
    GraphicEngineMessage message;
    MessageManager<GraphicEngineMessage> messageManager;
    
    message.major_type = GRAPHIC_ENGINE_CONTROL;
    message.minor_msg.control_message.minor_type = GRAPHIC_ENGINE_CONTROL_ACTIVATE;
    
    messageManager.postMessage(GraphicEngine::queue_id, 
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
STATUS GraphicEngine::postTransitionToShutdown()
{
    GraphicEngineMessage message;
    MessageManager<GraphicEngineMessage> messageManager;
    
    message.major_type = GRAPHIC_ENGINE_CONTROL;
    message.minor_msg.control_message.minor_type = GRAPHIC_ENGINE_CONTROL_TRANSITION_TO_SHUTDOWN;
    messageManager.postMessage(GraphicEngine::queue_id, 
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
STATUS GraphicEngine::postShutdown()
{
    GraphicEngineMessage message;
    MessageManager<GraphicEngineMessage> messageManager;
    
    message.major_type = GRAPHIC_ENGINE_CONTROL;
    message.minor_msg.control_message.minor_type = GRAPHIC_ENGINE_CONTROL_SHUTDOWN;
    messageManager.postMessage(GraphicEngine::queue_id, 
                               message, 
                               QUEUE_TIMEOUT_INFINITE);
    
    return STATUS_SUCCESS;
}