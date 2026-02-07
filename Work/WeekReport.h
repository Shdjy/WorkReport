#pragma once
#include "ReportBase.h"

#define  WEEKREPORTPATH "\\..\\Template\\WeekReport.json"

class WeekReport :
    public ReportBase
{

	DateInfo GetDateInfo() override;
	ReportTemplate GetReport() override;
	ReportTemplate GetTemplate() override;
	void SaveTemplate() override;
};

