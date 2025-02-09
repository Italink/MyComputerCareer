#include "SystemInputHook.h"
#include "SystemInputHook_Windows.h"

SystemInputHook* SystemInputHook::Instance()
{
#ifdef _WIN32
	static SystemInputHook_Windows Inst;
	return &Inst;
#endif
	return nullptr;
}

void SystemInputHook::startup(KeyboardEventCallback keyboardCallback, MouseEventCallback mouseCallback)
{
	mKeyboardEventCallback = keyboardCallback;
	mMouseEventCallback = mouseCallback;
}

void SystemInputHook::shutdown()
{

}

void SystemInputHook::invokeKeyboardEvent(const MinimizedInputEvent_Keyboard& event)
{
	mKeyboardEventCallback(event);
}

void SystemInputHook::invokeMouseEvent(const MinimizedInputEvent_Mouse& event)
{
	mMouseEventCallback(event);
}

QString SystemInputHook::getShortKeyNameByVkCode(int vk)
{
	if (VkCodeToShortKeyName.find(vk) != VkCodeToShortKeyName.end()) {
		return VkCodeToShortKeyName[vk];
	}
	return "";
}

QString SystemInputHook::getKeyNameByVkCode(int vk)
{
	if (VkCodeToKeyName.find(vk) != VkCodeToKeyName.end()) {
		return VkCodeToKeyName[vk];
	}
	return "";
}

int SystemInputHook::getVkCodeByKeyName(QString keyName)
{
	for (const auto& item : VkCodeToKeyName.asKeyValueRange()) {
		if (item.second == keyName) {
			return item.first;
		}
	}
	return 0;
}

QMap<int, QString> SystemInputHook::VkCodeToKeyName = {
	{VK_LBUTTON, "Left Mouse Button"},
	{VK_RBUTTON, "Right Mouse Button"},
	{VK_MBUTTON, "Middle Mouse Button"},
	{VK_BACK, "Backspace"},
	{VK_TAB, "Tab"},
	{VK_RETURN, "Enter"},
	{VK_LSHIFT, "Left Shift"},
	{VK_RSHIFT, "Right Shift"},
	{VK_LCONTROL, "Left Ctrl"},
	{VK_RCONTROL, "Right Ctrl"},
	{VK_LMENU, "Left Alt"},
	{VK_RMENU, "Right Alt"},
	{VK_PAUSE, "Pause"},
	{VK_CAPITAL, "Caps Lock"},
	{VK_ESCAPE, "Esc"},
	{VK_SPACE, "Space"},
	{VK_PRIOR, "Page Up"},
	{VK_NEXT, "Page Down"},
	{VK_END, "End"},
	{VK_HOME, "Home"},
	{VK_LEFT, "←"},
	{VK_UP, "↑"},
	{VK_RIGHT, "→"},
	{VK_DOWN, "↓"},
	{VK_INSERT, "Insert"},
	{VK_DELETE, "Delete"},
	{VK_LWIN, "Left Win"},
	{VK_RWIN, "Right Win"},
	{VK_APPS, "Apps"},
	{VK_NUMPAD0, "Num 0"},
	{VK_NUMPAD1, "Num 1"},
	{VK_NUMPAD2, "Num 2"},
	{VK_NUMPAD3, "Num 3"},
	{VK_NUMPAD4, "Num 4"},
	{VK_NUMPAD5, "Num 5"},
	{VK_NUMPAD6, "Num 6"},
	{VK_NUMPAD7, "Num 7"},
	{VK_NUMPAD8, "Num 8"},
	{VK_NUMPAD9, "Num 9"},
	{VK_MULTIPLY, "Num *"},
	{VK_NUMLOCK, "Num Lock"},
	{VK_ADD, "Num +"},
	{VK_SUBTRACT, "Num -"},
	{VK_DECIMAL, "Num ."},
	{VK_DIVIDE, "Num /"},
	{VK_F1, "F1"},
	{VK_F2, "F2"},
	{VK_F3, "F3"},
	{VK_F4, "F4"},
	{VK_F5, "F5"},
	{VK_F6, "F6"},
	{VK_F7, "F7"},
	{VK_F8, "F8"},
	{VK_F9, "F9"},
	{VK_F10, "F10"},
	{VK_F11, "F11"},
	{VK_F12, "F12"},
	{'0', "0"},
	{'1', "1"},
	{'2', "2"},
	{'3', "3"},
	{'4', "4"},
	{'5', "5"},
	{'6', "6"},
	{'7', "7"},
	{'8', "8"},
	{'9', "9"},
	{'A', "A"},
	{'B', "B"},
	{'C', "C"},
	{'D', "D"},
	{'E', "E"},
	{'F', "F"},
	{'G', "G"},
	{'H', "H"},
	{'I', "I"},
	{'J', "J"},
	{'K', "K"},
	{'L', "L"},
	{'M', "M"},
	{'N', "N"},
	{'O', "O"},
	{'P', "P"},
	{'Q', "Q"},
	{'R', "R"},
	{'S', "S"},
	{'T', "T"},
	{'U', "U"},
	{'V', "V"},
	{'W', "W"},
	{'X', "X"},
	{'Y', "Y"},
	{'Z', "Z"},
	{VK_OEM_1, ";"},
	{VK_OEM_2, "/"},
	{VK_OEM_3, "`"},
	{VK_OEM_4, "["},
	{VK_OEM_5, "\\"},
	{VK_OEM_6, "]"},
	{VK_OEM_7, "'"},
	{VK_OEM_COMMA, "," },
	{VK_OEM_PERIOD, "." },
	{ VK_OEM_MINUS , "-"},
	{ VK_OEM_PLUS, "+" },
	{ VK_SNAPSHOT, "Print Screen" },
	{ VK_SCROLL, "Scroll Lock"},
};

