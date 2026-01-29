#pragma once
class ReportBase
{
public:
	virtual ~ReportBase() = default;

	void SetTitle(const std::string& title);
	void SetContent(const std::string& content);

	virtual std::string GetPeriodKey() const = 0;
	virtual std::string GetStorageFileName() const = 0;

	nlohmann::json ToJson() const
	{
		nlohmann::json j;
		j["Title"] = m_title;
		j["Content"] = m_content;
		j["Time"] = GetTimeString();
		return j;
	}


	static std::string GetTimeString();
	static std::string GetDateString();
	static std::string GetMonthString();

protected:
	std::string m_title;
	std::string m_content;
};

