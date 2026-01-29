#include "pch.h"
#include "TemplateManager.h"

bool TemplateManager::Load(const std::string& filePath)
{
	std::ifstream ifs(filePath);
	if (!ifs.is_open())
	{
		return false;
	}

	json j;
	ifs >> j;

	m_templates.clear();

	for (auto it = j.begin(); it != j.end(); ++it)
	{
		ReportTemplate tpl;
		tpl.Title = it.value().value("Title", "");
		tpl.Body = it.value().value("Body", "");

		m_templates.emplace(it.key(), tpl);
	}

	return true;
}

bool TemplateManager::Save(const std::string& filePath) const
{
	json j;

	for (const auto& kv : m_templates)
	{
		j[kv.first]["Title"] = kv.second.Title;
		j[kv.first]["Body"] = kv.second.Body;
	}

	std::ofstream ofs(filePath, std::ios::trunc);
	if (!ofs.is_open())
	{
		return false;
	}

	ofs << j.dump(4);
	return true;
}

void TemplateManager::SetTemplate(const std::string& key, const ReportTemplate& tpl)
{
	m_templates[key] = tpl;
}

bool TemplateManager::GetTemplate(const std::string& key, ReportTemplate& out) const
{
	auto it = m_templates.find(key);
	if (it == m_templates.end())
	{
		return false;
	}

	out = it->second;
	return true;
}
