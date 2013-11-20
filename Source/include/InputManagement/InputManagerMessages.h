//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef __InputManagerMessages_h_
#define __InputManagerMessages_h_

// Includes
#include "stdafx.h"
#include "QueueManagement\Objects\AbstractMessage.h"


//  NAME
//  Explaination
typedef enum _INPUT_MANAGER_MESSAGE_TYPE
{
    INPUT_ACTIVATE = 0,

    INPUT_WINDOW_RESIZED,

    INPUT_TRANSITION_TO_SHUTDOWN,
    INPUT_SHUTDOWN

} INPUT_MANAGER_MESSAGE_TYPE;


//  NAME
//  Explaination
typedef struct _INPUT_WINDOW_RESIZED_PARAMS
{
    int width;
    int height;

} INPUT_WINDOW_RESIZED_PARAMS;


//  NAME
//  Explaination
typedef union _INPUT_MANAGER_MESSAGE_PARAMS
{
    INPUT_WINDOW_RESIZED_PARAMS window_resized;

} INPUT_MANAGER_MESSAGE_PARAMS;


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
class InputManagerMessage : public AbstractMessage
{
    public:
        INPUT_MANAGER_MESSAGE_TYPE      major_type;      // Message type from enumeration
        INPUT_MANAGER_MESSAGE_PARAMS    params;          // Union representing message specific params
        
        ULONG getMajorMessageType()
        {
            return (ULONG) major_type;
        }
};

#endif // #ifndef __InputManagerMessages_h_