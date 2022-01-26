#pragma once
#include "../Base/GameObject.h"
#include "../Component/SpriteRender.h"
#include "../Manager/SceneManager.h"

#include "../System/dSound.h"

template<class _nextScene>
class FadeObject : public GameObject
{
private:
	class SpriteRender* fadeRender;
	short alpha = 0;
	BYTE speed = 3;
	dSound* dsound;
	
	enum Mode
	{
		FADEIN = 0, FADEOUT = 1
	} mode = FADEOUT;

public:
	FadeObject()
	{
		fadeRender = AddComponent<SpriteRender>();

		Gdiplus::Bitmap* bmp = new Gdiplus::Bitmap(WND_W, WND_H);
		HBITMAP hBmp;
		bmp->GetHBITMAP(Gdiplus::Color(0, 0, 0), &hBmp);
		
		fadeRender->AttachBitmap(hBmp);
		fadeRender->SetLayer("System");
		fadeRender->SetObject(this);

		dsound = dSound::GetInstance();
		
		delete(bmp);
	}
	~FadeObject() = default;

	void SetMode(bool isOut, BYTE _alpha = !isOut * 255)
	{
		mode = static_cast<Mode>(isOut);
		alpha = _alpha;
	}

	void SetSpeed(BYTE _speed)
	{
		speed = _speed;
	}

	void Exec() override
	{
		switch (mode)
		{
		case FADEIN:
			alpha -= speed;
			if (alpha < 0)
			{
				alpha = 0;
				mode = FADEOUT;
				isActive = false;
			}
			break;
		case FADEOUT:
			alpha += speed;
			if (alpha > 255)
			{
				alpha = 255;
				mode = FADEIN;
				SceneManager::GetInstance()->ChangeScene<_nextScene>();
			}
			break;
		}
		dsound->SetVolume(1000 - alpha * 4);

		fadeRender->SetAlpha(alpha);
	}
};