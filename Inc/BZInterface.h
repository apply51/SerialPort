#ifndef _BZINTERFACE_H_
#define _BZINTERFACE_H_
//�ص��ӿ���
class CCallbackInterface
{
public:

	CCallbackInterface()
	{

	}
	virtual ~CCallbackInterface()
	{

	}

public:
	virtual void Callback(void *pHandle, void *pValue) = 0;
};
//�ӿ���
class CBZInterface
{
	//����
public:
	CBZInterface()
	{
	}
	virtual ~CBZInterface()
	{
	}

	//�ӿ�
	virtual int Set(void *pHandle, void *pInputParam=NULL, void *pOutputParam=NULL) = 0;

};

#endif // _BZINTERFACE_H_


extern "C"
{
	__declspec(dllexport) CBZInterface* Create();//����ӿڡ�����һ����
};

typedef CBZInterface*(*CreateInterface)();//����ָ��