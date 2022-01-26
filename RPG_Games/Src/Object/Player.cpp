#include "Player.h"

Player::Player()
{
	tileRender = AddComponent<TileRender>();
	tileCollider = AddComponent<TileCollider>();
	text = AddComponent<TextRender>();

	// �^�C���摜���̒�`
	tileRender->SetLayer("Object");		// ���C���[
	tileRender->SetObject(this);		// ������I�u�W�F�N�g
	tileRender->rect = { 32, 64 };		// ���C���[�̕�, ����
	tileRender->hasAlpha = true;		// �^�C���摜�̓��ߏ��̗L��

	// �^�C���摜�Ǎ�
	tileRender->ImageLoad("Image/Character/Player.png");

	// �R���C�_�[���̒�`
	tileCollider->localPosition.y = 19;
	tileCollider->rect = { 34, 45 };
	tileCollider->SetObject(this);

	// �e�L�X�g����`
	text->SetLayer("UI");
	text->SetObject(this);
	text->SetFont(8, 16, "851�`�J�������N");
	text->text = "Player";
	text->localPosition = { -10, -15 };
	text->bkColor = RGB(25, 140, 80);

	// �v���C���[�̏����ʒu�A�傫���ύX
	position = { 64, 64 };
	scale = { 1.2, 1.2 };

	// ���͊Ǘ��擾
	input = InputManager::GetInstance();
}

void Player::Exec()
{
	oldPosition = position;

	if (input->GetKey(KEY_UP))
	{
		position.y -= 3;
		if (position.y < -9) position.y = -9;
		direction = UP;
	}
	if (input->GetKey(KEY_LEFT))
	{
		position.x -= 3;
		if (position.x < 0) position.x = 0;
		direction = LEFT;
	}
	if (input->GetKey(KEY_DOWN))
	{
		position.y += 3;
		if (position.y > WND_H - tileRender->rect.y * scale.y) position.y = WND_H - tileRender->rect.y * scale.y;
		direction = DOWN;
	}
	if (input->GetKey(KEY_RIGHT))
	{
		position.x += 3;
		if (position.x > WND_W - tileRender->rect.x * scale.x) position.x = WND_W - tileRender->rect.x * scale.x;
		direction = RIGHT;
	}

	if (animInterval == 0)
	{
		animIndex += isAddIndex ? 1 : -1;
		if (animIndex == 2) isAddIndex = false;
		if (animIndex == 0) isAddIndex = true;

		animInterval = 15;
	}
	else --animInterval;

	tileRender->index = direction * 3 + animIndex;
}