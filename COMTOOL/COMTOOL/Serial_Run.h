/***************************************************************
Copyright (C) 2017 博众精工科技股份有限公司北京研究院 版权所有

文件名：
文件功能描述：

创建者：刘亮 
时间：

修改人：
时间：
修改说明：

版本：V1.0.0
***************************************************************/
#pragma once
#include "BZInterface.h"
#include "FPCSysdefine.h"
#include "SerialPort.h"

class CSerial_Run : public CBZInterface
{
public:
	CSerial_Run();
	~CSerial_Run();
	//bool InitForCallBack();
	//static void WINAPI CallBackSerialPort(void *sCallBackParam);
	int Set(void *pHandle, void *pInputParam, void *pOutputParam);

	CSerialPort m_SerialPort;
	CString	m_strReceive;
	CString *m_pForCOM;

protected:
	void Init(void *pInputParam);
	void Open(void *pInputParam);
	void Send();
	void Send2();
	void SendOrder(void *pInputParam);
	void DllCallBack(void *pInputParam);
	//LRESULT OnReceiveChar(char ch, LPARAM port);
private:

};