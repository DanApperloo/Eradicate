//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#include "SystemManagement\SystemManager.h"
#include "QueueManagement\MessageManager.h"

//
///		NAME
//
///		SHORT DESCRIPTION
//
///		Description:
///			LONG DESCRIPTION
///
///		Return
///			VALUE and DESCRIPTION
//
STATUS SystemManager::triggerShutdown(void)
{
	SystemManagerMessage  message;
	MessageManager<SystemManagerMessage> messageManager;

	// Post an activate message
	message.major_type = SYSTEM_TRANSITION_TO_SHUTDOWN;
	messageManager.postMessage(SystemManager::queue_id, message, QUEUE_TIMEOUT_INFINITE);

	// Post an activate message
	message.major_type = SYSTEM_SHUTDOWN;
	messageManager.postMessage(SystemManager::queue_id, message, QUEUE_TIMEOUT_INFINITE);

	return STATUS_SUCCESS;
}