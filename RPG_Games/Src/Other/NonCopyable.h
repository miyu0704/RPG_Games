#pragma once

class NonCopyable
{
protected:
	NonCopyable() = default;
	virtual ~NonCopyable() = default;

private:
	// コンストラクタ.
	NonCopyable(NonCopyable& Copy) = delete;
	// 演算子のオーバーロード '='.
	void operator=(NonCopyable Copy) = delete;
	
};