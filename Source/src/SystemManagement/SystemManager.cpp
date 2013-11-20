//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#include "SystemManagement\SystemManager.h"
#include "LoggingManagement\LogManager.h"
#include "QueueManagement\QueueManager.h"
#include "QueueManagement\MessageManager.h"


// Initialize static member variables
ULONG       SystemManager::queue_id = 0;


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
SystemManager::SystemManager(void)
{
    mState = SYSTEM_MANAGER_INIT;
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
SystemManager::~SystemManager(void)
{
    QueueManager::deleteQueues();
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
STATUS SystemManager::initializeLogManager(void)
{
    LogManager* logManager = new LogManager();

    // Spawn the thread
    mLoggingThread = new boost::thread(LogManager::threadEntry, logManager);

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
STATUS SystemManager::shutdownLogManager(void)
{
    LogManager::logMessage(MODULE_SYSTEM_MANAGER,
                           INFO_LEVEL,
                           SHUTDOWN_LOG_MANAGER,
                           "Closing LogManager Thread");
    mLoggingThread->join();
    delete mLoggingThread;
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
STATUS SystemManager::initializeGraphicsEngine(void) 
{
    ULONG queueId = 0;
    
    // Create a message queue
    QueueManager::createQueue(queueId, MAX_QUEUE_SIZE_DEFAULT);
    
    // Spawn Graphic Engine
    GraphicEngine* graphicEngine = new GraphicEngine(queueId);
    graphicEngine->initialize();
    mWindow = graphicEngine->getWindowPtr();
    
    // Spawn the thread
    boost::thread *graphicEngineThread = new boost::thread(GraphicEngine::threadEntry, graphicEngine);
    mThreadGroup.add_thread(graphicEngineThread);
    
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
STATUS SystemManager::initializeGameEngine(void) 
{
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
STATUS SystemManager::initializeInputManager(void) 
{
    ULONG queueId = 0;
    
    // Create a message queue
    QueueManager::createQueue(queueId, MAX_QUEUE_SIZE_DEFAULT);
    
    // Spawn Input Manager
    InputManager* inputManager = new InputManager(queueId, mWindow);
    inputManager->setupInputSystem(); // Currently always returns success
    inputManager->setShutdownCallback(SystemManager::triggerShutdown);
    
    // Spawn the thread
    boost::thread *inputManagerThread = new boost::thread(InputManager::threadEntry, inputManager);
    mThreadGroup.add_thread(inputManagerThread);
    
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
STATUS SystemManager::initializeManagers(void)
{
    STATUS status = STATUS_FAILURE;
    
    status = initializeGraphicsEngine();
    if(status != STATUS_SUCCESS)
    {
        // Log
        return status;
    }
    
    status = initializeInputManager();
    
    return status;
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
STATUS SystemManager::systemLoop(void) 
{
    STATUS                                  status = STATUS_FAILURE;
    MessageManager<SystemManagerMessage>    messageManager;
    SystemManagerMessage                    message;
    
    // Create a message queue
    QueueManager::createQueue(SystemManager::queue_id, MAX_QUEUE_SIZE_DEFAULT);
    
    // Post an activate message
    message.major_type = SYSTEM_ACTIVATE;
    messageManager.postMessage(SystemManager::queue_id, message, QUEUE_TIMEOUT_INFINITE);
    
    // Start loop
    while(1) 
    {
        status = messageManager.getMessage(SystemManager::queue_id,
                                           message,
                                           QUEUE_TIMEOUT_DEFAULT);
        
        if(status == STATUS_SUCCESS)
        {
            LogManager::logMessage(MODULE_SYSTEM_MANAGER,
                                   DEBUG_LEVEL,
                                   NULL,
                                   "Received Message, Major Type: %lu",
                                   message.major_type);
            
            switch(mState)
            {
                case SYSTEM_MANAGER_INIT:
                    status = initProcessing(message);
                    break;
                
                case SYSTEM_MANAGER_ACTIVE:
                    status = activeProcessing(message);
                    break;
                
                case SYSTEM_MANAGER_SHUTDOWN:
                    status = shutdownProcessing(message);
                    break;
                
                default:
                    break;
            }
            
            if(status == STATUS_SHUTDOWN_SUCCESS)
            {
                break;
            }
        }
    }
    
    mThreadGroup.join_all();
    
    LogManager::logMessage(MODULE_SYSTEM_MANAGER,
                           DEBUG_LEVEL,
                           NULL,
                           "All Threads Joined Succesfully.");
    
    return STATUS_SUCCESS;
}