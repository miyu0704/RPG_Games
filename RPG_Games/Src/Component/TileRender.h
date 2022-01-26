#pragma once
#include "Render.h"

class TileRender : public Render
{
private:
	CImage base;					// 元画像.
	std::vector<CImage*> tiles;		// タイル画像.
	
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

	int					index = 0;					// 使用タイルインデックス
	std::vector<int>	indices;					// 使用タイルインデックス群

	Vector2				rect{ 0, 0 };				// タイルの幅, 高さ
	bool				hasAlpha = true;			// タイルに透過度があるか
	int					wIndex = 0;					// 一列のタイル描画数

	void ImageLoad(const char* path)
	{
		base.Load(path);

		for (int ref_y = 0; ref_y < base.GetHeight(); ref_y += rect.y)
		{
			for (int ref_x = 0; ref_x < base.GetWidth(); ref_x += rect.x)
			{
				// タイルの空データ作成
				tiles.emplace_back(new CImage);
				tiles.back()->Create(rect.x, rect.y, 32, hasAlpha);

				// 作成した空タイルに、元の画像を切り取って描画
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