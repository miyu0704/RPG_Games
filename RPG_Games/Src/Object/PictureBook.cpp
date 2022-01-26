#include "PictureBook.h"

PictureBook::PictureBook()
{
	sprite = AddComponent<SpriteRender>();

	sprite->ImageLoad("Image/UI/picturebook_icon.png");
	sprite->SetLayer("UI");
	sprite->SetObject(this);

	// 位置・大きさの調整
	position = { 100,100 };
}

PictureBook::~PictureBook()
{
}

void PictureBook::Exec()
{
}
