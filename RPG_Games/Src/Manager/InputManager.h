#pragma once
#include "../Other/Singleton.h"
#include "../Other/EnumIterator.h"

#include <Windows.h>
#include <unordered_map>

enum Key
{
	KEY_ESCAPE = VK_ESCAPE,
	KEY_RETURN = VK_RETURN,
	KEY_SPACE = VK_SPACE,

	KEY_LSHIFT = VK_LSHIFT,
	KEY_RSHIFT = VK_RSHIFT,
	KEY_LCTRL = VK_LCONTROL,
	KEY_RCTRL = VK_RCONTROL,

	KEY_DOWN = VK_DOWN,
	KEY_UP = VK_UP,
	KEY_RIGHT = VK_RIGHT,
	KEY_LEFT = VK_LEFT,

	KEY_W = 'W',
	KEY_A = 'A',
	KEY_S = 'S',
	KEY_D = 'D',

	KEY_ANY = -1,
};

class InputManager : public Singleton<InputManager>
{
private:
	enum KeyState
	{
		PUSH = 0,
		RELEASE,
	};

	struct KeyStatus
	{
		KeyState now;
		KeyState before;
	};
	std::unordered_map<short, KeyStatus> keystatus;

	bool ANY_PUSH;	/* いずれかのキーが押されているか */

public:
	InputManager();
	~InputManager() = default;

	// キー入力状態更新.
	void KeyStateUpdate();

	// 押されたとき
	bool GetKeyDown(Key keycode);

	// 押されているとき.
	bool GetKey(Key keycode);

	// 離されたとき.
	bool GetKeyUp(Key keycode);
};