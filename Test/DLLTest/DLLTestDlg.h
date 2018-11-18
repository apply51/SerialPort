
// DLLTestDlg.h : ͷ�ļ�
//

#pragma once
#include "BZInterface.h"
#include "FPCSysdefine.h"
#include "SerialPort.h"
#include "afxwin.h"


// CDLLTestDlg �Ի���
class CDLLTestDlg : public CDialogEx
{
// ����
public:
	CDLLTestDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CDLLTestDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLLTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	HINSTANCE              m_hSerialPort;
	CBZInterface          *m_pSerialPort;
	CString	  m_strReceive;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void Init();
	bool InitForCallBack();
	static void WINAPI CallBackSerialPort(void *sCallBackParam);
	LRESULT OnReceiveChar(char ch, LPARAM port);

	afx_msg void OnBnClickedBtnInit();
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnSend();
	afx_msg void OnBnClickedBtnSend2();
	CString m_strOutput;

	CComboBox m_PortNO;
	CString m_strPortNO;
	CComboBox m_BaudRate;
	CString m_strBaudRate;
	CComboBox m_DataBits;
	CString m_strDataBits;
	CComboBox m_Parity;
	CString m_strParity;
	CComboBox m_StopBits;
	CString m_strStopBits;
	CString m_strSend;
	afx_msg void OnBnClickedSendorder();
};
