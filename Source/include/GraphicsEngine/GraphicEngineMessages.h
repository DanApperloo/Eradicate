//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef __GraphicEngineMessages_h_
#define __GraphicEngineMessages_h_

// Includes
#include "stdafx.h"
#include "QueueManagement\Objects\AbstractMessage.h"

using namespace Eradicate;


//  NAME
//  Explaination
typedef enum _GRAPHIC_ENGINE_CONTROL_MESSAGE_TYPE
{
    GRAPHIC_ENGINE_CONTROL_ACTIVATE = 0,
    
    GRAPHIC_ENGINE_CONTROL_TRANSITION_TO_SHUTDOWN,
    GRAPHIC_ENGINE_CONTROL_SHUTDOWN

} GRAPHIC_ENGINE_CONTROL_MESSAGE_TYPE;


//  NAME
//  Explaination
typedef struct _GRAPHIC_ENGINE_CONTROL_MESSAGE_TRANSITION_TO_SHUTDOWN_PARAMS
{
    STATUS  exit_status;

} GRAPHIC_ENGINE_CONTROL_MESSAGE_TRANSITION_TO_SHUTDOWN_PARAMS;


//  NAME
//  Explaination
typedef union _GRAPHIC_ENGINE_CONTROL_MESSAGE_PARAMS
{
    GRAPHIC_ENGINE_CONTROL_MESSAGE_TRANSITION_TO_SHUTDOWN_PARAMS transition_params;

} GRAPHIC_ENGINE_CONTROL_MESSAGE_PARAMS;


//  NAME
//  Explaination
typedef struct _GRAPHIC_ENGINE_CONTROL_MESSAGE
{
    GRAPHIC_ENGINE_CONTROL_MESSAGE_TYPE		minor_type;
    GRAPHIC_ENGINE_CONTROL_MESSAGE_PARAMS	minor_params;

} GRAPHIC_ENGINE_CONTROL_MESSAGE;


//  NAME
//  Explaination
typedef union _GRAPHIC_ENGINE_MINOR_MESSAGES
{
    GRAPHIC_ENGINE_CONTROL_MESSAGE      control_message;

} GRAPHIC_ENGINE_MINOR_MESSAGES;


//  NAME
//  Explaination
typedef enum _GRAPHIC_ENGINE_MAJOR_MESSAGE_TYPE
{
    GRAPHIC_ENGINE_CONTROL = 0,

} GRAPHIC_ENGINE_MAJOR_MESSAGE_TYPE;


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
class GraphicEngineMessage : public AbstractMessage
{
    public:
        GRAPHIC_ENGINE_MAJOR_MESSAGE_TYPE       major_type;      // Message type from enumeration
        GRAPHIC_ENGINE_MINOR_MESSAGES           minor_msg;       // Union representing message specific params
        
        ULONG getMajorMessageType()
        {
            return (ULONG) major_type;
        }
};

#endif // #ifndef __GraphicEngineMessages_h_