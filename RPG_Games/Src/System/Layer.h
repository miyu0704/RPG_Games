#pragma once
#include "Canvas.h"
#include "../Base/Component.h"

#include <unordered_map>
#include <atlimage.h>

constexpr COLORREF LAYER_BACKGROUND = RGB(100, 100, 100);

class Layer : public Singleton<Layer>
{
private:
	Canvas* canvas = Canvas::GetInstance();
	std::unordered_map<const char*, std::vector<Component*>> LayerRenders;
	std::vector<const char*> keyList;

public:
	Layer();
	~Layer();

	// レイヤーの追加.
	void Add(const char* key, int width = WND_W, int height = WND_H);
	
	// レイヤーの削除.
	void Delete(const char* key);

	// 描画コンポーネントの登録
	void RegisterRender(const char* key, Component* render);

	// 描画コンポーネントの登録解除
	void UnRegisterRender(const char* key);
	void UnRegisterRender(const char* key, Component* render);
	void UnRegisterRenderAll();

	// レイヤーの実行
	// TODO：レイヤーの実行を呼び出す
	void Exec();
};