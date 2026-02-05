#pragma once
#include <vector>
#include <curl/curl.h>

class MailSender
{
public:
	MailSender();
	~MailSender();

	void SetServer(const std::string& smtpUrl);
	void SetAccount(const std::string& user, const std::string& password);

	void SetFrom(const std::string& from);
	void AddTo(const std::vector<std::string>& toList);
	void AddCc(const std::vector<std::string>& ccList);

	void SetSubject(const std::string& subject);
	void SetBody(const std::string& body);

	void AddAttachment(const std::string& filePath);

	bool Send(std::string& errMsg);

private:
	void BuildRecipients();
	std::string BuildHeader() const;

private:
	CURL* m_curl;
	curl_slist* m_recipients;
	curl_mime* m_mime;

	std::string m_smtpUrl;
	std::string m_user;
	std::string m_password;
	std::string m_from;

	std::vector<std::string> m_toList;
	std::vector<std::string> m_ccList;
	std::vector<std::string> m_attachList;

	std::string m_subject;
	std::string m_body;
};
