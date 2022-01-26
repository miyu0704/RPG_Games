#pragma once
#include "Render.h"
#include <string>

class TextRender : public Render
{
private:
	HFONT hFont;

	void Render_Exec() override
	{
		SelectObject(canvasDC, hFont);

		SetTextColor(canvasDC, txColor);
		SetBkColor(canvasDC, bkColor);
		SetBkMode(canvasDC, bkMode);

		TextOut(canvasDC, position->x + localPosition.x, position->y + localPosition.y, text.c_str(), text.size());
	}

public:
	TextRender() = default;
	~TextRender()
	{
		// フォントデータの削除.
		DeleteObject(hFont);

		// テキストのデータ解放.
		text.shrink_to_fit();
	}

	std::string text;
	COLORREF txColor = 0;					// デフォルト色は黒
	int bkMode = TRANSPARENT;				// デフォルトモードは透過
	COLORREF bkColor = RGB(0, 255, 0);		// デフォルト色は青

	void SetFont(int w, int h, const char* fontName)
	{
		DeleteObject(hFont);
		hFont = CreateFont(
			h,							//フォント高さ
			w,							//文字幅
			0,							//テキストの角度
			0,							//ベースラインとｘ軸との角度
			FW_REGULAR,					//フォントの重さ（太さ）
			FALSE,						//イタリック体
			FALSE,						//アンダーライン
			FALSE,						//打ち消し線
			SHIFTJIS_CHARSET,			//文字セット
			OUT_DEFAULT_PRECIS,			//出力精度
			CLIP_DEFAULT_PRECIS,		//クリッピング精度
			PROOF_QUALITY,				//出力品質
			FIXED_PITCH | FF_MODERN,	//ピッチとファミリー
			fontName					//書体名
		);
	}
};

/*
		txtrendr = AddComponent<TextRender>();
		txtrendr->text = "ABC";
		txtrendr->SetLayer(Layer::GetInstance()->Get("Back"));
		txtrendr->SetObject(this);
		txtrendr->SetFont(20, 30, "07あかずきんポップ Heavy");*/