#include "stdafx.h"
#include "Serial_Run.h"

CBZInterface *Create()
{
	return new CSerial_Run;
}

CSerial_Run::CSerial_Run()
{
	m_strReceive = "";
	m_pForCOM = NULL;
}

CSerial_Run::~CSerial_Run()
{

}

//bool CSerial_Run::InitForCallBack()
//{
//	SerialPortCallBackParamIn sCallBackParamIn;
//	sCallBackParamIn.pThis = this;
//	sCallBackParamIn.CallBackSerial = CallBackSerialPort;
//	m_SerialPort.InitForCallBack(sCallBackParamIn);
//
//	return true;
//}
//
//void WINAPI CSerial_Run::CallBackSerialPort(void *sCallBackParam)
//{
//	SerialPortCallBackParamOut *pSerialPortParam = (SerialPortCallBackParamOut *)sCallBackParam;
//	CSerial_Run *pSerialPort = (CSerial_Run *)pSerialPortParam->pThis;
//	pSerialPort->OnReceiveChar(pSerialPortParam->RXBuff, NULL);
//
//}

int CSerial_Run::Set(void *pHandle, void *pInputParam, void *pOutputParam)
{
	VisionSys_SerialPort *handle = (VisionSys_SerialPort *)pHandle;
	switch (*handle)
	{
	case VISIONSYS_SERIALPORT_INIT:
		Init(pInputParam);
		break;
	case VISIONSYS_SERIALPORT_OPEN:
		Open(pInputParam);
		break;
	case VISIONSYS_SERIALPORT_SEND:
		Send();
		break;
	case VISIONSYS_SERIALPORT_SEND2:
		Send2();
		break;
	case VISIONSYS_SERIALPORT_SENDORDER:
		SendOrder(pInputParam);
		break;
	case VISIONSYS_SERIALPORT_CALLBACK:
		DllCallBack(pInputParam);
		break;
	}

	return 0;
}

void CSerial_Run::Init(void *pInputParam)
{
	CStringArray *m_pTemp = (CStringArray *)pInputParam;
	CString temp;
	for (int i = 1; i <= MaxSerialPortNum - 1; i++)
	{
		if (m_SerialPort.InitPort(NULL, i))
		{
			temp.Format("COM%d", i);
			m_pTemp->Add(temp);
		}
	}
	//m_SerialPort.InitPort(NULL, 3, 57600, 'N', 8, 1, EV_RXCHAR | EV_CTS, 512);
	//InitForCallBack();
}

void CSerial_Run::Open(void *pInputParam)
{
	CStringArray * strArray = (CStringArray*)pInputParam;
	CString PortNO = strArray->GetAt(0);
	CString BaudRate = strArray->GetAt(1);
	CString DataBits = strArray->GetAt(2);
	CString Parity = strArray->GetAt(3);
	CString StopBits = strArray->GetAt(4);
	CString temp;
	temp = PortNO;
	temp.Delete(0, 3);
	int SelPortNO, SelBaudRate, SelDataBits, SelStopBits;
	char SelParity;
	SelPortNO = atoi(temp);
	SelBaudRate = atoi(BaudRate);
	SelDataBits = atoi(DataBits);
	SelParity = Parity.GetAt(0);
	SelStopBits = atoi(StopBits);
	if (m_SerialPort.InitPort(NULL, SelPortNO, SelBaudRate, SelParity, SelDataBits, SelStopBits, EV_RXCHAR | EV_CTS, 512))
	{
		m_SerialPort.StartMonitoring();
	}
	else
		AfxMessageBox("该串口已经被其他应用程序所占用!\n请选择其它的串口");
}

void CSerial_Run::Send()
{
	CString temp = "LMD,SLN,00,1,\r\n";
	m_SerialPort.WriteToPort(temp.GetBuffer(temp.GetLength()), temp.GetLength());
}

void CSerial_Run::Send2()
{
	CString temp = "LMD,SLF,00,1,\r\n";
	m_SerialPort.WriteToPort(temp.GetBuffer(temp.GetLength()), temp.GetLength());
}

void CSerial_Run::SendOrder(void *pInputParam)
{
	CString *temp = (CString*)pInputParam;
	m_SerialPort.WriteToPort(temp->GetBuffer(temp->GetLength()), temp->GetLength());
}

void CSerial_Run::DllCallBack(void *pInputParam)
{
	SerialPortCallBackParamIn *sCallBackParamIn_2 = (SerialPortCallBackParamIn*)pInputParam;
	m_SerialPort.InitForCallBack(*sCallBackParamIn_2);
}

//LRESULT CSerial_Run::OnReceiveChar(char ch, LPARAM port)
//{
//
//	CString strReceive(ch);
//	m_strReceive = m_strReceive + strReceive;
//	if (m_strReceive.Right(1) == "\n")
//	{
//		TRACE("Receive Message:%s", m_strReceive);
//		m_strReceive = "";
//	}
//
//	return 1;
//}
