#include "dSound.h"

void dSound::MCI(std::string str)
{
	char buf[256];
	mciGetErrorString(mciSendString(str.c_str(), NULL, 0, NULL), buf, sizeof(buf));
}

void dSound::CreateSoundBuffer(LPDIRECTSOUNDBUFFER* dsb, std::string file)
{
	HRESULT ret;
	MMCKINFO mSrcWaveFile;
	MMCKINFO mSrcWaveFmt;
	MMCKINFO mSrcWaveData;
	LPWAVEFORMATEX wf;

	// WAV�t�@�C�������[�h
	HMMIO hSrc;
	hSrc = mmioOpenA((LPSTR)file.c_str(), NULL, MMIO_ALLOCBUF | MMIO_READ | MMIO_COMPAT);

	// 'WAVE'�`�����N�`�F�b�N
	ZeroMemory(&mSrcWaveFile, sizeof(mSrcWaveFile));
	ret = mmioDescend(hSrc, &mSrcWaveFile, NULL, MMIO_FINDRIFF);

	// 'fmt '�`�����N�`�F�b�N
	ZeroMemory(&mSrcWaveFmt, sizeof(mSrcWaveFmt));
	ret = mmioDescend(hSrc, &mSrcWaveFmt, &mSrcWaveFile, MMIO_FINDCHUNK);

	// �w�b�_�T�C�Y�̌v�Z
	int iSrcHeaderSize = mSrcWaveFmt.cksize;
	if (iSrcHeaderSize < sizeof(WAVEFORMATEX))
		iSrcHeaderSize = sizeof(WAVEFORMATEX);

	// �w�b�_�������m��
	wf = (LPWAVEFORMATEX)malloc(iSrcHeaderSize);
	ZeroMemory(wf, iSrcHeaderSize);

	// WAVE�t�H�[�}�b�g�̃��[�h
	ret = mmioRead(hSrc, (char*)wf, mSrcWaveFmt.cksize);

	// fmt�`�����N�ɖ߂�
	mmioAscend(hSrc, &mSrcWaveFmt, NULL);

	// data�`�����N��T��
	while (1) {
		// ����
		if (FAILED(mmioDescend(hSrc, &mSrcWaveData, &mSrcWaveFile, NULL))) {
			free(wf);
			mmioClose(hSrc, NULL);
			return;
		}
		if (mSrcWaveData.ckid == mmioStringToFOURCCA("data", NULL)) break;
		// ���̃`�����N��
		ret = mmioAscend(hSrc, &mSrcWaveData, NULL);
	}

	// �T�E���h�o�b�t�@�̍쐬
	DSBUFFERDESC dsdesc;
	ZeroMemory(&dsdesc, sizeof(DSBUFFERDESC));
	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	// dwFlags�ɂ��āF
	//  DSBCAPS_GETCURRENTPOSITION2�F��萳�m�ȍĐ��J�[�\�����擾
	//	DSBCAPS_STATIC�F			 �I���{�[�h�n�[�h�E�F�A�������Ƀo�b�t�@
	//  DSBCAPS_LOCDEFER�F			 �Đ����A�\�t�g�E�F�A���\�[�X�Ƀo�b�t�@�����蓖��
	//	DSBCAPS_CTRLVOLUME�F		 ���ʒ����\
	dsdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_STATIC | DSBCAPS_LOCDEFER | DSBCAPS_CTRLVOLUME;
	dsdesc.dwBufferBytes = mSrcWaveData.cksize;
	dsdesc.lpwfxFormat = wf;
	dsdesc.guid3DAlgorithm = DS3DALG_DEFAULT;
	ret = lpDS->CreateSoundBuffer(&dsdesc, dsb, NULL);

	// ���b�N
	LPVOID pMem1, pMem2;
	DWORD dwSize1, dwSize2;
	ret = (*dsb)->Lock(NULL, mSrcWaveData.cksize, &pMem1, &dwSize1, &pMem2, &dwSize2, NULL);

	// �f�[�^��������
	mmioRead(hSrc, (char*)pMem1, dwSize1);
	mmioRead(hSrc, (char*)pMem2, dwSize2);

	// ���b�N����
	(*dsb)->Unlock(pMem1, dwSize1, pMem2, dwSize2);

	// �w�b�_�p���������J��
	free(wf);

	// WAV�����
	mmioClose(hSrc, 0);
}

