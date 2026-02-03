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

	// 去掉 UTF-8 BOM
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

	DateInfo date = GetTodayDate();

	ReplaceAll(m_template.Title, "{DATE_CN}", date.cn);
	ReplaceAll(m_template.Body, "{DATE_DOT}", date.dot);

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

DateInfo TemplateManager::GetTodayDate()
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



void TemplateManager::ReplaceAll(std::string& text, const std::string& from, const std::string& to)
{
	size_t pos = 0;
	while ((pos = text.find(from, pos)) != std::string::npos)
	{
		text.replace(pos, from.length(), to);
		pos += to.length();
	}
}

void TemplateManager::SetTemplate(const ReportTemplate& tpl)
{
	m_template = tpl;
}
