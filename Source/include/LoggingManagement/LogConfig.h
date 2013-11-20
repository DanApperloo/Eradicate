//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef __LogConfig_h_
#define __LogConfig_h_

#define MAXIMUM_MESSAGE_SIZE    256
#define MAX_LOGGING_QUEUE_SIZE  100
#define LOG_OUTPUT_FILE         "Excalibur_log.txt"

//  NAME
//  Explaination
typedef enum LOGGING_LEVEL
{
    ERROR_LEVEL = 0,
    WARNING_LEVEL,
    INFO_LEVEL,
    DEBUG_LEVEL

};


//  NAME
//  Explaination
static char* logging_level_string_lut[] = 
{
    "  Error",
    "Warning",
    "   Info",
    "  Debug"

};


//  NAME
//  Explaination
typedef enum COMPONENT_MODULE
{
    MODULE_SYSTEM_MANAGER = 0,
    MODULE_INPUT_MANAGER,
    MODULE_GRAPHIC_ENGINE

};


//  NAME
//  Explaination
static char* logging_component_string_lut[] =
{
    "System_Manager",
    " Input_Manager",
    "Graphic_Engine"

};


//  NAME
//  Explaination
static LOGGING_LEVEL logging_component_level_lut[] = 
{
    DEBUG_LEVEL,      // MODULE_SYSTEM_MANAGER
    DEBUG_LEVEL,      // MODULE_INPUT_MANAGER
    DEBUG_LEVEL       // MODULE_GRAPHIC_ENGINE

};

#endif // __LogConfig_h_