dSound::dSound()
{
	HRESULT ret;

	// �ȉ�SE�Đ���(DirectSound)�̏���
	// COM�̏�����
	CoInitialize(NULL);

	// DirectSound8���쐬
	ret = DirectSoundCreate8(NULL, &lpDS, NULL);

	// �������[�h
	ret = lpDS->SetCooperativeLevel(Window::GetInstance()->getHWND(), DSSCL_EXCLUSIVE | DSSCL_PRIORITY);
	WAVEFORMATEX wf;

	// �v���C�}���T�E���h�o�b�t�@�̍쐬
	DSBUFFERDESC dsdesc;
	ZeroMemory(&dsdesc, sizeof(DSBUFFERDESC));
	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	dsdesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	dsdesc.dwBufferBytes = 0;
	dsdesc.lpwfxFormat = NULL;
	ret = lpDS->CreateSoundBuffer(&dsdesc, &lpPrimary, NULL);

	// �v���C�}���o�b�t�@�̃X�e�[�^�X������
	wf.cbSize = sizeof(WAVEFORMATEX);
	wf.wFormatTag = WAVE_FORMAT_PCM;
	wf.nChannels = 2;
	wf.nSamplesPerSec = 44100;
	wf.wBitsPerSample = 16;
	wf.nBlockAlign = wf.nChannels * wf.wBitsPerSample / 8;
	wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;
	ret = lpPrimary->SetFormat(&wf);
}

dSound::~dSound()
{
	for (auto& _se : se) for (auto& data : _se.second.se_buf)
	{
		data->Release();
		data = NULL;
	}

	if (lpPrimary) {
		lpPrimary->Release();
		lpPrimary = NULL;
	}

	if (lpDS) {
		lpDS->Release();
		lpDS = NULL;
	}

	// COM�̏I��
	CoUninitialize();

	bgm.clear();
	se.clear();
}

void dSound::AddBGM(std::string path, const char* name)
{
	bgm[name] = path;
}

void dSound::AddSE(std::string path, const char* name, short buffer)
{
	soundThread.push_back(
		new std::thread([&]()
		{
			// SE�f�[�^�̐�L
			se_guard.acquire();

			// SE�f�[�^�̐���.
			se[name] = sound::SE(path, buffer);
			for (auto& data : se[name].se_buf)
			{
				CreateSoundBuffer(&data, se[name]);
			}

			// SE�f�[�^�̉��
			se_guard.release();
		}
		)
	);
}

void dSound::DeleteBGM(const char* name)
{
	bgm.erase(name);
}

void dSound::DeleteSE(const char* name)
{
	for (auto& data : se[name].se_buf)
	{
		data->Release();
		data = NULL;
	}
	se.erase(name);
}

void dSound::ClearBGM()
{
	bgm.clear();
}

void dSound::ClearSE()
{
	soundThread.push_back(
		new std::thread([&]() {

			// SE�f�[�^�̐�L
			se_guard.acquire();

			// SE�f�[�^�̑S�폜
			for (auto& _se : se) for (auto& data : _se.second.se_buf)
			{
				data->Release();
				data = NULL;
			}
			se.clear();

			// SE�f�[�^�̉��
			se_guard.release();
		}
		)
	);
}

void dSound::setBGM(const char* name)
{
	Stop();
	Close();

	std::string bgm_path(bgm[name]);
	std::string str = "open " + bgm_path + " alias BGM";
	MCI(str.c_str());
}

void dSound::Play()
{
	MCI("play BGM");
}

void dSound::Pause()
{
	MCI("pause BGM");
}

void dSound::Stop()
{
	MCI("stop BGM");
}

void dSound::Close()
{
	MCI("close BGM");
}

void dSound::Loop()
{
	char	sMsg[256];
	mciSendString("status BGM mode", sMsg, 255, NULL);

	if (strcmp(sMsg, "stopped") == 0) {
		MCI("seek BGM to start");
		MCI("play BGM notify");
	}
}

void dSound::SetVolume(int vol)
{
	if (vol > 1000) vol = 1000;
	if (vol < 0) vol = 0;

	std::string str = "setaudio BGM volume to " + std::to_string(vol);
	MCI(str.c_str());
}

void dSound::sPlay(const char* name)
{
	se[name].play();
}

void dSound::sSetVolume(int vol)
{
	if (vol > 1000) vol = 1000;
	if (vol < 0) vol = 0;

	for (auto& data : se)
	{
		data.second.volume(vol);
	}
}

void dSound::WaitSoundThread()
{
	for (int num = 0; num < soundThread.size(); ++num)
	{
		soundThread[num]->join();
	}
	soundThread.clear();
}
