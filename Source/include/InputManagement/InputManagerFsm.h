//////////////////////////////////////////////////////////////////////////////////////
//																					//
//																					//
//																					//
//																					//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef __InputManagerFsm_h_
#define __InputManagerFsm_h_

typedef enum INPUT_MANAGER_STATE
{
	INPUT_MANAGER_INIT = 0,
	INPUT_MANAGER_ACCEPT,
	INPUT_MANAGER_IGNORE,
	INPUT_MANAGER_SHUTDOWN
};

#endif // #ifndef __InputManagerFsm_h_