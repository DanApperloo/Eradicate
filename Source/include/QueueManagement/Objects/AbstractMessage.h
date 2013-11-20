//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef __AbstractMessage_h_
#define __AbstractMessage_h_

// Includes
#include <stdafx.h>

// Namespaces
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
class AbstractMessage
{
	// Public Access
	public:
		virtual ULONG getMajorMessageType() = 0;

};

#endif // #ifndef __AbstractMessage_h_