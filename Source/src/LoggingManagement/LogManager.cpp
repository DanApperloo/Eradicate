//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
// Includes
#include "LoggingManagement\LogManager.h"
#include <iostream>

boost::condition_variable       LogManager::buffer_not_full;
boost::condition_variable       LogManager::buffer_not_empty;
boost::mutex                    LogManager::buffer_mutex;
std::queue<LogMessage>          LogManager::buffer;


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
LogManager::LogManager()
{
    // Delete Previous log
    fopen_s(&logFile, LOG_OUTPUT_FILE, "w");

    // Flush buffer and release file
    fclose(logFile);
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
LogManager::~LogManager()
{
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
BOOLEAN LogManager::predicate()
{
    return buffer.size() != max_size;
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
void LogManager::writeLine(
    ULONG       level,
    ULONG       component,
    std::string message
    )
{
    boost::posix_time::millisec_posix_time_system_config::time_duration_type 
        now = boost::posix_time::second_clock::local_time().time_of_day();

    fprintf(logFile, 
            "(%02u:%02u:%02u) %s - %s:  %s \n",
            now.hours(), now.minutes(), now.seconds(),
            logging_level_string_lut[level], 
            logging_component_string_lut[component], 
            message.c_str());
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
void LogManager::writeMessage(LogMessage message)
{
    fopen_s(&logFile, LOG_OUTPUT_FILE, "a");
    
    writeLine(message.level,
              message.component,
              message.data);

    fflush(logFile);
    fclose(logFile);
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
STATUS LogManager::logMessage(
    COMPONENT_MODULE component,
    LOGGING_LEVEL    level,
    ULONG            controlCode,
    const char*      format,
    ...
    )
{
    LogMessage  logMessage;
    char        formatted[MAXIMUM_MESSAGE_SIZE];
    va_list     argptr;

    // If the logging level is set 
    if(level <= logging_component_level_lut[component])
    {
    
        va_start(argptr, format);
        vsnprintf_s(formatted, MAXIMUM_MESSAGE_SIZE, format, argptr);
        va_end(argptr);
        
        logMessage.component   = component;
        logMessage.level       = level;
        logMessage.data        = std::string(formatted);
        logMessage.controlCode = controlCode;
        
        boost::unique_lock<boost::mutex> mlock(buffer_mutex);
        if(buffer.size() == max_size)
        {
            buffer_not_full.wait(mlock, LogManager::predicate);
        }
        buffer.push(logMessage);
        buffer_not_empty.notify_one();

    }
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
LogMessage LogManager::getMessage(void)
{
    LogMessage message;
    
    boost::unique_lock<boost::mutex> mlock(buffer_mutex);
    if(buffer.empty())
    {
        buffer_not_empty.wait(mlock, [this](){return !buffer.empty();});
    }
    message = buffer.front();
    buffer.pop();
    buffer_not_full.notify_one();
    return message;
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
void LogManager::threadEntry(
    LogManager* manager
    )
{
    LogManager*     logManager = manager;
    LogMessage      message;
    STATUS          status = STATUS_FAILURE;
    
    while(1)
    {
        // Get message is no timeout queue call
        message = logManager->getMessage();
        logManager->writeMessage(message);
        
        if(message.controlCode != NULL)
        {
            // Manager Control message
            switch(message.controlCode)
            {
                case SHUTDOWN_LOG_MANAGER:
                    status = STATUS_SHUTDOWN_SUCCESS;
                    break;
            
                default:
                    break;
            }
        }
        
        if(status == STATUS_SHUTDOWN_SUCCESS)
        {
            break;
        }
    }
    
    // Ensure Cleanup
    delete logManager;
}
