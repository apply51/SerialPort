// COMTOOL.h : COMTOOL DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCOMTOOLApp
// �йش���ʵ�ֵ���Ϣ������� COMTOOL.cpp
//

class CCOMTOOLApp : public CWinApp
{
public:
	CCOMTOOLApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
