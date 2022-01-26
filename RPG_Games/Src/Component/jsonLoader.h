#pragma once
#include "../Base/Component.h"

#include <document.h>
#include <istreamwrapper.h>
#include <fstream>

class jsonLoader : public Component
{
private:

public:
	jsonLoader() = default;
	~jsonLoader() = default;

	rapidjson::Document doc;

	// ÉfÅ[É^ì«Ç›çûÇ›.
	void Loadjson(const char* path)
	{
		std::ifstream ifs(path);
		rapidjson::IStreamWrapper isw(ifs);
		doc.ParseStream(isw);
	}

	void Exec(){}
};