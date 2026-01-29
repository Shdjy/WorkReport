#pragma once
#include "ReportBase.h"
class DailyReport :
    public ReportBase
{
	std::string GetPeriodKey() const override
	{
		return GetDateString();   // yyyy-MM-dd
	}

	std::string GetStorageFileName() const override
	{
		return GetMonthString() + ".json"; // yyyy-MM.json
	}
};

