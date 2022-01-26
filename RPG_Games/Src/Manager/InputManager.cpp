#include "InputManager.h"

InputManager::InputManager()
{
	// ���ꂼ��̃L�[�̓��͏�ԍ\���̂̍쐬.
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
	// ANY�L�[������ԃ��Z�b�g.
	ANY_PUSH = false;

	for (auto& keystate : keystatus)
	{
		// �O����͏��̍X�V.
		keystate.second.before = keystate.second.now;

		// ANY�L�[�̌��ݓ��͏��X�V�͌�ق�.
		if (keystate.first == Key::KEY_ANY) continue;

		// ���ݓ��͏��̍X�V.
		if (GetAsyncKeyState(keystate.first))
		{
			keystate.second.now = PUSH;
			ANY_PUSH = true;
		}
		else
			keystate.second.now = RELEASE;
	}

	// ANY�L�[�̍X�V.
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
