#pragma once
#include "ReportBase.h"

class ReportStorage
{
public:
	bool Save(const std::string& baseDir, ReportBase& report);
	//static bool Load();
};

