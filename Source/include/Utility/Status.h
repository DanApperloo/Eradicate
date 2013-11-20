//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef __Status_h_
#define __Status_h_

// Namespace Declaration -- Avoids Status declaration collisions
namespace Eradicate
{

// Status Error Base Values
#define SUCCESS_VALUE 0
#define BASE_ERROR -100

//
/// Status Enumeration
///		- Success and Failure codes
//
typedef enum STATUS
{
	// General Failure
	STATUS_FAILURE = BASE_ERROR,

	// Class Inheritance Errors
	STATUS_VIRTUAL_METHOD_ERROR,

	// State Machine Errors
	STATUS_INVALID_MESSAGE,

	// Invalid Parameter Failures

	// Setup Failures
	STATUS_INITIALIZATION_ERROR,

	// Message Queue Specific
	STATUS_QUEUE_EMPTY,
	STATUS_QUEUE_FULL,
	STATUS_QUEUE_TIMEOUT_NOT_SUPPORTED,
	STATUS_QUEUE_TIMEOUT,

	// Message Queue Manager Specific

	// General Success
	STATUS_SUCCESS = SUCCESS_VALUE,

	// Manager General Success
	STATUS_SHUTDOWN_SUCCESS,
	
};

};
#endif // #ifndef __Status_h_