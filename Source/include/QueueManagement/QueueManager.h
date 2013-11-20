//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef __QueueManager_h_
#define __QueueManager_h_

// Includes
#include "stdafx.h"
#include "QueueManagement\Objects\MessageQueue.h"

using namespace Eradicate;

// Defines
#define QUEUE_MANAGER_MAX_QUEUE 30

class QueueManager
{
	protected:
		static MessageQueue*			queue_array[QUEUE_MANAGER_MAX_QUEUE];
		static ULONG					registered_queue_count;
		static boost::mutex				queue_array_modification_mutex;

	public:

		static STATUS createQueue(
			ULONG		&queue_id,
			ULONG		max_size
			);

		static STATUS deleteQueues(void);

};
#endif // __QueueManager_h_
