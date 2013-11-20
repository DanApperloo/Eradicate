//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef __MessageQueue_h_
#define __MessageQueue_h_

// Includes
#include "stdafx.h"
#include "QueueManagement\Objects\AbstractMessage.h"

// Namespace Declaration -- Avoids Status declaration collisions
namespace Eradicate
{
// Definitions
#define MAX_QUEUE_SIZE_DEFAULT 0x50   // Max size default = 80

#define NO_TIMEOUT_ON_WAIT true // boost::condition_variable return value when timeout is not hit on wait_for()

// Durations specified in milliseconds
#define QUEUE_TIMEOUT_PLACEHOLDER_VALUE		boost::posix_time::milliseconds(0)
#define QUEUE_TIMEOUT_DEFAULT_VALUE			boost::posix_time::milliseconds(50)
#define QUEUE_TIMEOUT_EXTENDED_VALUE		boost::posix_time::milliseconds(100)
#define QUEUE_TIMEOUT_TEST_VALUE            boost::posix_time::milliseconds(250)

}

using namespace Eradicate;
//
///		NAME
//
///		SHORT DESCRIPTION
//
///		Description:
///			LONG DESCRIPTION
///
//
typedef enum MESSAGE_QUEUE_TIMEOUT
{
	QUEUE_TIMEOUT_ONCE = 0,

	QUEUE_TIMEOUT_DEFAULT,
	QUEUE_TIMEOUT_EXTENDED,
    QUEUE_TIMEOUT_TEST,

	QUEUE_TIMEOUT_INFINITE,

	QUEUE_TIMEOUT_SIZE

};


//
///		NAME
//
///		SHORT DESCRIPTION
//
///		Description:
///			LONG DESCRIPTION
///
//
static boost::posix_time::milliseconds s_message_queue_timeout_map[QUEUE_TIMEOUT_SIZE] = 
{
	QUEUE_TIMEOUT_PLACEHOLDER_VALUE,	// Represents QUEUE_TIMEOUT_ONCE

	QUEUE_TIMEOUT_DEFAULT_VALUE,
	QUEUE_TIMEOUT_EXTENDED_VALUE,
    QUEUE_TIMEOUT_TEST_VALUE,

	QUEUE_TIMEOUT_PLACEHOLDER_VALUE		// Represents QUEUE_TIMEOUT_INFINITE
};


//
///		NAME
//
///		SHORT DESCRIPTION
//
///		Description:
///			LONG DESCRIPTION
///
//
class MessageQueue
{
	// Private Access
	private:
		// Property Members
		ULONG							max_size;					// Buffer max size

		// Data Members
		boost::condition_variable		buffer_not_full;			// Buffer is not full
		boost::condition_variable		buffer_not_empty;			// Buffer is not empty
		boost::mutex					buffer_mutex;				// Buffer is being accessed
		std::queue<AbstractMessage*>	buffer;						// Queue (Pass by Value)
		
		// Pop Message Functions
		STATUS PopMessageNoTimeout(AbstractMessage* &message);
		STATUS PopMessageWithTimeout(AbstractMessage* &message, const boost::posix_time::milliseconds timeout);
		STATUS TryPopMessage(AbstractMessage* &message);

		// Push Message Functions
		STATUS PushMessageNoTimeout(AbstractMessage* message);
		STATUS PushMessageWithTimeout(AbstractMessage* message, const boost::posix_time::milliseconds timeout);
		STATUS TryPushMessage(AbstractMessage* message);

	// Public Access
	public:
		// Constructor
		MessageQueue(ULONG size_allowed = MAX_QUEUE_SIZE_DEFAULT);
		// Destructor
		~MessageQueue();

		// Access Methods
		STATUS PushMessage(AbstractMessage* message, const MESSAGE_QUEUE_TIMEOUT timeout = QUEUE_TIMEOUT_EXTENDED);
		STATUS PopMessage(AbstractMessage* &message, const MESSAGE_QUEUE_TIMEOUT timeout = QUEUE_TIMEOUT_DEFAULT);

};
#endif // #ifndef __MessageQueue_h_