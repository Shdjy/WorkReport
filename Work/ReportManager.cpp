#include "pch.h"
#include "ReportManager.h"

bool ReportManager::InitTemplate(const std::string& path)
{
	return m_templateMgr.Load(path);
}

bool ReportManager::SaveReport(const std::string& baseDir, ReportBase& report, const std::string& templateKey)
{
	//ReportTemplate tpl;
	//if (!m_templateMgr.GetTemplate(templateKey, tpl))
	//{
	//	return false;
	//}

	//report.SetTitle(tpl.Title);
	//report.SetContent(tpl.Body);

	return m_storage.Save(baseDir, report);
}
