#include "InputManager.h"

InputManager::InputManager()
{
	// それぞれのキーの入力状態構造体の作成.
	keystatus.emplace(Key::KEY_ESCAPE, KeyStatus());
	keystatus.emplace(Key::KEY_RETURN, KeyStatus());
	keystatus.emplace(Key::KEY_SPACE,  KeyStatus());
	keystatus.emplace(Key::KEY_LSHIFT, KeyStatus());
	keystatus.emplace(Key::KEY_RSHIFT, KeyStatus());
	keystatus.emplace(Key::KEY_LCTRL,  KeyStatus());
	keystatus.emplace(Key::KEY_RCTRL,  KeyStatus());
	keystatus.emplace(Key::KEY_W,	   KeyStatus());
	keystatus.emplace(Key::KEY_A,	   KeyStatus());
	keystatus.emplace(Key::KEY_S,	   KeyStatus());
	keystatus.emplace(Key::KEY_D,	   KeyStatus());
	keystatus.emplace(Key::KEY_UP,     KeyStatus());
	keystatus.emplace(Key::KEY_DOWN,   KeyStatus());
	keystatus.emplace(Key::KEY_LEFT,   KeyStatus());
	keystatus.emplace(Key::KEY_RIGHT,  KeyStatus());
	keystatus.emplace(Key::KEY_ANY,    KeyStatus());
}

void InputManager::KeyStateUpdate()
{
	// ANYキー押下状態リセット.
	ANY_PUSH = false;

	for (auto& keystate : keystatus)
	{
		// 前回入力情報の更新.
		keystate.second.before = keystate.second.now;

		// ANYキーの現在入力情報更新は後ほど.
		if (keystate.first == Key::KEY_ANY) continue;

		// 現在入力情報の更新.
		if (GetAsyncKeyState(keystate.first))
		{
			keystate.second.now = PUSH;
			ANY_PUSH = true;
		}
		else
			keystate.second.now = RELEASE;
	}

	// ANYキーの更新.
	if (ANY_PUSH) keystatus[Key::KEY_ANY].now = PUSH;
	else		  keystatus[Key::KEY_ANY].now = RELEASE;
}

bool InputManager::GetKeyDown(Key keycode)
{
	return keystatus[keycode].now == PUSH && keystatus[keycode].before == RELEASE ? true : false;
}

bool InputManager::GetKey(Key keycode)
{
	return keystatus[keycode].now == PUSH ? true : false;
}

bool InputManager::GetKeyUp(Key keycode)
{
	return keystatus[keycode].now == RELEASE && keystatus[keycode].before == PUSH ? true : false;
}
