#pragma once
#include "ReportBase.h"
#include "ReportStorage.h"

class ReportManager
{
public:
	bool SaveReport(const std::string& baseDir, ReportBase& report, const std::string& templateKey);

	std::unique_ptr<ReportBase> m_report;
private:
	ReportTemplate m_reportTemplate;
	ReportStorage m_storage;
};

