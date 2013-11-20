//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#include "InputManagement/Listeners/InputBroker.h"


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
InputBroker::InputBroker(
    OIS::InputManager* inputManager
    )
    : mCEGUISystem(0) // Initialize the CEGUI::System pointer to null
{
    mInputManager = inputManager;
    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));
    
    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);
    
    mCEGUISystem = CEGUI::System::getSingletonPtr();
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
InputBroker::~InputBroker(void) 
{
    mInputManager->destroyInputObject(mMouse);
    mInputManager->destroyInputObject(mKeyboard);
    mInputManager = 0;
    
    mCEGUISystem = 0;
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
STATUS InputBroker::setShutdownCallback(
    callback call
    )
{
    triggerShutdown = call;
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
bool InputBroker::keyPressed(
    const OIS::KeyEvent& evt
    ) 
{
    unsigned int ch = evt.text;
    mCEGUISystem->injectKeyDown(evt.key);

    switch (evt.key) {
        case OIS::KC_ESCAPE:
            triggerShutdown();
            break;

        default:
            break;
        }
    return mCEGUISystem->injectChar(ch);
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
bool InputBroker::keyReleased(
    const OIS::KeyEvent& evt
    ) 
{
    return mCEGUISystem->injectKeyUp(evt.key);
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
bool InputBroker::mouseMoved(
    const OIS::MouseEvent& evt
    ) 
{
    mCEGUISystem->injectMouseWheelChange((float) evt.state.Z.rel);
    return mCEGUISystem->injectMouseMove((float) evt.state.X.rel, 
                                         (float) evt.state.Y.rel);
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
bool InputBroker::mousePressed(
    const OIS::MouseEvent& evt, 
    OIS::MouseButtonID id
    ) 
{
    CEGUI::MouseButton button = CEGUI::NoButton;
    
    if (id == OIS::MB_Left)
        button = CEGUI::LeftButton;
    
    if (id == OIS::MB_Middle)
        button = CEGUI::MiddleButton;
    
    if (id == OIS::MB_Right)
        button = CEGUI::RightButton;
    
    return mCEGUISystem->injectMouseButtonDown(button);
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
bool InputBroker::mouseReleased(
    const OIS::MouseEvent&  evt, 
    OIS::MouseButtonID      id
    ) 
{ 
    CEGUI::MouseButton button = CEGUI::NoButton;
 
    if (id == OIS::MB_Left)
        button = CEGUI::LeftButton;
 
    if (id == OIS::MB_Middle)
        button = CEGUI::MiddleButton;
 
    if (id == OIS::MB_Right)
        button = CEGUI::RightButton;

    return mCEGUISystem->injectMouseButtonUp(button);
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
STATUS InputBroker::captureInput()
{
    // Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();
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
STATUS InputBroker::setWindowExtents(
    int width, 
    int height
    ) 
{
    // Set mouse region (if window resizes, we should alter this to reflect as well)
    const OIS::MouseState &mouseState = mMouse->getMouseState();
    mouseState.width  = width;
    mouseState.height = height;
    return STATUS_SUCCESS;
}