#pragma once

struct ReportTemplate
{
	std::string Title;
	std::string Body;
};

struct DateInfo
{
	std::string cn;   // 2026Äê1ÔÂ1ÈÕ
	std::string dot;  // 2026.1.1
};

class TemplateManager
{
public:
	bool Load(const std::string& filePath);
	bool Save(const std::string& filePath) const;

	void SetTemplate(const ReportTemplate& tpl);
	ReportTemplate GetTemplate() const;
	ReportTemplate GetTodayTemplate();
	DateInfo GetTodayDate();
	void ReplaceAll(std::string& text, const std::string& from, const std::string& to);

private:
	ReportTemplate m_template;
};

