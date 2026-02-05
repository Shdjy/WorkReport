#pragma once
#include "MailSender.h"
#include "TemplateManager.h"

class ReportBase
{
public:
	ReportBase();
	virtual ~ReportBase() = default;

	void SetTitle(const std::string& title);
	void SetContent(const std::string& content);

	virtual DateInfo GetDateInfo() = 0;
	virtual ReportTemplate GetReport() = 0;

	nlohmann::json ToJson() const
	{
		nlohmann::json j;
		j["Title"] = m_title;
		j["Content"] = m_content;
		j["Time"] = GetTimeString();
		return j;
	}


	void ReplaceAll(std::string& text, const std::string& from, const std::string& to);

	static std::string GetTimeString();
	static std::string GetDateString();
	static std::string GetMonthString();
	static std::string GetWeekString();

	MailSender m_sender;
	TemplateManager m_templateManager;
	bool m_isLoadSuccess;


	ReportTemplate m_reportTemplate;
	std::string m_title;
	std::string m_content;
protected:

	
};

