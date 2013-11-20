//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef __GraphicEngine_h_
#define __GraphicEngine_h_

// Includes
#include <stdafx.h>
#include "GraphicsEngine\GraphicEngineFsm.h"
#include "GraphicsEngine\GraphicEngineMessages.h"
#include "GraphicsEngine\Listeners\WindowListener.h"
#include "GraphicsEngine/Managers/FrameManagement/FrameManager.h"
#include "GraphicsEngine/Managers/EntityManagement/AnimeManager.h" // Example Uses

// Namespaces
using namespace Eradicate;

class GraphicEngine
{
    // Public Access
    public:
        static void threadEntry(GraphicEngine* manager);
        
        GraphicEngine(ULONG queueId);
        ~GraphicEngine(void);
        STATUS initialize();
        // Getters
        Ogre::RenderWindow* getWindowPtr();
        // Display Control Functions
        bool renderOneFrame();
        // Windows Message Functions
        STATUS windowsMessagePump();
        
        // API
        static STATUS postActivate(void);
        static STATUS postTransitionToShutdown(void);
        static STATUS postShutdown(void);

        AnimeManager* mAnimeManager; // Points to AnimeManager

    protected:
        STATUS setupOGRE();
        STATUS loadResources();
        STATUS createRenderWindow();
        STATUS initializeFrameManager();
        STATUS initializeResources();
        STATUS setupCEGUI();
        STATUS exampleSetup(); // Not real method: used for example. Remove after.
        
    private:
        // Read-only After Init Members
        static ULONG queue_id;
        
        // Methods
        STATUS initProcessing(GraphicEngineMessage message);
        STATUS activeProcessing(GraphicEngineMessage message);
        STATUS shutdownProcessing(GraphicEngineMessage message);
        
        // GraphicEngineControl Methods
        STATUS graphicEngineControlInitProcessing(GRAPHIC_ENGINE_CONTROL_MESSAGE message);
        STATUS graphicEngineControlActiveProcessing(GRAPHIC_ENGINE_CONTROL_MESSAGE message);
        STATUS graphicEngineControlShutdownProcessing(GRAPHIC_ENGINE_CONTROL_MESSAGE message);
        
        // Members
        GRAPHIC_ENGINE_STATE    mState;
        Ogre::Root*             mRoot; // Points to the Ogre Root object
        Ogre::String            mPluginsCfg; // Defines the location of the plugins config file
        Ogre::String            mVideoCfg; // Defines the location of the video config file
        Ogre::String            mLogFile; // Defines the Ogre output log name
        Ogre::String            mResourcesCfg; // Defines the location of the resources config file
        Ogre::RenderWindow*     mWindow; // Points to the Render Window
        CEGUI::OgreRenderer*    mRenderer; // Points to the Ogre Renderer
        FrameManager*           mFrameManager; // Points to the FrameManager
        WindowListener*         mListener; // Ogre Window Listener
        //AnimeManager* mAnimeManager; // Points to AnimeManager
};
#endif // #ifndef __GraphicEngine_h_
