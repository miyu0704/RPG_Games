#include "GameManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "FrameManager.h"

#include "../System/Window.h"

GameManager::GameManager()
{
	sceneManager = SceneManager::GetInstance();
	inputManager = InputManager::GetInstance();
	frameManager = FrameManager::GetInstance();

	layer = Layer::GetInstance();

	/* TODO：ゲーム開始前(タイトル等準備) */
	/* 画像管理 -> GameObjectのコンポーネントひとつひとつが保持 */
	/* シーン -> SceneManagerが一つのシーンデータを持ち、プレイ */
	/* 描画システム -> レイヤー別に描画データを用意し、Canvasクラス内で順に描画 */
	/* ex.テキストデータ -> jsonファイルから読込, ファイルはstd::filesystemを用いる */
}

GameManager::~GameManager()
{
}

void GameManager::Terminate()
{
	// ゲーム処理で使用したオブジェクトの破棄処理
	

	// 管理クラス
	sceneManager->DestroyInstance();
	inputManager->DestroyInstance();
	frameManager->DestroyInstance();

	// 自身の破棄
	this->DestroyInstance();
}

// ゲーム内容実行.
void GameManager::Exec()
{
	// ウィンドウの表示, アクティブ化.
	Window::GetInstance()->Show();
	SetForegroundWindow(Window::GetInstance()->getHWND());

	// ゲーム処理.
	while (!isExit)
	{
		if (inputManager->GetKeyDown(KEY_ESCAPE))
		{
			// ウィンドウを閉じる -> isExitがtrueになる
			PostMessage(Window::GetInstance()->getHWND(), WM_CLOSE, NULL, NULL);
		}

		// 入力更新.
		inputManager->KeyStateUpdate();

		// シーンの再生.
		sceneManager->Exec();

		// 描画出力.
		Window::GetInstance()->DrawOut();

		// フレーム更新.
		frameManager->Exec();
	}

	// TODO：TextLoaderの導入・作成
}
