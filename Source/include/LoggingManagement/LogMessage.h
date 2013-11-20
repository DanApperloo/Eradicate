//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef __LogMessage_h_
#define __LogMessage_h_

// Includes
#include "stdafx.h"
#include "LoggingManagement\LogConfig.h"
#include <string>

using namespace Eradicate;

//  NAME
//  Explaination
typedef enum LOG_MESSAGE_CONTROL_CODE
{
    SHUTDOWN_LOG_MANAGER = 1

};


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
class LogMessage
{
    public:
        COMPONENT_MODULE component;
        LOGGING_LEVEL    level;
        std::string      data;
        ULONG            controlCode;
};
#endif // __LogMessage_h_
