//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef __SystemManagerMessages_h_
#define __SystemManagerMessages_h_

// Includes
#include "stdafx.h"
#include "QueueManagement\Objects\AbstractMessage.h"


//  NAME
//  Explaination
typedef enum _SYSTEM_MANAGER_MESSAGE_TYPE
{
    SYSTEM_ACTIVATE = 0,

    SYSTEM_TRANSITION_TO_SHUTDOWN,
    SYSTEM_SHUTDOWN

} SYSTEM_MANAGER_MESSAGE_TYPE;


//  NAME
//  Explaination
typedef struct _SYSTEM_MANAGER_PLACEHOLDER_PARAMS
{
    int placeholder;

} SYSTEM_MANAGER_PLACEHOLDER_PARAMS;


//  NAME
//  Explaination
typedef union _SYSTEM_MANAGER_MESSAGE_PARAMS
{
    SYSTEM_MANAGER_PLACEHOLDER_PARAMS placeholder;

} SYSTEM_MANAGER_MESSAGE_PARAMS;


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
class SystemManagerMessage : public AbstractMessage
{
    public:
        SYSTEM_MANAGER_MESSAGE_TYPE     major_type;      // Message type from enumeration
        SYSTEM_MANAGER_MESSAGE_PARAMS   params;         // Union representing message specific params
        
        ULONG getMajorMessageType()
        {
            return (ULONG) major_type;
        }
};

#endif // #ifndef __SystemManagerMessages_h_