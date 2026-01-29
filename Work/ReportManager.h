#pragma once
#include "ReportBase.h"
#include "ReportStorage.h"
#include "TemplateManager.h"

class ReportManager
{
public:
	bool InitTemplate(const std::string& path);
	
	bool SaveReport(const std::string& baseDir, ReportBase& report, const std::string& templateKey);

private:
	TemplateManager m_templateMgr;
	ReportStorage   m_storage;
};

