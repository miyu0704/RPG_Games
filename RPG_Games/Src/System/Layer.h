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

	// ���C���[�̒ǉ�.
	void Add(const char* key, int width = WND_W, int height = WND_H);
	
	// ���C���[�̍폜.
	void Delete(const char* key);

	// �`��R���|�[�l���g�̓o�^
	void RegisterRender(const char* key, Component* render);

	// �`��R���|�[�l���g�̓o�^����
	void UnRegisterRender(const char* key);
	void UnRegisterRender(const char* key, Component* render);
	void UnRegisterRenderAll();

	// ���C���[�̎��s
	// TODO�F���C���[�̎��s���Ăяo��
	void Exec();
};