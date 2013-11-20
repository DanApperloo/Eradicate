//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#include "GraphicsEngine/GraphicEngine.h"


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
STATUS GraphicEngine::graphicEngineControlInitProcessing(
    GRAPHIC_ENGINE_CONTROL_MESSAGE message
    )
{
    STATUS status = STATUS_FAILURE;
    
    switch (message.minor_type)
    {
        case GRAPHIC_ENGINE_CONTROL_ACTIVATE:
            status = exampleSetup(); // REMOVE AFTER EXAMPLE
            if(status != STATUS_SUCCESS)
            {
                return status;
            }
            mState = GRAPHIC_ENGINE_ACTIVE;
            return status;
        
        case GRAPHIC_ENGINE_CONTROL_TRANSITION_TO_SHUTDOWN:
            mState = GRAPHIC_ENGINE_SHUTDOWN;
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
STATUS GraphicEngine::graphicEngineControlActiveProcessing(
    GRAPHIC_ENGINE_CONTROL_MESSAGE message
    )
{
    switch (message.minor_type)
    {
        case GRAPHIC_ENGINE_CONTROL_TRANSITION_TO_SHUTDOWN:
            mState = GRAPHIC_ENGINE_SHUTDOWN;
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
STATUS GraphicEngine::graphicEngineControlShutdownProcessing(
    GRAPHIC_ENGINE_CONTROL_MESSAGE message
    )
{
    switch (message.minor_type)
    {
        case GRAPHIC_ENGINE_CONTROL_SHUTDOWN:
            return STATUS_SHUTDOWN_SUCCESS;

        default:
            return STATUS_INVALID_MESSAGE;
    }
}