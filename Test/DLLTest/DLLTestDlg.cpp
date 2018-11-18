
// DLLTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DLLTest.h"
#include "DLLTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int BaudRate[] = { 300,600,1200,2400,4800,9600,14400,19200,38400,56000,57600,115200,230400,460800,921600 };
int ParitySelNum = 5;
CString Parity[] = { _T("None"),_T("Odd"),_T("Even"),_T("Mark"),_T("Space") };
int DataBits[] = { 5,6,7,8 };
int StopBits[] = { 1,2 };

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CDLLTestDlg �Ի���



CDLLTestDlg::CDLLTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLLTEST_DIALOG, pParent)
	, m_strOutput(_T(""))
	, m_strPortNO(_T(""))
	, m_strBaudRate(_T(""))
	, m_strDataBits(_T(""))
	, m_strParity(_T(""))
	, m_strStopBits(_T(""))
	, m_strSend(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hSerialPort = NULL;
	m_pSerialPort = NULL;
	m_strReceive = _T("");
}

CDLLTestDlg::~CDLLTestDlg()
{
	if (m_pSerialPort != NULL)
	{
		delete m_pSerialPort;
		m_pSerialPort = NULL;
	}

	if (m_hSerialPort != NULL)
	{
		AfxFreeLibrary(m_hSerialPort);
		m_hSerialPort = NULL;
	}
}

void CDLLTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_OUTPUT, m_strOutput);
	DDX_Control(pDX, IDC_COM, m_PortNO);
	DDX_CBString(pDX, IDC_COM, m_strPortNO);
	DDX_Control(pDX, IDC_Baudrate, m_BaudRate);
	DDX_CBString(pDX, IDC_Baudrate, m_strBaudRate);
	DDX_Control(pDX, IDC_DataBits, m_DataBits);
	DDX_CBString(pDX, IDC_DataBits, m_strDataBits);
	DDX_Control(pDX, IDC_ParityBits, m_Parity);
	DDX_CBString(pDX, IDC_ParityBits, m_strParity);
	DDX_Control(pDX, IDC_StopBits, m_StopBits);
	DDX_CBString(pDX, IDC_StopBits, m_strStopBits);
	DDX_Text(pDX, IDC_SendEdit, m_strSend);
}

BEGIN_MESSAGE_MAP(CDLLTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, &CDLLTestDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_INIT, &CDLLTestDlg::OnBnClickedBtnInit)
	ON_BN_CLICKED(IDC_BTN_SEND, &CDLLTestDlg::OnBnClickedBtnSend)
	ON_BN_CLICKED(IDC_BTN_SEND2, &CDLLTestDlg::OnBnClickedBtnSend2)
	ON_BN_CLICKED(IDC_SendOrder, &CDLLTestDlg::OnBnClickedSendorder)
END_MESSAGE_MAP()


// CDLLTestDlg ��Ϣ�������

BOOL CDLLTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	Init();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDLLTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDLLTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDLLTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDLLTestDlg::Init()
{
	CString temp;

	//��ʾ������
	for (int i = 0; i < sizeof(BaudRate) / sizeof(int); i++)
	{
		temp.Format("%d", BaudRate[i]);
		m_BaudRate.AddString((LPCTSTR)temp);
	}
	temp.Format("%d", 57600);
	m_BaudRate.SetCurSel(m_BaudRate.FindString(0, temp));

	//��ʾ��żУ��
	for (int i = 0; i < ParitySelNum; i++)
	{
		m_Parity.AddString((LPCTSTR)Parity[i]);
	}
	m_Parity.SetCurSel(m_Parity.FindString(0, _T("None")));

	//��ʾֹͣλ
	for (int i = 0; i < sizeof(StopBits) / sizeof(int); i++)
	{
		temp.Format("%d", StopBits[i]);
		m_StopBits.AddString((LPCTSTR)temp);
	}
	temp.Format("%d", 1);
	m_StopBits.SetCurSel(m_StopBits.FindString(0, (LPCTSTR)temp));

	//��ʾ����λ
	for (int i = 0; i < sizeof(DataBits) / sizeof(int); i++)
	{
		temp.Format("%d", DataBits[i]);
		m_DataBits.AddString((LPCTSTR)temp);
	}
	temp.Format("%d", 8);
	m_DataBits.SetCurSel(m_DataBits.FindString(0, (LPCTSTR)temp));


	if (m_hSerialPort == NULL)
	{
		m_hSerialPort = AfxLoadLibrary(_T("COMTOOL.dll"));
		CreateInterface creater_Motion = (CreateInterface)GetProcAddress(m_hSerialPort, "Create");
		m_pSerialPort = creater_Motion();

	}

	InitForCallBack();
}