QMap<int, QString> SystemInputHook::VkCodeToShortKeyName = {
	{VK_LBUTTON, "┛"},
	{VK_RBUTTON, "┗"},
	{VK_MBUTTON, "0"},
	{VK_BACK, "Backspace"},
	{VK_TAB, "Tab"},
	{VK_RETURN, "En"},
	{VK_LSHIFT, "Shift"},
	{VK_RSHIFT, "Shift"},
	{VK_LCONTROL, "Ctrl"},
	{VK_RCONTROL, "Ctrl"},
	{VK_LMENU, "Alt"},
	{VK_RMENU, "Alt"},
	{VK_PAUSE, "PB"},
	{VK_CAPITAL, "[A]"},
	{VK_ESCAPE, "Esc"},
	{VK_SPACE, "Space"},
	{VK_PRIOR, "PU"},
	{VK_NEXT, "PD"},
	{VK_END, "END"},
	{VK_HOME, "HM"},
	{VK_LEFT, "←"},
	{VK_UP, "↑"},
	{VK_RIGHT, "→"},
	{VK_DOWN, "↓"},
	{VK_INSERT, "INS"},
	{VK_DELETE, "DEL"},
	{VK_LWIN, "Win"},
	{VK_RWIN, "Win"},
	{VK_APPS, "FN"},
	{VK_NUMPAD0, "0"},
	{VK_NUMPAD1, "1"},
	{VK_NUMPAD2, "2"},
	{VK_NUMPAD3, "3"},
	{VK_NUMPAD4, "4"},
	{VK_NUMPAD5, "5"},
	{VK_NUMPAD6, "6"},
	{VK_NUMPAD7, "7"},
	{VK_NUMPAD8, "8"},
	{VK_NUMPAD9, "9"},
	{VK_MULTIPLY, "*"},
	{VK_NUMLOCK, "Num"},
	{VK_ADD, "+"},
	{VK_SUBTRACT, "-"},
	{VK_DECIMAL, "."},
	{VK_DIVIDE, "/"},
	{VK_F1, "F1"},
	{VK_F2, "F2"},
	{VK_F3, "F3"},
	{VK_F4, "F4"},
	{VK_F5, "F5"},
	{VK_F6, "F6"},
	{VK_F7, "F7"},
	{VK_F8, "F8"},
	{VK_F9, "F9"},
	{VK_F10, "F10"},
	{VK_F11, "F11"},
	{VK_F12, "F12"},
	{'0', "0"},
	{'1', "1"},
	{'2', "2"},
	{'3', "3"},
	{'4', "4"},
	{'5', "5"},
	{'6', "6"},
	{'7', "7"},
	{'8', "8"},
	{'9', "9"},
	{'A', "A"},
	{'B', "B"},
	{'C', "C"},
	{'D', "D"},
	{'E', "E"},
	{'F', "F"},
	{'G', "G"},
	{'H', "H"},
	{'I', "I"},
	{'J', "J"},
	{'K', "K"},
	{'L', "L"},
	{'M', "M"},
	{'N', "N"},
	{'O', "O"},
	{'P', "P"},
	{'Q', "Q"},
	{'R', "R"},
	{'S', "S"},
	{'T', "T"},
	{'U', "U"},
	{'V', "V"},
	{'W', "W"},
	{'X', "X"},
	{'Y', "Y"},
	{'Z', "Z"},
	{VK_OEM_1, ";"},
	{VK_OEM_2, "/"},
	{VK_OEM_3, "`"},
	{VK_OEM_4, "["},
	{VK_OEM_5, "\\"},
	{VK_OEM_6, "]"},
	{VK_OEM_7, "'"},
	{VK_OEM_COMMA, "," },
	{VK_OEM_PERIOD, "." },
	{ VK_OEM_MINUS , "-"},
	{ VK_OEM_PLUS, "+" },
	{ VK_SNAPSHOT, "PS" },
	{ VK_SCROLL, "SL"},
};
