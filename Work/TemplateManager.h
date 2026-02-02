#pragma once

struct ReportTemplate
{
	std::string Title;
	std::string Body;
};

class TemplateManager
{
public:
	bool Load(const std::string& filePath);
	bool Save(const std::string& filePath) const;

	void SetTemplate(const ReportTemplate& tpl);
	ReportTemplate GetTemplate() const;

private:
	ReportTemplate m_template;
};

