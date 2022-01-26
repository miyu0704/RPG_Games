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

	/* TODO�F�Q�[���J�n�O(�^�C�g��������) */
	/* �摜�Ǘ� -> GameObject�̃R���|�[�l���g�ЂƂЂƂ��ێ� */
	/* �V�[�� -> SceneManager����̃V�[���f�[�^�������A�v���C */
	/* �`��V�X�e�� -> ���C���[�ʂɕ`��f�[�^��p�ӂ��ACanvas�N���X���ŏ��ɕ`�� */
	/* ex.�e�L�X�g�f�[�^ -> json�t�@�C������Ǎ�, �t�@�C����std::filesystem��p���� */
}

GameManager::~GameManager()
{
}

void GameManager::Terminate()
{
	// �Q�[�������Ŏg�p�����I�u�W�F�N�g�̔j������
	

	// �Ǘ��N���X
	sceneManager->DestroyInstance();
	inputManager->DestroyInstance();
	frameManager->DestroyInstance();

	// ���g�̔j��
	this->DestroyInstance();
}

// �Q�[�����e���s.
void GameManager::Exec()
{
	// �E�B���h�E�̕\��, �A�N�e�B�u��.
	Window::GetInstance()->Show();
	SetForegroundWindow(Window::GetInstance()->getHWND());

	// �Q�[������.
	while (!isExit)
	{
		if (inputManager->GetKeyDown(KEY_ESCAPE))
		{
			// �E�B���h�E����� -> isExit��true�ɂȂ�
			PostMessage(Window::GetInstance()->getHWND(), WM_CLOSE, NULL, NULL);
		}

		// ���͍X�V.
		inputManager->KeyStateUpdate();

		// �V�[���̍Đ�.
		sceneManager->Exec();

		// �`��o��.
		Window::GetInstance()->DrawOut();

		// �t���[���X�V.
		frameManager->Exec();
	}

	// TODO�FTextLoader�̓����E�쐬
}
