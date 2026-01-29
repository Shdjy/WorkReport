#include "pch.h"
#include "ReportBase.h"

void ReportBase::SetTitle(const std::string& title)
{
	m_title = title;
}

void ReportBase::SetContent(const std::string& content)
{
	m_content = content;
}

std::string ReportBase::GetTimeString()
{
	std::time_t t = std::time(nullptr);
	std::tm tm{};
	localtime_s(&tm, &t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "%H:%M:%S");
	return oss.str();
}

std::string ReportBase::GetDateString()
{
	std::time_t t = std::time(nullptr);
	std::tm tm{};
	localtime_s(&tm, &t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "%Y-%m-%d");
	return oss.str();
}

std::string ReportBase::GetMonthString()
{
	std::time_t t = std::time(nullptr);
	std::tm tm{};
	localtime_s(&tm, &t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "%Y-%m");
	return oss.str();
}
