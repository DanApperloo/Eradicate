//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#include <stdafx.h>
#include "SystemManagement\SystemManager.h"

using namespace Eradicate;

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif
 
#ifdef __cplusplus
extern "C" {
#endif
 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        STATUS status = STATUS_FAILURE;
        // Create application object
        SystemManager excalibur_main;

        try {
            excalibur_main.initializeLogManager();
            excalibur_main.initializeManagers();
            excalibur_main.systemLoop();
            status = excalibur_main.shutdownLogManager();
        } 
        catch( Ogre::Exception& e ) 
        {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }
        if(status == STATUS_SUCCESS)
        {
            std::cout << "Completed Shutdown Successfully!" << std::endl;
            return 0;
        }
        else
        {
            return -1;
        }
    }
 
#ifdef __cplusplus
}
#endif