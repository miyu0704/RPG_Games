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
	// �}�b�v�C���f�b�N�X�̏�����
	tileRender->indices.clear();

	// �ǂݍ��ݏ���
	rapidjson::Value* data = &(jsonloader->doc["Maps"]);
	for (auto& IDs : jsonloader->doc["MapIDs"].GetArray())
	{
		int id = IDs.GetInt();
		if (id == mapID)
		{
			// �^�C���̕�, ����, ���`�搔�̎擾
			tileRender->rect = { (*data)[id]["rect"]["x"].GetInt(), (*data)[id]["rect"]["y"].GetInt()};
			tileRender->wIndex = (*data)[id]["wIndex"].GetInt();

			// �^�C���摜�̓��ߏ��̗L��
			tileRender->hasAlpha = (*data)[id]["alpha"].GetBool();

			// �^�C���摜�̓Ǎ�
			tileRender->ImageLoad((*data)[id]["source"].GetString());

			// �g�p�^�C���C���f�b�N�X�̓Ǎ�
			for (int num = 0; num < (*data)[id]["bin"].Size(); ++num)
			{
				tileRender->indices.push_back((*data)[id]["bin"][num].GetInt());
			}

			// �g�p�^�C���C�x���g�̓Ǎ�.
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
