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
		// �t�H���g�f�[�^�̍폜.
		DeleteObject(hFont);

		// �e�L�X�g�̃f�[�^���.
		text.shrink_to_fit();
	}

	std::string text;
	COLORREF txColor = 0;					// �f�t�H���g�F�͍�
	int bkMode = TRANSPARENT;				// �f�t�H���g���[�h�͓���
	COLORREF bkColor = RGB(0, 255, 0);		// �f�t�H���g�F�͐�

	void SetFont(int w, int h, const char* fontName)
	{
		DeleteObject(hFont);
		hFont = CreateFont(
			h,							//�t�H���g����
			w,							//������
			0,							//�e�L�X�g�̊p�x
			0,							//�x�[�X���C���Ƃ����Ƃ̊p�x
			FW_REGULAR,					//�t�H���g�̏d���i�����j
			FALSE,						//�C�^���b�N��
			FALSE,						//�A���_�[���C��
			FALSE,						//�ł�������
			SHIFTJIS_CHARSET,			//�����Z�b�g
			OUT_DEFAULT_PRECIS,			//�o�͐��x
			CLIP_DEFAULT_PRECIS,		//�N���b�s���O���x
			PROOF_QUALITY,				//�o�͕i��
			FIXED_PITCH | FF_MODERN,	//�s�b�`�ƃt�@�~���[
			fontName					//���̖�
		);
	}
};

/*
		txtrendr = AddComponent<TextRender>();
		txtrendr->text = "ABC";
		txtrendr->SetLayer(Layer::GetInstance()->Get("Back"));
		txtrendr->SetObject(this);
		txtrendr->SetFont(20, 30, "07����������|�b�v Heavy");*/