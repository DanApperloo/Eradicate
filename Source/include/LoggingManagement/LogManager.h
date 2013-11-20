//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef __LogManager_h_
#define __LogManager_h_

// Includes
#include "stdafx.h"
#include "LoggingManagement\LogMessage.h"

using namespace Eradicate;


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
class LogManager
{
    private:
        // Property Members
        static const ULONG                      max_size = MAX_LOGGING_QUEUE_SIZE;      // Buffer max size
    
        // Data Members
        static boost::condition_variable        buffer_not_full;            // Buffer is not full
        static boost::condition_variable        buffer_not_empty;           // Buffer is not empty
        static boost::mutex                     buffer_mutex;               // Buffer is being accessed
        static std::queue<LogMessage>           buffer;                     // Queue (Pass by Value)
    
        FILE*   logFile;
    
        // Methods
        static BOOLEAN predicate();
        void writeMessage(LogMessage message);
        void writeLine(ULONG        level, 
                       ULONG        component, 
                       std::string  message);
    
    public:
        static void threadEntry(LogManager* manager);
    
        LogManager();
        ~LogManager();
    
        static STATUS logMessage(COMPONENT_MODULE component,
                                 LOGGING_LEVEL    level,
                                 ULONG            controlCode,
                                 const char*      format,
                                 ...);
    
        LogMessage  getMessage(void);
    
};
#endif // __LogManager_h_
