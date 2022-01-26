#include "FrameManager.h"
#include <string>
#include <Windows.h>

using namespace std::chrono;

FrameManager::FrameManager()
{
	// Œ»İŠÔ‚Ìæ“¾.
	t1 = system_clock::now();
	t2 = t1;
}

void FrameManager::Exec()
{
	do 
	{
		t2 = system_clock::now();
	} while (duration_cast<nanoseconds>(t2 - t1).count() < 1000000000 / 60);

	t1 = t2;
}
