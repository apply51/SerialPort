#ifndef _BZINTERFACE_H_
#define _BZINTERFACE_H_
//回调接口类
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
//接口类
class CBZInterface
{
	//操作
public:
	CBZInterface()
	{
	}
	virtual ~CBZInterface()
	{
	}

	//接口
	virtual int Set(void *pHandle, void *pInputParam=NULL, void *pOutputParam=NULL) = 0;

};

#endif // _BZINTERFACE_H_


extern "C"
{
	__declspec(dllexport) CBZInterface* Create();//对外接口。返回一个类
};

typedef CBZInterface*(*CreateInterface)();//函数指针