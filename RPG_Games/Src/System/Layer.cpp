#include "Layer.h"
#include "Error.h"

Layer::Layer()
{
	// レイヤーの追加（追加順に描画）.
	Add("Back");		// 背景系（ex. タイトル画像, マップ）
	Add("Object");		// プレイヤー, 落ちてるものなど
	Add("UI");			// メッセージボックス, HPバーなど
	Add("System");		// フェード, ダイアログなど
}

Layer::~Layer()
{
	// vectorのメモリ解放 -> swap技法, shrink_to_fit()関数
	// mapのメモリ解放 -> clear()関数
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
