
// WorkDlg.h: 头文件
//

#pragma once


// CWorkDlg 对话框
class CWorkDlg : public CDialogEx
{
// 构造
public:
	CWorkDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WORK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString m_reportTitle;
	CString m_reportBody;

	static std::string CStringToString(const CString& str);
	static CString StringToCString(const std::string& str);

private: 
	std::string GetExeFullPath();


	CBrush m_bkBrush;

	ReportTemplate m_reportTemplate;
	TemplateManager m_templateManager;

	std::string m_appPath;

public:
	afx_msg void OnBnClickedButton2();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
