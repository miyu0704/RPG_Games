#include "Enemy.h"

Enemy::Enemy()
{
	tileRender = AddComponent<TileRender>();

	// タイル画像情報の定義
	tileRender->SetLayer("Object");		// レイヤー.
	tileRender->SetObject(this);		// 属するオブジェクト.
	tileRender->rect = { 64, 64 };		// レイヤーの幅, 高さ.
	tileRender->hasAlpha = true;		// タイル画像の透過情報の有無.

}

Enemy::~Enemy()
{
}
