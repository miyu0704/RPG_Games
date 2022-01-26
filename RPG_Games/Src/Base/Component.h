#pragma once

class Component
{
protected:

public:
	Component() = default;
	virtual ~Component() = default;

	bool isActive = true;	// アクティブ状態

	// コンポーネント処理実行
	virtual void Exec() abstract;
};