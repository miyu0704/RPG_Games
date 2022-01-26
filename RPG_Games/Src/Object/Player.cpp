#include "Player.h"

Player::Player()
{
	tileRender = AddComponent<TileRender>();
	tileCollider = AddComponent<TileCollider>();
	text = AddComponent<TextRender>();

	// タイル画像情報の定義
	tileRender->SetLayer("Object");		// レイヤー
	tileRender->SetObject(this);		// 属するオブジェクト
	tileRender->rect = { 32, 64 };		// レイヤーの幅, 高さ
	tileRender->hasAlpha = true;		// タイル画像の透過情報の有無

	// タイル画像読込
	tileRender->ImageLoad("Image/Character/Player.png");

	// コライダー情報の定義
	tileCollider->localPosition.y = 19;
	tileCollider->rect = { 34, 45 };
	tileCollider->SetObject(this);

	// テキスト情報定義
	text->SetLayer("UI");
	text->SetObject(this);
	text->SetFont(8, 16, "851チカラヨワク");
	text->text = "Player";
	text->localPosition = { -10, -15 };
	text->bkColor = RGB(25, 140, 80);

	// プレイヤーの初期位置、大きさ変更
	position = { 64, 64 };
	scale = { 1.2, 1.2 };

	// 入力管理取得
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