#include "System/Window.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR      lpCmdLine,
	int       nCmdShow
)
{
	MSG msg;				// �E�B���h�E���b�Z�[�W.
	Window::GetInstance();	// �E�B���h�E�̃C���X�^���X����.

	//���b�Z�[�W���[�v�i�E�B���h�E��������܂Ń��[�v).
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		// �E�B���h�E�֐��Ƀ��b�Z�[�W�𑗂�.
		DispatchMessage(&msg);
	}
	
	return 0;
}