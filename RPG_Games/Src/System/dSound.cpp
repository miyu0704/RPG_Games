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

	// WAVファイルをロード
	HMMIO hSrc;
	hSrc = mmioOpenA((LPSTR)file.c_str(), NULL, MMIO_ALLOCBUF | MMIO_READ | MMIO_COMPAT);

	// 'WAVE'チャンクチェック
	ZeroMemory(&mSrcWaveFile, sizeof(mSrcWaveFile));
	ret = mmioDescend(hSrc, &mSrcWaveFile, NULL, MMIO_FINDRIFF);

	// 'fmt 'チャンクチェック
	ZeroMemory(&mSrcWaveFmt, sizeof(mSrcWaveFmt));
	ret = mmioDescend(hSrc, &mSrcWaveFmt, &mSrcWaveFile, MMIO_FINDCHUNK);

	// ヘッダサイズの計算
	int iSrcHeaderSize = mSrcWaveFmt.cksize;
	if (iSrcHeaderSize < sizeof(WAVEFORMATEX))
		iSrcHeaderSize = sizeof(WAVEFORMATEX);

	// ヘッダメモリ確保
	wf = (LPWAVEFORMATEX)malloc(iSrcHeaderSize);
	ZeroMemory(wf, iSrcHeaderSize);

	// WAVEフォーマットのロード
	ret = mmioRead(hSrc, (char*)wf, mSrcWaveFmt.cksize);

	// fmtチャンクに戻る
	mmioAscend(hSrc, &mSrcWaveFmt, NULL);

	// dataチャンクを探す
	while (1) {
		// 検索
		if (FAILED(mmioDescend(hSrc, &mSrcWaveData, &mSrcWaveFile, NULL))) {
			free(wf);
			mmioClose(hSrc, NULL);
			return;
		}
		if (mSrcWaveData.ckid == mmioStringToFOURCCA("data", NULL)) break;
		// 次のチャンクへ
		ret = mmioAscend(hSrc, &mSrcWaveData, NULL);
	}

	// サウンドバッファの作成
	DSBUFFERDESC dsdesc;
	ZeroMemory(&dsdesc, sizeof(DSBUFFERDESC));
	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	// dwFlagsについて：
	//  DSBCAPS_GETCURRENTPOSITION2：より正確な再生カーソルを取得
	//	DSBCAPS_STATIC：			 オンボードハードウェアメモリにバッファ
	//  DSBCAPS_LOCDEFER：			 再生時、ソフトウェアリソースにバッファを割り当て
	//	DSBCAPS_CTRLVOLUME：		 音量調整可能
	dsdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_STATIC | DSBCAPS_LOCDEFER | DSBCAPS_CTRLVOLUME;
	dsdesc.dwBufferBytes = mSrcWaveData.cksize;
	dsdesc.lpwfxFormat = wf;
	dsdesc.guid3DAlgorithm = DS3DALG_DEFAULT;
	ret = lpDS->CreateSoundBuffer(&dsdesc, dsb, NULL);

	// ロック
	LPVOID pMem1, pMem2;
	DWORD dwSize1, dwSize2;
	ret = (*dsb)->Lock(NULL, mSrcWaveData.cksize, &pMem1, &dwSize1, &pMem2, &dwSize2, NULL);

	// データ書き込み
	mmioRead(hSrc, (char*)pMem1, dwSize1);
	mmioRead(hSrc, (char*)pMem2, dwSize2);

	// ロック解除
	(*dsb)->Unlock(pMem1, dwSize1, pMem2, dwSize2);

	// ヘッダ用メモリを開放
	free(wf);

	// WAVを閉じる
	mmioClose(hSrc, 0);
}

dSound::dSound()
{
	HRESULT ret;

	// 以下SE再生環境(DirectSound)の準備
	// COMの初期化
	CoInitialize(NULL);

	// DirectSound8を作成
	ret = DirectSoundCreate8(NULL, &lpDS, NULL);

	// 強調モード
	ret = lpDS->SetCooperativeLevel(Window::GetInstance()->getHWND(), DSSCL_EXCLUSIVE | DSSCL_PRIORITY);
	WAVEFORMATEX wf;

	// プライマリサウンドバッファの作成
	DSBUFFERDESC dsdesc;
	ZeroMemory(&dsdesc, sizeof(DSBUFFERDESC));
	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	dsdesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	dsdesc.dwBufferBytes = 0;
	dsdesc.lpwfxFormat = NULL;
	ret = lpDS->CreateSoundBuffer(&dsdesc, &lpPrimary, NULL);

	// プライマリバッファのステータスを決定
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

	// COMの終了
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
			// SEデータの占有
			se_guard.acquire();

			// SEデータの生成.
			se[name] = sound::SE(path, buffer);
			for (auto& data : se[name].se_buf)
			{
				CreateSoundBuffer(&data, se[name]);
			}

			// SEデータの解放
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

			// SEデータの占有
			se_guard.acquire();

			// SEデータの全削除
			for (auto& _se : se) for (auto& data : _se.second.se_buf)
			{
				data->Release();
				data = NULL;
			}
			se.clear();

			// SEデータの解放
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
