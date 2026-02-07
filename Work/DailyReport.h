#pragma once
#include "ReportBase.h"

#define  DAILYREPORTPATH "\\..\\Template\\DilyReport.json"

class DailyReport :
    public ReportBase
{
public:
    DailyReport();

    DateInfo GetDateInfo() override;
    ReportTemplate GetReport() override;
    ReportTemplate GetTemplate() override;
    void SaveTemplate() override;
};

