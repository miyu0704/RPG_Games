#pragma once
#include "Window.h"
#include "../Other/Singleton.h"

#include <string>
#include <thread>
#include <semaphore>
#include <unordered_map>

#include <dsound.h>
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "winmm.lib")

namespace sound
{
	// BGM�\����
	struct BGM
	{
	private:
		std::string bgm_path;
	public:
		BGM() = default;
		BGM(std::string path) : bgm_path(path) {};
		~BGM() = default;
		// bgm�p�X�̏o��
		operator std::string()
		{
			return bgm_path;
		}
	};

	// SE�\����
	struct SE
	{
	private:
		std::string se_path;
		short buffer;
		short num = 0;
	public:
		SE() = default;
		SE(std::string path, short _buffer)
		{
			se_path = path;
			buffer = _buffer;
			se_buf.resize(buffer);
		}
		~SE() = default;

		std::vector<LPDIRECTSOUNDBUFFER> se_buf;

		// bgm�p�X�̏o��
		operator std::string()
		{
			return se_path;
		}

		void play()
		{
			HRESULT ret = se_buf[num]->Play(0, 0, 0);
			++num;
			if (num == buffer) num = 0;
		}

		void volume(short vol)
		{
			double db;
			if (vol > 500)		db = 600 * (static_cast<short>(vol - 1000) / 500.0);
			else if (vol > 250) db = 600 * (static_cast<short>(vol - 500) / 250.0) - 600;
			else if (vol > 125) db = 1200 * (static_cast<short>(vol - 250) / 125.0) - 1200;
			else if (vol > 63)	db = 2400 * (static_cast<short>(vol - 125) / 63.0) - 2400;
			else if (vol != 0)	db = 5200 * (static_cast<short>(vol - 63) / 63.0) - 4800;
			else				db = DSBVOLUME_MIN;
			for (auto& buf : se_buf) buf->SetVolume(db);
		}
	};
}

class dSound : public Singleton<dSound>
{
private:
	std::unordered_map<const char*, sound::BGM> bgm;
	std::unordered_map<const char*, sound::SE> se;
	
	// SE�f�[�^����Ɋւ��X���b�h
	std::vector<std::thread*> soundThread;
	std::binary_semaphore se_guard{ 1 };

	LPDIRECTSOUND8      lpDS = NULL;            // DirectSound8
	LPDIRECTSOUNDBUFFER lpPrimary = NULL;       // �v���C�}���T�E���h�o�b�t�@

	// MCI�R�}���h�̍Đ�.
	void MCI(std::string str);
	// �T�E���h�o�b�t�@����.
	void CreateSoundBuffer(LPDIRECTSOUNDBUFFER* dsb, std::string file);

public:
	dSound();
	~dSound();

	// BGM�f�[�^�̒ǉ�.
	void AddBGM(std::string path, const char* name);
	// SE�f�[�^�̒ǉ�
	// buffer�F�����Đ��\��
	// �v���FWaitSoundThread()�֐����Ăяo������.
	void AddSE(std::string path, const char* name, short buffer = 20);

	// BGM�f�[�^�̍폜.
	void DeleteBGM(const char* name);
	// SE�f�[�^�̍폜.
	void DeleteSE(const char* name);

	// BGM�f�[�^�̑S�폜.
	void ClearBGM();
	// SE�f�[�^�̑S�폜.
	// �v���FWaitSoundThread()�֐����Ăяo������.
	void ClearSE();

	// �ǉ���BGM�̃Z�b�g.
	void setBGM(const char* name);

	// BGM�Đ�.
	void Play();

	// BGM�ꎞ��~.
	void Pause();

	// BGM��~.
	void Stop();

	// �ǉ���BGM�����
	// ���f�[�^�͏����Ȃ�.
	void Close();

	// BGM���[�v�Đ�.
	void Loop();

	// BGM���ʂ̕ύX.
	void SetVolume(int vol);

	// SE�Đ�.
	void sPlay(const char* name);

	// SE���ʂ̕ύX.
	void sSetVolume(int vol);

	// �T�E���h�f�[�^����X���b�h�ҋ@
	void WaitSoundThread();
};