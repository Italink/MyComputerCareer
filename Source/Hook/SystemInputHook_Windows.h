#ifdef _WIN32

#ifndef SystemInputHook_Windows_h__
#define SystemInputHook_Windows_h__

#include "SystemInputHook.h"
#include <windows.h>

class SystemInputHook_Windows : public SystemInputHook 
{
public:
	SystemInputHook_Windows();
	void startup(KeyboardEventCallback keyboardCallback, MouseEventCallback mouseCallback) override;
	void shutdown() override;
private:
	HHOOK mKeyboardHook = 0;
	HHOOK mMouseHook = 0;
};

#endif // SystemInputHook_Windows_h__

#endif // _WIN32