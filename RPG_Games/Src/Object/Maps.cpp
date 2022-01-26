#include "Maps.h"
#include "ShareObject.h"

Maps::Maps()
{
	tileRender = AddComponent<TileRender>();
	jsonloader = AddComponent<jsonLoader>();

	jsonloader->Loadjson("Maps.json");

	tileRender->SetLayer("Back");
	tileRender->SetObject(this);

	player = ShareObject::GetInstance()->FindObject<Player>();
}

void Maps::Load(int mapID)
{
	// マップインデックスの初期化
	tileRender->indices.clear();

	// 読み込み処理
	rapidjson::Value* data = &(jsonloader->doc["Maps"]);
	for (auto& IDs : jsonloader->doc["MapIDs"].GetArray())
	{
		int id = IDs.GetInt();
		if (id == mapID)
		{
			// タイルの幅, 高さ, 一列描画数の取得
			tileRender->rect = { (*data)[id]["rect"]["x"].GetInt(), (*data)[id]["rect"]["y"].GetInt()};
			tileRender->wIndex = (*data)[id]["wIndex"].GetInt();

			// タイル画像の透過情報の有無
			tileRender->hasAlpha = (*data)[id]["alpha"].GetBool();

			// タイル画像の読込
			tileRender->ImageLoad((*data)[id]["source"].GetString());

			// 使用タイルインデックスの読込
			for (int num = 0; num < (*data)[id]["bin"].Size(); ++num)
			{
				tileRender->indices.push_back((*data)[id]["bin"][num].GetInt());
			}

			// 使用タイルイベントの読込.
			for (int num = 0; num < (*data)[id]["event"].Size(); ++num)
			{
				if ((*data)[id]["event"][num].GetInt() == 1)
				{
					collider = AddComponent<TileCollider>();
					collider->rect = tileRender->rect;
					collider->localPosition = { num % tileRender->wIndex * collider->rect.x, num / tileRender->wIndex * collider->rect.y };
					collider->SetObject(this);
					collider->SetTarget<TileCollider>(player);
				}

				
			}
			return;
		}
	}
	THROW("Not Found mapID");
}

void Maps::Exec()
{
	for (auto& pCollider : *GetComponents<TileCollider>())
	{
		collider = static_cast<TileCollider*>(pCollider.get());
		collider->Exec();
		if (collider->GetHit())
		{
			player->position = player->oldPosition;
			return;
		}
	}
}
