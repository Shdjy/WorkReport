#include "pch.h"
#include "TemplateManager.h"
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

bool TemplateManager::Load(const std::string& filePath)
{
	std::ifstream ifs(filePath, std::ios::binary);
	if (!ifs.is_open())
	{
		return false;
	}

	std::string content(
		(std::istreambuf_iterator<char>(ifs)),
		std::istreambuf_iterator<char>()
	);

	// È¥µô UTF-8 BOM
	if (content.size() >= 3 &&
		(unsigned char)content[0] == 0xEF &&
		(unsigned char)content[1] == 0xBB &&
		(unsigned char)content[2] == 0xBF)
	{
		content.erase(0, 3);
	}

	json j = json::parse(content, nullptr, false);
	if (j.is_discarded())
	{
		return false;
	}

	m_template.Title = j.value("Title", "");
	m_template.Body = j.value("Body", "");

	return true;
}


bool TemplateManager::Save(const std::string& filePath) const
{
	json j;
	j["Title"] = m_template.Title;
	j["Body"] = m_template.Body;

	std::ofstream ofs(filePath, std::ios::trunc);
	if (!ofs.is_open())
	{
		return false;
	}

	ofs << j.dump(4);
	return true;
}

ReportTemplate TemplateManager::GetTemplate() const
{
	return m_template;
}



void TemplateManager::SetTemplate(const ReportTemplate& tpl)
{
	m_template = tpl;
}
