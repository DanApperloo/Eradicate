#include <Python.h>
#include "GraphicsEngine/Managers/ConversationManagement/ConversationManager.h"

//---------------------------------------------------------------------
/*
	Default Constructor.
*/
ConversationManager::ConversationManager()
{
}
//---------------------------------------------------------------------
/*
	Destructor.
*/
ConversationManager::~ConversationManager(void) {
}
//---------------------------------------------------------------------
void ConversationManager::registerConversation(Ogre::String script) {

}
//---------------------------------------------------------------------
void ConversationManager::executeConversation(Ogre::String script) {
	PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pArgs, *pValue;

	UNREFERENCED_PARAMETER(pDict);

    Py_Initialize();
	const char* test = script.c_str();
    pName = PyUnicode_FromString(test);
    /* Error checking of pName left out */

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "Multiply");
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(2);
            pValue = PyLong_FromLong(2);
            if (!pValue) {
                Py_DECREF(pArgs);
                Py_DECREF(pModule);
                Ogre::LogManager::getSingleton().logMessage("Cannot convert argument");
            }
            /* pValue reference stolen here: */
            PyTuple_SetItem(pArgs, 0, pValue);

			pValue = PyLong_FromLong(3);
            if (!pValue) {
                Py_DECREF(pArgs);
                Py_DECREF(pModule);
				Ogre::LogManager::getSingleton().logMessage("Cannot convert argument");
            }
            /* pValue reference stolen here: */
            PyTuple_SetItem(pArgs, 1, pValue);

            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {
				char s[100];
				sprintf_s(s, "Result of call: %ld", PyLong_AsLong(pValue));
                Ogre::LogManager::getSingleton().logMessage(s);
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                Ogre::LogManager::getSingleton().logMessage("Call failed");
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            Ogre::LogManager::getSingleton().logMessage("Cannot find function Multiply");
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        Ogre::LogManager::getSingleton().logMessage("Failed to load Multiply");
    }
    Py_Finalize();
}
//---------------------------------------------------------------------