#pragma once
#include "NonCopyable.h"
#include <memory>

template <class T>
class Singleton : private NonCopyable
{
private:
	static std::unique_ptr<T> instance;

public:
	Singleton() = default;
	virtual ~Singleton() = default;

	static T* GetInstance()
	{
		if (!instance)
		{
			instance.reset(new T);
		}

		return instance.get();
	}

	static void DestroyInstance()
	{
		if (!instance) return;
		instance.reset(nullptr);
	}
};

// staticêÈåæ. 
template <class T> 
std::unique_ptr<T> Singleton <T>::instance;