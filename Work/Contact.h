#pragma once

#define CONTACTPATH "\\..\\Template\\DilyReport.json"

class Contact
{
public:
	void LoadContact();
	void SaveContact();

private:
	std::map<std::string, std::string> m_contact;
};

