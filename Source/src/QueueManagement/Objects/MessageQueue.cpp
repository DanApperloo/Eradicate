//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
// Includes
#include "QueueManagement\Objects\MessageQueue.h"


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
MessageQueue::MessageQueue(
    ULONG size_allowed
    )
{
    max_size = size_allowed;
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
MessageQueue::~MessageQueue()
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
STATUS MessageQueue::PopMessageNoTimeout(
    AbstractMessage *&message
    )
{
    boost::unique_lock<boost::mutex> mlock(buffer_mutex);
    if(buffer.empty())
    {
        buffer_not_empty.wait(mlock, [this](){return !buffer.empty();});
    }
    message = buffer.front();
    buffer.pop();
    buffer_not_full.notify_one();
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
STATUS MessageQueue::PopMessageWithTimeout(
    AbstractMessage*                      &message,
    const boost::posix_time::milliseconds timeout
    )
{
    boost::unique_lock<boost::mutex> mlock(buffer_mutex);
    
    if(buffer.empty())
    {
        if(buffer_not_empty.timed_wait(mlock, timeout, [this](){return !buffer.empty();}) == NO_TIMEOUT_ON_WAIT)
        {
            message = buffer.front();
            buffer.pop();
            return STATUS_SUCCESS;
        }
        else
        {
            return STATUS_QUEUE_TIMEOUT;
        }
    }
    else
    {
        message = buffer.front();
        buffer.pop();
        buffer_not_full.notify_one();
        return STATUS_SUCCESS;
    }
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
STATUS MessageQueue::TryPopMessage(
    AbstractMessage *&message
    )
{
    boost::unique_lock<boost::mutex> mlock(buffer_mutex);
    if(buffer.empty())
    {
        return STATUS_QUEUE_EMPTY;
    }
    message = buffer.front();
    buffer.pop();
    buffer_not_full.notify_one();
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
STATUS MessageQueue::PushMessageNoTimeout(
    AbstractMessage *message
    )
{
    boost::unique_lock<boost::mutex> mlock(buffer_mutex);
    if(buffer.size() == max_size)
    {
        buffer_not_full.wait(mlock, [this](){return buffer.size() != max_size;});
    }
    buffer.push(message);
    buffer_not_empty.notify_one();
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
STATUS MessageQueue::PushMessageWithTimeout(
    AbstractMessage                       *message,
    const boost::posix_time::milliseconds timeout
    )
{
    boost::unique_lock<boost::mutex> mlock(buffer_mutex);
    
    if(buffer.size() == max_size)
    {
        if(buffer_not_full.timed_wait(mlock, boost::get_system_time() + timeout, [this](){return buffer.size() != max_size;}) == NO_TIMEOUT_ON_WAIT)
        {
            buffer.push(message);
            buffer_not_empty.notify_one();
            return STATUS_SUCCESS;
        }
        else
        {
            return STATUS_QUEUE_TIMEOUT;
        }
    }
    else
    {
        buffer.push(message);
        buffer_not_empty.notify_one();
        return STATUS_SUCCESS;
    }
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
STATUS MessageQueue::TryPushMessage(
    AbstractMessage *message
    )
{
    boost::unique_lock<boost::mutex> mlock(buffer_mutex);
    if(buffer.size() == max_size)
    {
        return STATUS_QUEUE_FULL;
    }
    buffer.push(message);
    buffer_not_empty.notify_one();
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
STATUS MessageQueue::PushMessage(
    AbstractMessage             *message,
    const MESSAGE_QUEUE_TIMEOUT timeout
    )
{
    switch(timeout)
    {
        case QUEUE_TIMEOUT_INFINITE:
            return PushMessageNoTimeout(message);
        
        case QUEUE_TIMEOUT_ONCE:
            return TryPushMessage(message);
        
        case QUEUE_TIMEOUT_DEFAULT:
        case QUEUE_TIMEOUT_EXTENDED:
            return PushMessageWithTimeout(message, s_message_queue_timeout_map[timeout]);
        
        default:
            return STATUS_QUEUE_TIMEOUT_NOT_SUPPORTED;
    }
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
STATUS MessageQueue::PopMessage(
    AbstractMessage             *&message, 
    const MESSAGE_QUEUE_TIMEOUT timeout
    )
{
    switch(timeout)
    {
        case QUEUE_TIMEOUT_INFINITE:
            return PopMessageNoTimeout(message);
        
        case QUEUE_TIMEOUT_ONCE:
            return TryPopMessage(message);
        
        case QUEUE_TIMEOUT_DEFAULT:
        case QUEUE_TIMEOUT_EXTENDED:
            return PopMessageWithTimeout(message, s_message_queue_timeout_map[timeout]);
        
        default:
            return STATUS_QUEUE_TIMEOUT_NOT_SUPPORTED;
    }
}