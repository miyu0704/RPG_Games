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
	// BGM構造体
	struct BGM
	{
	private:
		std::string bgm_path;
	public:
		BGM() = default;
		BGM(std::string path) : bgm_path(path) {};
		~BGM() = default;
		// bgmパスの出力
		operator std::string()
		{
			return bgm_path;
		}
	};

	// SE構造体
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

		// bgmパスの出力
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
	
	// SEデータ操作に関わるスレッド
	std::vector<std::thread*> soundThread;
	std::binary_semaphore se_guard{ 1 };

	LPDIRECTSOUND8      lpDS = NULL;            // DirectSound8
	LPDIRECTSOUNDBUFFER lpPrimary = NULL;       // プライマリサウンドバッファ

	// MCIコマンドの再生.
	void MCI(std::string str);
	// サウンドバッファ生成.
	void CreateSoundBuffer(LPDIRECTSOUNDBUFFER* dsb, std::string file);

public:
	dSound();
	~dSound();

	// BGMデータの追加.
	void AddBGM(std::string path, const char* name);
	// SEデータの追加
	// buffer：同時再生可能数
	// 要件：WaitSoundThread()関数を呼び出すこと.
	void AddSE(std::string path, const char* name, short buffer = 20);

	// BGMデータの削除.
	void DeleteBGM(const char* name);
	// SEデータの削除.
	void DeleteSE(const char* name);

	// BGMデータの全削除.
	void ClearBGM();
	// SEデータの全削除.
	// 要件：WaitSoundThread()関数を呼び出すこと.
	void ClearSE();

	// 追加済BGMのセット.
	void setBGM(const char* name);

	// BGM再生.
	void Play();

	// BGM一時停止.
	void Pause();

	// BGM停止.
	void Stop();

	// 追加済BGMを閉じる
	// ※データは消えない.
	void Close();

	// BGMループ再生.
	void Loop();

	// BGM音量の変更.
	void SetVolume(int vol);

	// SE再生.
	void sPlay(const char* name);

	// SE音量の変更.
	void sSetVolume(int vol);

	// サウンドデータ操作スレッド待機
	void WaitSoundThread();
};