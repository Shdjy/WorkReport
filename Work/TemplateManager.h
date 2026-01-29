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

	void SetTemplate(const std::string& key, const ReportTemplate& tpl);
	bool GetTemplate(const std::string& key, ReportTemplate& out) const;

private:
	std::unordered_map<std::string, ReportTemplate> m_templates;
};

