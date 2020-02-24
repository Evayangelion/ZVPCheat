
// ZVPCheatDlg.h: 头文件
//

#pragma once


// CZVPCheatDlg 对话框
class CZVPCheatDlg : public CDialogEx
{
// 构造
public:
	CZVPCheatDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZVPCHEAT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedFindme();
private:
	friend DWORD listenerTreadFunc(LPVOID);
	HANDLE m_listenerThread;
	//一击必杀按钮
	CButton m_bnKill;
	// 无限阳光按钮
	CButton m_bnSun;
public:
	afx_msg void OnBnClickedKill();
	afx_msg void OnBnClickedSun();
	
};
