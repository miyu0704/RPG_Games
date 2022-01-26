#include "Layer.h"
#include "Error.h"

Layer::Layer()
{
	// ���C���[�̒ǉ��i�ǉ����ɕ`��j.
	Add("Back");		// �w�i�n�iex. �^�C�g���摜, �}�b�v�j
	Add("Object");		// �v���C���[, �����Ă���̂Ȃ�
	Add("UI");			// ���b�Z�[�W�{�b�N�X, HP�o�[�Ȃ�
	Add("System");		// �t�F�[�h, �_�C�A���O�Ȃ�
}

Layer::~Layer()
{
	// vector�̃�������� -> swap�Z�@, shrink_to_fit()�֐�
	// map�̃�������� -> clear()�֐�
	LayerRenders.clear();
	keyList.shrink_to_fit();
}

void Layer::Add(const char* key, int width, int height)
{
	if (LayerRenders.contains(key))
	{
		THROW("layerDC has value");
		return;
	}

	LayerRenders.emplace(key, std::vector<Component*>());
	keyList.push_back(key);
}

void Layer::RegisterRender(const char* key, Component* render)
{
	LayerRenders[key].push_back(render);
}

void Layer::UnRegisterRender(const char* key)
{
	LayerRenders[key].clear();
}

void Layer::UnRegisterRender(const char* key, Component* render)
{
	for (int num = 0; num < LayerRenders[key].size(); ++num)
	{
		if (LayerRenders[key][num] == render) LayerRenders[key].erase(LayerRenders[key].begin() + num);
	}
}

void Layer::UnRegisterRenderAll()
{
	for (auto& key : keyList)
	{
		LayerRenders[key].clear();
	}
}

void Layer::Delete(const char* key)
{
	LayerRenders.erase(key);
}

void Layer::Exec()
{
	for (auto& key : keyList)
	{
		for (auto& render : LayerRenders[key])
		{
			render->Exec();
		}
	}
}
