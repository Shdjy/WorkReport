
// WorkDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Work.h"
#include "WorkDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWorkDlg 对话框



CWorkDlg::CWorkDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WORK_DIALOG, pParent)
	, m_reportTitle(_T(""))
	, m_reportBody(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWorkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_reportTitle);
	DDX_Text(pDX, IDC_EDIT2, m_reportBody);
}

BEGIN_MESSAGE_MAP(CWorkDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CWorkDlg::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_MENULOADAY, &CWorkDlg::OnMenuToaday)
	ON_COMMAND(ID_MENUSETDAY, &CWorkDlg::OnMenusetday)
	ON_COMMAND(ID_MENUTODAY, &CWorkDlg::OnMenutoday)
	ON_COMMAND(ID_MENUWEEK, &CWorkDlg::OnMenuweek)
	ON_COMMAND(ID_MENUMONTH, &CWorkDlg::OnMenumonth)
END_MESSAGE_MAP()


// CWorkDlg 消息处理程序

BOOL CWorkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//加载菜单栏
	m_menu.LoadMenu(IDR_MENU1);
	this->SetMenu(&m_menu);
	
	//创建背景画刷
	m_bkBrush.CreateSolidBrush(RGB(255, 192, 203)); // 标准粉色

	m_reportT = std::make_unique<DailyReport>();

	OnMenutoday();//加载今日模板
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWorkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWorkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWorkDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	curl_global_init(CURL_GLOBAL_DEFAULT);
	CURL* curl = curl_easy_init();

	if (curl)
	{
		std::cout << "libcurl 初始化成功" << std::endl;
		curl_easy_cleanup(curl);
	}
	else
	{
		std::cout << "libcurl 初始化失败" << std::endl;
	}

	curl_global_cleanup();
}


std::string CWorkDlg::CStringToString(const CString& str)
{
	//return std::string(str.GetString());
	CStringW wide(str);

	int len = WideCharToMultiByte(
		CP_UTF8,
		0,
		wide,
		-1,
		nullptr,
		0,
		nullptr,
		nullptr);

	std::string utf8(len - 1, '\0');

	WideCharToMultiByte(
		CP_UTF8,
		0,
		wide,
		-1,
		&utf8[0],
		len,
		nullptr,
		nullptr);

	return utf8;

}

CString CWorkDlg::StringToCString(const std::string& str)
{
	//return CString(str.c_str());
	//if (str.empty())
	//{
	//	return CString();
	//}

	//int wideLen = MultiByteToWideChar(
	//	CP_UTF8,
	//	0,
	//	str.c_str(),
	//	-1,
	//	nullptr,
	//	0);

	//if (wideLen <= 0)
	//{
	//	return CString();
	//}

	//CString result;
	//wchar_t* buffer = result.GetBuffer(wideLen - 1);

	//MultiByteToWideChar(
	//	CP_UTF8,
	//	0,
	//	str.c_str(),
	//	-1,
	//	buffer,
	//	wideLen);

	//result.ReleaseBuffer();
	//return result;

	if (str.empty())
	{
		return CString();
	}

	int wideLen = MultiByteToWideChar(
		CP_UTF8,
		0,
		str.c_str(),
		-1,
		nullptr,
		0);

	if (wideLen <= 0)
	{
		return CString();
	}

	CStringW wideStr;
	wchar_t* buffer = wideStr.GetBuffer(wideLen);

	MultiByteToWideChar(
		CP_UTF8,
		0,
		str.c_str(),
		-1,
		buffer,
		wideLen);

	wideStr.ReleaseBuffer();

	// 如果工程是 MBCS，这里会自动转成 CStringA
	return CString(wideStr);
}



HBRUSH CWorkDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_DLG)
	{
		return (HBRUSH)m_bkBrush;
	}
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);           // 背景透明
		pDC->SetTextColor(RGB(0, 0, 0));        // 文字颜色（可选）
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	if (nCtlColor == CTLCOLOR_BTN)
	{
		pDC->SetBkMode(TRANSPARENT);           // 背景透明
		pDC->SetTextColor(RGB(100, 100, 100));        // 文字颜色（可选）
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CWorkDlg::OnMenuToaday()//加载日报模板
{
	// TODO: 在此添加命令处理程序代码
	m_reportT->GetTemplate();
	if (m_reportT->m_isLoadSuccess)
	{
		m_reportTitle = StringToCString(m_reportT->m_reportTemplate.Title);
		m_reportBody = StringToCString(m_reportT->m_reportTemplate.Body);
		UpdateData(FALSE);
	}
}


void CWorkDlg::OnMenusetday()
{
	// TODO: 在此添加命令处理程序代码
	UpdateData(TRUE);
	m_reportT->m_reportTemplate.Title = CStringToString(m_reportTitle);
	m_reportT->m_reportTemplate.Body = CStringToString(m_reportBody);
	m_reportT->SaveTemplate();
}


void CWorkDlg::OnMenutoday()//加载今日模板
{
	// TODO: 在此添加命令处理程序代码
	if (m_reportT->m_isLoadSuccess)
	{
		m_reportT->GetReport();
		m_reportTitle = StringToCString(m_reportT->m_reportTemplate.Title);
		m_reportBody = StringToCString(m_reportT->m_reportTemplate.Body);
		UpdateData(FALSE);
	}
}


void CWorkDlg::OnMenuweek()
{
	// TODO: 在此添加命令处理程序代码
}


void CWorkDlg::OnMenumonth()
{
	// TODO: 在此添加命令处理程序代码
}
