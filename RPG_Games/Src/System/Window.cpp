#include "Window.h"
#include "Error.h"
#include "../Manager/GameManager.h"

DWORD WINAPI GameLauncher(LPVOID* data)
{
	GameManager::GetInstance()->Exec();
	return true;
}

// �E�B���h�E�֐�
LRESULT CALLBACK WindowProc(
	HWND hWnd,       // �E�B���h�E�n���h��
	UINT uMsg,       // ���b�Z�[�W�i�L�[�������ꂽ���j
	WPARAM wParam,   // ���b�Z�[�W�ɑΉ��������
	LPARAM lParam)   // ���b�Z�[�W�ɑΉ��������
{
	HDC             hdc;    // �f�o�C�X�R���e�L�X�g�i�ȉ�DC�Əȗ��j
	PAINTSTRUCT     ps;     // �`��\����
	HBITMAP hBMP;			// �r�b�g�}�b�v�n���h��

	Canvas* canvas = Canvas::GetInstance();

	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, 0);

	// �X���b�h�Ǘ��p
	static HANDLE th;
	DWORD result;

	// ���b�Z�[�W(���ꂽ����)�ʂ̏���
	switch (uMsg)
	{
	case WM_CREATE:	// �E�C���h�E���������ꂽ�Ƃ�
		hdc = GetDC(hWnd);										// hdc���擾.

		canvas->hdc = CreateCompatibleDC(hdc);					// HDC���R�s�[.
		hBMP = CreateCompatibleBitmap(hdc, WND_W, WND_H);		// BMP�n���h�����쐬.
		SelectObject(canvas->hdc, hBMP);						// BMP�n���h�������蓖��.
		DeleteObject(hBMP);										// BMP���폜.

		ReleaseDC(hWnd, hdc);									// hdc�����

		// �_�u���o�b�t�@�̍쐬
		canvas->MakeBufferDC();

		// �Q�[���X���b�h�̍쐬
		th = CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(GameLauncher), NULL, NULL, NULL);

		return 0;

	case WM_KEYDOWN:	//�L�[�������ꂽ�Ƃ�
		return 0;

	case WM_PAINT:	// �\�������Ƃ�(�ŏ��̐����ƃE�C���h�E���\�������Ƃ�)

		// �\���J�n.
		hdc = BeginPaint(hWnd, &ps);

		// �\�����e.
		BitBlt(hdc, 0, 0, WND_W, WND_H, canvas->GetBufferDC(), 0, 0, SRCCOPY);

		// �\���I��.
		EndPaint(hWnd, &ps);

		return 0;

	case WM_CLOSE:
		GameManager::GetInstance()->isExit = true;
		while (1) 
		{
				// �X���b�h���I��������`�F�b�N
				GetExitCodeThread(th, &result);

				// �I�������n���h�������
				if (STILL_ACTIVE != result) 
				{
					CloseHandle(th);
					break;
				}
		}
		DestroyWindow(hWnd);
		return 0;

	case WM_DESTROY:	// �E�C���h�E��������Ƃ�
		PostQuitMessage(0);									// �A�v���P�[�V�����̏I��
		Gdiplus::GdiplusShutdown(gdiplusToken);				// GDI+�̏I������
		GameManager::GetInstance()->Terminate();			// �Q�[���̏I��
		return DefWindowProc(hWnd, uMsg, wParam, lParam);	// main�ɕԂ����
	}

	// main�ɕԂ����
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Window::Window()
{
	WNDCLASS wc;				// �E�B���h�N���X�\����

	DWORD	ProcessAffinityMask;// CPU���w��
	HANDLE	hProcess;			// �v���Z�X�n���h��
	DWORD	errnum;				// �֐����A�l
	RECT	rect;				// ��`�\����
	DWORD dwStyle;				// �E�B���h�E�X�^�C��

	// ���g�̃v���Z�X�n���h�����擾
	hProcess = GetCurrentProcess();

	// ���g�𓮍삳����CPU���w�肷��
	ProcessAffinityMask = 1;		//CPU 0���g���i�Q�i���Ŏw��j
	if (!SetProcessAffinityMask(hProcess, ProcessAffinityMask)) {
		errnum = GetLastError();	//�G���[�����擾
		return;
	}

	// �E�B���h�E���̐ݒ�
	wc.style = CS_HREDRAW | CS_VREDRAW;		// �ĕ`��wREDRAW�x
	wc.lpfnWndProc = WindowProc;		    // �E�B���h�E�֐���
	wc.cbClsExtra = 0;						// �g��Ȃ�
	wc.cbWndExtra = 0;						// �g��Ȃ�
	wc.hInstance = NULL;					// �C���X�^���X�ԍ��i�g�p���Ȃ��j
	wc.hIcon = NULL;					    // �A�C�R��(�f�t�H���g)
	wc.hCursor = NULL;						// �J�[�\���i�f�t�H���g�j
	wc.hbrBackground =
		(HBRUSH)COLOR_BACKGROUND + 1;		// �w�i�F
	wc.lpszMenuName = NULL;					// ���j���[���i�����j
	wc.lpszClassName = APP_NAME;		    // �A�v���P�[�V������

	// �E�B���h�E�N���X��windows�ɓo�^
	if (RegisterClass(&wc) == false)
	{
		// ���s�������̃G���[���b�Z�[�W
		ERRMSG("�E�B���h�E�N���X�̓o�^���s", "�G���[���b�Z�[�W");
		return;
	}

	// �����̃v���b�g�̈�ɗ^����ꂽ�T�C�Y�̋�`��`��
	rect.top = 0;		//��
	rect.left = 0;		//��
	rect.right = WND_W;	//�E
	rect.bottom = WND_H;//��

	
	dwStyle = WS_OVERLAPPEDWINDOW;	// �E�B���h�E���

	// AdjustWindowRect((in)�摜�T�C�Y����������`�\����(out), dwStyle(�E�B���h�E�X�^�C��), NULL(���j���[�������ǂ���))
	if (!AdjustWindowRect(&rect, dwStyle, NULL))
	{
		// ���s�������̃G���[���b�Z�[�W
		ERRMSG("�E�B���h�E�̈�̒����Ɏ��s", "�G���[���b�Z�[�W");
		return;
	}
	

	//�E�C���h�E�쐬
	hWnd = CreateWindow(
		APP_NAME,				// �A�v���P�[�V������
		TITLE_NAME,				// �E�B���h�E�^�C�g��
		dwStyle,				// ���ʂ̃E�B���h�E
		120, 45,				// �\������ʒu��xy���W
		rect.right - rect.left,
		rect.bottom - rect.top,	// �E�B���h�E�̕��A����
		NULL,                   // �e�E�B���h�E�̃n�[�h��
		NULL,                   // ���j���[�̐ݒ�i�g�p���Ȃ��j
		NULL,					// �C���X�^���X�ԍ��i�g�p���Ȃ��j
		NULL);                  // �g�p���Ȃ�

	if (hWnd == NULL) {
		ERRMSG("�E�B���h�E�̍쐬���s", "�G���[���b�Z�[�W");
		return;
	}

	// �L�����o�X�̎��̎擾.
	canvas = Canvas::GetInstance();

	// ���C���[�̎��̎擾.
	layer = Layer::GetInstance();
}

Window::~Window()
{
	DeleteObject(hWnd);
}

void Window::Show()
{
	ShowWindow(hWnd, SW_SHOW);
}

void Window::DrawOut()
{
	// ���C���[�̎��s.
	layer->Exec();

	// �o�b�t�@�ɑ��M.
	BitBlt(
		canvas->GetBufferDC(),
		0, 0,
		WND_W, WND_H,
		canvas->hdc,
		0, 0,
		SRCCOPY
	);

	// WM_PAINT���Ăяo��.
	InvalidateRect(hWnd, NULL, FALSE);
}

HWND Window::getHWND()
{
	return hWnd;
}
