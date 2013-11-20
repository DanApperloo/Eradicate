#ifndef __ConversationManager_h_
#define __ConversationManager_h_

#include <stdafx.h>
#include "GraphicsEngine\Managers\EntityManagement\AnimeManager.h"

class ConversationManager
{
	// Public Access
	public:
		ConversationManager();
		~ConversationManager(void);
		void registerConversation(Ogre::String script);
		void executeConversation(Ogre::String script);

	private:
		// Storage of path by callname
		AnimeManager* mAnimeManager;

};
#endif // #ifndef __ConversationManager_h_