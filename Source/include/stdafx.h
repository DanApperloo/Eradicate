/*
-----------------------------------------------------------------------
	Filename: stdafx.h
	Author: Dan Apperloo
	Date: June 15, 2013
-----------------------------------------------------------------------
	Description:
	Include file for standard system include files,
	or project specific include files that are used frequently, but
	are changed infrequently
-----------------------------------------------------------------------
*/

// Compile only once
#pragma once

// Windows version information
#include <targetver.h>

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN             

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <queue>				// std::queue

// OGRE Header Files
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreException.h>
#include <OgreWindowEventUtilities.h> // Special Event Reader
   
// OIS Header Files
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

// CEGUI Header Files
#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>

// Game Specific Files
#include "Utility/Status.h"
#include "QueueManagement/QueueManager.h"

// Global Defines
#define ERADICATE_GAME_NAME "Game Name"

// Global Typedefs
typedef Eradicate::STATUS (*callback)(void);