bool CDLLTestDlg::InitForCallBack()
{
	SerialPortCallBackParamIn sCallBackParamIn;
	sCallBackParamIn.pThis = this;
	sCallBackParamIn.CallBackSerial = CallBackSerialPort;
	VisionSys_SerialPort handle = VISIONSYS_SERIALPORT_CALLBACK;
	m_pSerialPort->Set(&handle, &sCallBackParamIn,NULL);

	return true;
}

void WINAPI CDLLTestDlg::CallBackSerialPort(void *sCallBackParam)
{
	SerialPortCallBackParamOut *pSerialPortParam = (SerialPortCallBackParamOut *)sCallBackParam;
	CDLLTestDlg *pSerialPort = (CDLLTestDlg *)pSerialPortParam->pThis;
	pSerialPort->OnReceiveChar(pSerialPortParam->RXBuff, NULL);
}

LRESULT CDLLTestDlg::OnReceiveChar(char ch, LPARAM port)
{
	CString strReceive(ch);
	m_strReceive = m_strReceive + strReceive;
	if (m_strReceive.Right(1) == "\n")
	{
		TRACE("Receive Message:%s", m_strReceive);
		m_strOutput = m_strOutput + m_strReceive;
		m_strReceive = "";
	}
	GetDlgItem(IDC_EDIT_OUTPUT)->SetWindowText(m_strOutput);

	if ((((CEdit*)GetDlgItem(IDC_EDIT_OUTPUT))->LineLength()) != 0)
	{
		((CEdit*)GetDlgItem(IDC_EDIT_OUTPUT))->LineScroll(
			m_strOutput.GetLength() / (((CEdit*)GetDlgItem(IDC_EDIT_OUTPUT))->LineLength()));
	}

	return 1;
}

void CDLLTestDlg::OnBnClickedBtnInit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��ʾ��������
	CStringArray m_strArray;
	VisionSys_SerialPort handle = VISIONSYS_SERIALPORT_INIT;
	m_pSerialPort->Set(&handle,&m_strArray);
	for (int i=0;i<m_strArray.GetSize();i++)
	{
		m_PortNO.AddString((LPCTSTR)m_strArray.GetAt(i));
	}
	m_PortNO.SetCurSel(0);

}

void CDLLTestDlg::OnBnClickedBtnOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CStringArray strArrayOpen;
	UpdateData(TRUE);
	strArrayOpen.Add(m_strPortNO);
	strArrayOpen.Add(m_strBaudRate);
	strArrayOpen.Add(m_strDataBits);
	strArrayOpen.Add(m_strParity);
	strArrayOpen.Add(m_strStopBits);
	VisionSys_SerialPort handle = VISIONSYS_SERIALPORT_OPEN;
	m_pSerialPort->Set(&handle, &strArrayOpen);
}


void CDLLTestDlg::OnBnClickedBtnSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	VisionSys_SerialPort handle = VISIONSYS_SERIALPORT_SEND;
	m_pSerialPort->Set(&handle);
}


void CDLLTestDlg::OnBnClickedBtnSend2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	VisionSys_SerialPort handle = VISIONSYS_SERIALPORT_SEND2;
	m_pSerialPort->Set(&handle);
}


void CDLLTestDlg::OnBnClickedSendorder()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString sendOrder;
	UpdateData(true);
	sendOrder = m_strSend;
	VisionSys_SerialPort handle = VISIONSYS_SERIALPORT_SENDORDER;
	m_pSerialPort->Set(&handle,&sendOrder);
}
