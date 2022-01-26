#pragma once
#include "Render.h"
#include <atlimage.h>

class SpriteRender : public Render
{
private:
	CImage image;
	BYTE alpha = 255;

	void Render_Exec() override
	{
		image.AlphaBlend(canvasDC, position->x + localPosition.x, position->y + localPosition.y, image.GetWidth() * scale->x * localScale.x, image.GetHeight() * scale->y * localScale.y, 0, 0, image.GetWidth(), image.GetHeight(), alpha);
	}

public:
	SpriteRender() = default;

	~SpriteRender()
	{
		image.Destroy();
	}

	void ImageLoad(const char* fileName)
	{
		image.Load(fileName);
	}

	void AttachBitmap(HBITMAP bmp)
	{
		image.Attach(bmp);
	}

	void SetAlpha(BYTE _alpha)
	{
		alpha = _alpha;
	}
};