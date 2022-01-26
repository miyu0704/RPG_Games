#pragma once
#include "Render.h"

class TileRender : public Render
{
private:
	CImage base;					// ���摜.
	std::vector<CImage*> tiles;		// �^�C���摜.
	
public:
	TileRender() = default;
	~TileRender()
	{
		base.Destroy();

		for (auto& tile : tiles)
		{
			tile->Destroy();
			delete(tile);
		}
		tiles.shrink_to_fit();
	}

	int					index = 0;					// �g�p�^�C���C���f�b�N�X
	std::vector<int>	indices;					// �g�p�^�C���C���f�b�N�X�Q

	Vector2				rect{ 0, 0 };				// �^�C���̕�, ����
	bool				hasAlpha = true;			// �^�C���ɓ��ߓx�����邩
	int					wIndex = 0;					// ���̃^�C���`�搔

	void ImageLoad(const char* path)
	{
		base.Load(path);

		for (int ref_y = 0; ref_y < base.GetHeight(); ref_y += rect.y)
		{
			for (int ref_x = 0; ref_x < base.GetWidth(); ref_x += rect.x)
			{
				// �^�C���̋�f�[�^�쐬
				tiles.emplace_back(new CImage);
				tiles.back()->Create(rect.x, rect.y, 32, hasAlpha);

				// �쐬������^�C���ɁA���̉摜��؂����ĕ`��
				base.Draw(tiles.back()->GetDC(), 0, 0, rect.x, rect.y, ref_x, ref_y, rect.x, rect.y);
				tiles.back()->ReleaseDC();
			}
		}
	}

	void Render_Exec() override
	{
		if (indices.empty()) tiles[index]->Draw(canvasDC, position->x + localPosition.x, position->y + localPosition.y, rect.x * scale->x * localScale.x, rect.y * scale->y * localScale.y);
		else
		{
			localPosition.x = 0;
			localPosition.y = 0;

			for (int num = 0; num < indices.size(); ++num)
			{
				tiles[indices[num]]->Draw(canvasDC, position->x + localPosition.x, position->y + localPosition.y, rect.x * scale->x * localScale.x, rect.y * scale->y * localScale.y);
				localPosition.x += rect.x;
				if ((num + 1) % wIndex == 0)
				{
					localPosition.x = 0;
					localPosition.y += rect.y;
				}
			}
		}
	}
};