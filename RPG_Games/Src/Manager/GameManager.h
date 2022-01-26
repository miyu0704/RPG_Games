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

	// 終了処理
	void Terminate();

	// ゲーム内容実行.
	void Exec();

};