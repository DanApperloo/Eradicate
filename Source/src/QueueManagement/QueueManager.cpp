//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
// Includes
#include "QueueManagement\QueueManager.h"

MessageQueue*           QueueManager::queue_array[QUEUE_MANAGER_MAX_QUEUE] = {NULL};
ULONG                   QueueManager::registered_queue_count = 0;
boost::mutex            QueueManager::queue_array_modification_mutex;


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
STATUS QueueManager::createQueue(
    ULONG   &queue_id,
    ULONG   max_size
    )
{
    boost::unique_lock<boost::mutex> mlock(queue_array_modification_mutex);
    queue_array[registered_queue_count] = new MessageQueue(max_size);
    queue_id = registered_queue_count;
    registered_queue_count++;
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
STATUS QueueManager::deleteQueues(void)
{
    boost::unique_lock<boost::mutex> mlock(queue_array_modification_mutex);
    for(ULONG i=0; i<registered_queue_count; i++)
    {
        delete queue_array[i];
    }
    registered_queue_count = 0;
    return STATUS_SUCCESS;
}
