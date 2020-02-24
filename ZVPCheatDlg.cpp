
// ZVPCheatDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ZVPCheat.h"
#include "ZVPCheatDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define log(fmt, ...) \
CString str;\
str.Format(CString(fmt),__VA_ARGS__);\
AfxMessageBox(str);

CZVPCheatDlg* g_dlg;
HANDLE g_processHandle;
DWORD listenerTreadFunc(LPVOID lpThreadParameter) {

	while (1) {
		//判断游戏是否打开
		
		//获取窗口句柄
		HWND isGameOpen = FindWindow(_T("MainWindow"), _T("植物大战僵尸中文版"));
		

		//如果没有获取到窗口句柄 说明游戏没有打开
		if (isGameOpen == NULL) {
			//使得按钮不可用
			g_dlg->m_bnKill.EnableWindow(FALSE);
			//重置checkbox状态
			g_dlg->m_bnKill.SetCheck(FALSE);

		}
		else {
			//按钮状态可用
			g_dlg->m_bnKill.EnableWindow(TRUE);

			//获取进程id
			DWORD pid;
			GetWindowThreadProcessId(isGameOpen, &pid);
			//获取进程句柄 
			g_processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
			//至此，进程句柄有了 在实现那里可以使用了
		}
		Sleep(1000);

	}
	return NULL;
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CZVPCheatDlg 对话框



CZVPCheatDlg::CZVPCheatDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ZVPCHEAT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZVPCheatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_KILL, m_bnKill);
}

BEGIN_MESSAGE_MAP(CZVPCheatDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FINDME, &CZVPCheatDlg::OnBnClickedFindme)
	ON_BN_CLICKED(IDC_KILL, &CZVPCheatDlg::OnBnClickedKill)
END_MESSAGE_MAP()


// CZVPCheatDlg 消息处理程序

BOOL CZVPCheatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_listenerThread = CreateThread(NULL, NULL, listenerTreadFunc, NULL, NULL, NULL);

	g_dlg = this;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CZVPCheatDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CZVPCheatDlg::OnPaint()
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
HCURSOR CZVPCheatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CZVPCheatDlg::OnBnClickedFindme()
{
	ShellExecute(NULL, CString("open"), CString("http://49.234.99.58/findme"), NULL, NULL, SW_SHOWNORMAL);

	// TODO: 在此添加控件通知处理程序代码
}


void CZVPCheatDlg::OnBnClickedKill()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bnKill.GetCheck()) {//功能开启
		WriteProcessMemory(g_processHandle);
		log("yeah");
	}
	else {
		log("no");
	}
}
