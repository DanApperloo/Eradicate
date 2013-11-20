//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#include "GraphicsEngine/GraphicEngine.h"
#include "QueueManagement\MessageManager.h"
#include "LoggingManagement\LogManager.h"
#include "GraphicsEngine/GraphicObjects/Entities/MapBlock.h" // Example Uses
#include "GraphicsEngine/GraphicObjects/Entities/StaticBackground.h" // Example Uses
#include "GraphicsEngine/GraphicObjects/Entities/Sprite.h" // Example Uses
#include "GraphicsEngine/GraphicObjects/Drawables/BillboardDrawable.h" // Example Uses
#include "GraphicsEngine/Factories/AnimeComponentFactory.h" // Example Uses
#include "GraphicsEngine/GraphicObjects/Drawables/ImageOverlay.h" // Example Uses
#include "GraphicsEngine/Managers/ConversationManagement/ConversationManager.h" // Example Uses

// Initialize static member variables
ULONG       GraphicEngine::queue_id = 0;

/*
	Default Constructor.
*/
GraphicEngine::GraphicEngine(
    ULONG queueId
    )
    : mRoot(0), // Initialize OGRE root pointer to null
    mPluginsCfg(Ogre::StringUtil::BLANK), // Initialize location of plugin config to empty string
    mVideoCfg(Ogre::StringUtil::BLANK), // Initialize location of video config to empty string
    mLogFile(Ogre::StringUtil::BLANK), // Initialize location of log file to empty string
    mResourcesCfg(Ogre::StringUtil::BLANK), // Initialize location of resources config to empty string
    mWindow(0), // Initialize Window pointer to null
    mRenderer(0), // Intialize Renderer pointer to null
    mFrameManager(0), // Initialize FrameManager pointer to null
    mAnimeManager(0), // Initialize AnimeManager pointer to null
    mListener(0)
{
    mState = GRAPHIC_ENGINE_INIT;
    queue_id = queueId;
}


/*
    Destructor.
*/
GraphicEngine::~GraphicEngine(void) 
{
    delete mListener;
    delete mAnimeManager;
    delete mFrameManager; // Cleanup FrameManager
    delete mRoot; // Cleanup the OGRE root
}


/*
    Run the setup in the specified order.
*/
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
STATUS GraphicEngine::initialize() 
{
    setupOGRE();
    loadResources();
    createRenderWindow();
    initializeResources();
    setupCEGUI();
    initializeFrameManager();
    return STATUS_SUCCESS;
}


/* 
    Initalize OGRE Root with Configuration.
*/
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
STATUS GraphicEngine::setupOGRE() 
{
    // Define the locations of the config files
    #ifdef _DEBUG
        mPluginsCfg = "plugins_d.cfg"; // Debug plugin file
        mVideoCfg = "ogre_d.cfg"; // Debug video settings file
        mLogFile = "Ogre_d.log"; // Debug log file
        mResourcesCfg = "resources_d.cfg"; // Debug resources file
    #else
        mPluginsCfg = "plugins.cfg"; // Release plugin file
        mVideoCfg = "ogre.cfg"; // Release video settings file
        mLogFile = "Ogre.log"; // Release log file
        mResourcesCfg = "resources.cfg"; // Release resources file
    #endif
    
    // Construct Ogre::Root, using the required plugin filepath
    mRoot = new Ogre::Root(mPluginsCfg, mVideoCfg, mLogFile);
    //-----------------------------------------------------------------
    return STATUS_SUCCESS;
}


/*
    Setup and parse Resources in Resources Config file.
*/
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
STATUS GraphicEngine::loadResources() 
{
    // Parse the resources config file
    Ogre::ConfigFile configFile;
    configFile.load(mResourcesCfg);
    
    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = configFile.getSectionIterator();
    
    // Basic Resource File Parsing Loop. 
    // Loads in the specified resource locations to the Resource Manager.
    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements()) {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext(); 
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i) {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, 
                                                                           typeName, 
                                                                           secName);
        }
    }
    //-----------------------------------------------------------------
    return STATUS_SUCCESS;
}


