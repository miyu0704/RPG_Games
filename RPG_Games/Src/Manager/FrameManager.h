#pragma once
#include "../Other/Singleton.h"
#include <chrono>	// ���Ԋ֌W.

class FrameManager : public Singleton<FrameManager>
{
private:
	std::chrono::system_clock::time_point t1, t2;

public:
	FrameManager();
	~FrameManager() = default;

	void Exec();
};
