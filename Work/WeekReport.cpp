#include "pch.h"
#include "WeekReport.h"

DateInfo WeekReport::GetDateInfo()
{
	time_t now = time(nullptr);
	tm local{};
	localtime_s(&local, &now);

	DateInfo info;

	char buf[32];

	// ---- 中文日期：YYYY年M月D日（UTF-8 硬编码，避免乱码） ----
	sprintf_s(buf, "%d", local.tm_year + 1900);
	std::string cn = buf;

	cn.append("\xE5\xB9\xB4"); // 年

	sprintf_s(buf, "%d", local.tm_mon + 1);
	cn.append(buf);
	cn.append("\xE6\x9C\x88"); // 月

	sprintf_s(buf, "%d", local.tm_mday);
	cn.append(buf);
	cn.append("\xE6\x97\xA5"); // 日

	info.cn = cn;

	// ---- 点分日期：YYYY.M.D ----
	sprintf_s(
		buf,
		"%d.%d.%d",
		local.tm_year + 1900,
		local.tm_mon + 1,
		local.tm_mday);

	info.dot = buf;

	return info;
}

ReportTemplate WeekReport::GetReport()
{

	return m_reportTemplate;
}

ReportTemplate WeekReport::GetTemplate()
{

	return m_reportTemplate;
}

void WeekReport::SaveTemplate()
{

}