/*
    Create the RenderSystem.
*/
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
STATUS GraphicEngine::createRenderWindow() 
{
    /*
    Ogre::NameValuePairList renderWindowConfig;
    HWND hWnd = 0; // Get the hWnd of the applicaiton -- TODO// Create loading image and window using win32 api
    renderWindowConfig["hidden"] = "true";
    renderWindowConfig["externalWindowHandle"] = Ogre::StringConverter::toString((int)hWnd);
    */

    // Show the configuration dialog and initialise the system
    if(!(mRoot->restoreConfig() || mRoot->showConfigDialog())) // If there is previous configuration, restore it
    //if(!(mRoot->showConfigDialog())) // If there is previous configuration, restore it
    {
        return STATUS_FAILURE;
    }
    mWindow = mRoot->initialise(true, ERADICATE_GAME_NAME);

    /*
    mRoot->initialise(false); // Do not automatically create a window
    mWindow = mRoot->createRenderWindow(ERADICATE_GAME_NAME,    // Window Title
                                        800,                    // Window Width
                                        600,                    // Window Height
                                        FALSE,                  // Fullscreen?
                                        &renderWindowConfig);   // Set window to be hidden by default
    */

    mListener = new WindowListener(mWindow);
    mListener->initialize();
    //-----------------------------------------------------------------
    return STATUS_SUCCESS;
}


/*
    Create a basic FrameListener.
*/
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
STATUS GraphicEngine::initializeFrameManager() 
{
    mFrameManager = new FrameManager(mWindow);
    return STATUS_SUCCESS;
}


/*
    Initialize the resources.
*/
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
STATUS GraphicEngine::initializeResources() 
{
    // Set default mipmap level (note: some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    // Initialize all resource groups
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    //-----------------------------------------------------------------
    return STATUS_SUCCESS;
}


