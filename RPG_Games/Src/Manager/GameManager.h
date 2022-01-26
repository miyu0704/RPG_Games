#pragma once
#include "../Other/Singleton.h"

#include <Windows.h>

class GameManager: public Singleton<GameManager>
{
private:
	class SceneManager* sceneManager;
	class InputManager* inputManager;
	class FrameManager* frameManager;
	class Layer*		layer;

public:
	GameManager();
	~GameManager();

	bool isExit = false;

	// �I������
	void Terminate();

	// �Q�[�����e���s.
	void Exec();

};