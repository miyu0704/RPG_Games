#include "Enemy.h"

Enemy::Enemy()
{
	tileRender = AddComponent<TileRender>();

	// �^�C���摜���̒�`
	tileRender->SetLayer("Object");		// ���C���[.
	tileRender->SetObject(this);		// ������I�u�W�F�N�g.
	tileRender->rect = { 64, 64 };		// ���C���[�̕�, ����.
	tileRender->hasAlpha = true;		// �^�C���摜�̓��ߏ��̗L��.

}

Enemy::~Enemy()
{
}
