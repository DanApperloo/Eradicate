//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef __MessageManager_h_
#define __MessageManager_h_

// Includes
#include <stdafx.h>
#include "QueueManagement\QueueManager.h"

// Namespaces
using namespace Eradicate;

// Defines
#define QUEUE_MANAGER_MAX_QUEUE 30          //////// Subject to change

template <class MESSAGE_TYPE>
class MessageManager : public QueueManager
{
	public:

		STATUS postMessage(
			ULONG					queue_id,
			MESSAGE_TYPE			&message,
			MESSAGE_QUEUE_TIMEOUT	timeout
			)
		{
			STATUS			  status = STATUS_FAILURE;
			AbstractMessage	  *baseMessage = new MESSAGE_TYPE(message);
		
			status = queue_array[queue_id]->PushMessage(baseMessage, timeout);
		
			return status;
		}
		
		STATUS getMessage(
			ULONG					queue_id,
			MESSAGE_TYPE			&message,
			MESSAGE_QUEUE_TIMEOUT	timeout
			)
		{
			STATUS			  status = STATUS_FAILURE;
			MESSAGE_TYPE	  *messageType = NULL;
			AbstractMessage	  *baseMessage = NULL;
		
			status = queue_array[queue_id]->PopMessage(baseMessage, timeout);
			
			if(status == STATUS_SUCCESS)
			{
				messageType = static_cast<MESSAGE_TYPE*>(baseMessage); 
				message = MESSAGE_TYPE(*messageType);
				delete baseMessage;
			}
		
			return status;
		}

}; 

#endif // __MessageManager_h_