/*
    Setup and initialize CEGUI with OGRE.
*/
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
STATUS GraphicEngine::setupCEGUI() 
{
    // Initialize CEGUI with the OgreRenderer
    mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
    
    // Set the CEGUI logging to maximum
    CEGUI::Logger::getSingleton().setLoggingLevel(CEGUI::LoggingLevel::Insane);
    
    // Load the Resource Group defaults using resource groups defined in the config file
    CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
    
    // Select the scheme or "Skin" for CEGUI elements
    CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
    
    // Select the default cursor appearence
    CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");
    
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
Ogre::RenderWindow* GraphicEngine::getWindowPtr() 
{
    return mWindow;
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
bool GraphicEngine::renderOneFrame() 
{
    return Ogre::Root::getSingleton().renderOneFrame();
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
STATUS GraphicEngine::windowsMessagePump() 
{
    Ogre::WindowEventUtilities::messagePump();
    return STATUS_SUCCESS;
}


/*
    NOT REAL CODE: USED FOR EXAMPLE. REMOVE AFTER.
*/
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
STATUS GraphicEngine::exampleSetup() 
{
    // Setup Camera
    Ogre::SceneManager* mSceneManager = Ogre::Root::getSingletonPtr()->createSceneManager("DefaultSceneManager");
    Ogre::Camera* mCamera = mSceneManager->createCamera("Camera");
    
    // Position it at 80 in Z direction
    mCamera->setPosition(Ogre::Vector3(50,0,50));
    
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);
    
    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
    
    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
        Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
    
    mAnimeManager = new AnimeManager();
    
    ImageOverlay panelA = AnimeComponentFactory().createTestImage("TestA", 
                Ogre::Vector2(0.25, 0.25), Ogre::Vector2(0.5,0.5), 5, Ogre::GMM_RELATIVE, "Examples/Background2");
    
    ImageOverlay panelB = AnimeComponentFactory().createTestImage("TestB",
                Ogre::Vector2(0, 0), Ogre::Vector2(0.5,0.5), 4, Ogre::GMM_RELATIVE, "Examples/Background2");
    
    mAnimeManager->addOverlay(panelB);
    mAnimeManager->addOverlay(panelA);
    
    mAnimeManager->showAllOverlays();
    //mAnimeManager->showOverlayByName("TestA");
    //mAnimeManager->showOverlayByName("TestB");
    
    Ogre::Vector3 position = Ogre::Vector3(0,0,0);
    //Ogre::Vector2 position = Ogre::Vector2(0,0);
    
    //BillboardDrawable mDraw = BillboardDrawable(mSceneManager, mSceneManager->getRootSceneNode(), "Billboard", "Examples/OgreParade", position);
    //mDraw.show();
    
    /*
    Sprite mCharacter = Sprite(mSceneManager, mSceneManager->getRootSceneNode(), "Backdrop", "Examples/OgreParade", 10, 10, position, 0);
    mCharacter.show();
    */
    
    
    //MapBlock mHead = MapBlock(mSceneManager, mSceneManager->getRootSceneNode(), "Head", "ogrehead.mesh", position, position);
    //mHead.show();
    
    
    /*
    Ogre::Entity* ogreHead = mSceneManager->createEntity("Head", "ogrehead.mesh");
    Ogre::SceneNode* headNode = mSceneManager->getRootSceneNode()->createChildSceneNode();
    headNode->attachObject(ogreHead);
    */
    
    /*
    CEGUI::ImagesetManager::getSingletonPtr()->createFromImageFile("CEGUIDemo/BackgroundImage", "BackgroundPicture2.tga");
    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
    CEGUI::System::getSingleton().setGUISheet(sheet);
    StaticBackground back = StaticBackground("CEGUIDemo/BackgroundImage", "CEGUIDemo");
    sheet->addChildWindow(back.getBackground());
    */
    // Set ambient light
    mSceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    
    // Create a light
    Ogre::Light* l = mSceneManager->createLight("MainLight");
    l->setPosition(20,80,50);
    
    ConversationManager convManager = ConversationManager();
    convManager.executeConversation("Multiply");
    
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
STATUS GraphicEngine::initProcessing(
    GraphicEngineMessage message
    )
{
    switch(message.major_type)
    {
        case GRAPHIC_ENGINE_CONTROL:
            return graphicEngineControlInitProcessing(message.minor_msg.control_message);
            break;
    
        default:
            return STATUS_INVALID_MESSAGE;
            break;
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
STATUS GraphicEngine::activeProcessing(
    GraphicEngineMessage message
    )
{
    switch(message.major_type)
    {
        case GRAPHIC_ENGINE_CONTROL:
            LogManager::logMessage(MODULE_GRAPHIC_ENGINE,
                                   DEBUG_LEVEL,
                                   NULL,
                                   "Received Message, Control Code: %lu",
                                   message.minor_msg.control_message.minor_type);
            return graphicEngineControlActiveProcessing(message.minor_msg.control_message);
            break;
        
        default:
            return STATUS_INVALID_MESSAGE;
            break;
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
STATUS GraphicEngine::shutdownProcessing(
    GraphicEngineMessage message
    )
{
    switch(message.major_type)
    {
        case GRAPHIC_ENGINE_CONTROL:
            return graphicEngineControlShutdownProcessing(message.minor_msg.control_message);
            break;
        
        default:
            return STATUS_INVALID_MESSAGE;
            break;
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
void GraphicEngine::threadEntry(
    GraphicEngine* manager
    )
{
    GraphicEngine*          graphicsEngine = manager;
    MessageManager<GraphicEngineMessage> messageManager;
    GraphicEngineMessage    message;
    STATUS                  status = STATUS_FAILURE;

    while(1)
    {
        status = messageManager.getMessage(GraphicEngine::queue_id,
                                           message,
                                           QUEUE_TIMEOUT_DEFAULT);
        
        // If a message was retrieved, process it
        if(status == STATUS_SUCCESS)
        {
            switch(graphicsEngine->mState)
            {
                case GRAPHIC_ENGINE_INIT:
                    status = graphicsEngine->initProcessing(message);
                    break;
            
                case GRAPHIC_ENGINE_ACTIVE:
                    status = graphicsEngine->activeProcessing(message);
                    break;
            
                case GRAPHIC_ENGINE_SHUTDOWN:
                    status = graphicsEngine->shutdownProcessing(message);
                    break;
            
                default:
                    break;
            }
        }

        // Pump window messages for nice behaviour
        graphicsEngine->windowsMessagePump();

        // Render a frame
        graphicsEngine->renderOneFrame();

        if(status == STATUS_SHUTDOWN_SUCCESS)
        {
            break;
        }
    }

    LogManager::logMessage(MODULE_GRAPHIC_ENGINE,
                           DEBUG_LEVEL,
                           NULL,
                           "Successfully transitioned to SHUTDOWN");

    // Ensure Cleanup
    delete graphicsEngine;
}