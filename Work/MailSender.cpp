#include "pch.h"
#include "MailSender.h"
#include <sstream>

MailSender::MailSender()
{
	curl_global_init(CURL_GLOBAL_DEFAULT);
	m_curl = curl_easy_init();
	m_recipients = nullptr;
	m_mime = nullptr;
}

MailSender::~MailSender()
{
	if (m_recipients)
	{
		curl_slist_free_all(m_recipients);
	}

	if (m_mime)
	{
		curl_mime_free(m_mime);
	}

	if (m_curl)
	{
		curl_easy_cleanup(m_curl);
	}

	curl_global_cleanup();
}

void MailSender::SetServer(const std::string& smtpUrl)
{
	m_smtpUrl = smtpUrl;
}

void MailSender::SetAccount(const std::string& user, const std::string& password)
{
	m_user = user;
	m_password = password;
}

void MailSender::SetFrom(const std::string& from)
{
	m_from = from;
}

void MailSender::AddTo(const std::vector<std::string>& toList)
{
	m_toList.insert(m_toList.end(), toList.begin(), toList.end());
}

void MailSender::AddCc(const std::vector<std::string>& ccList)
{
	m_ccList.insert(m_ccList.end(), ccList.begin(), ccList.end());
}

void MailSender::SetSubject(const std::string& subject)
{
	m_subject = subject;
}

void MailSender::SetBody(const std::string& body)
{
	m_body = body;
}

void MailSender::AddAttachment(const std::string& filePath)
{
	m_attachList.push_back(filePath);
}

void MailSender::BuildRecipients()
{
	for (const auto& to : m_toList)
	{
		m_recipients = curl_slist_append(
			m_recipients,
			("<" + to + ">").c_str());
	}

	for (const auto& cc : m_ccList)
	{
		m_recipients = curl_slist_append(
			m_recipients,
			("<" + cc + ">").c_str());
	}
}

std::string MailSender::BuildHeader() const
{
	std::ostringstream oss;

	oss << "From: <" << m_from << ">\r\n";

	if (!m_toList.empty())
	{
		oss << "To: ";
		for (size_t i = 0; i < m_toList.size(); ++i)
		{
			if (i > 0) oss << ", ";
			oss << "<" << m_toList[i] << ">";
		}
		oss << "\r\n";
	}

	if (!m_ccList.empty())
	{
		oss << "Cc: ";
		for (size_t i = 0; i < m_ccList.size(); ++i)
		{
			if (i > 0) oss << ", ";
			oss << "<" << m_ccList[i] << ">";
		}
		oss << "\r\n";
	}

	oss << "Subject: " << m_subject << "\r\n";

	return oss.str();
}

bool MailSender::Send(std::string& errMsg)
{
	if (!m_curl)
	{
		errMsg = "curl init failed";
		return false;
	}

	BuildRecipients();

	curl_easy_setopt(m_curl, CURLOPT_USERNAME, m_user.c_str());
	curl_easy_setopt(m_curl, CURLOPT_PASSWORD, m_password.c_str());
	curl_easy_setopt(m_curl, CURLOPT_URL, m_smtpUrl.c_str());
	curl_easy_setopt(m_curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
	curl_easy_setopt(m_curl, CURLOPT_MAIL_FROM, ("<" + m_from + ">").c_str());
	curl_easy_setopt(m_curl, CURLOPT_MAIL_RCPT, m_recipients);

	m_mime = curl_mime_init(m_curl);

	/* ÕýÎÄ */
	curl_mimepart* part = curl_mime_addpart(m_mime);
	curl_mime_data(part, m_body.c_str(), CURL_ZERO_TERMINATED);
	curl_mime_type(part, "text/plain; charset=utf-8");

	/* ¸½¼þ */
	for (const auto& file : m_attachList)
	{
		curl_mimepart* attach = curl_mime_addpart(m_mime);
		curl_mime_filedata(attach, file.c_str());
		curl_mime_encoder(attach, "base64");
		curl_mime_type(attach, "application/octet-stream");
	}

	curl_easy_setopt(m_curl, CURLOPT_MIMEPOST, m_mime);

	struct curl_slist* headers = nullptr;
	headers = curl_slist_append(headers, BuildHeader().c_str());
	curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, headers);

	CURLcode res = curl_easy_perform(m_curl);

	curl_slist_free_all(headers);

	if (res != CURLE_OK)
	{
		errMsg = curl_easy_strerror(res);
		return false;
	}

	return true;
}

