#ifndef _FPCSYSDEFINE_H_
#define _FPCSYSDEFINE_H_

struct Spoint
{
    double dCX;
    double dCY;
	
    Spoint(double x = 0, double y = 0)
    {
        dCX = x;
        dCY = y;
    }
    void Clear()
    {
        dCX = 0;
        dCY = 0;
    }
};

typedef enum
{
	VISIONSYS_MOTION_INIT = 1,
	VISIONSYS_MOTION_CLOSE,
	VISIONSYS_MOTION_ORG,
	VISIONSYS_MOTION_P2P,
	VISIONSYS_MOTION_CALL_DLGCONTROLXY,   //liuliang添加
	VISIONSYS_MOTION_AXIS,     //liuliang添加
	VISIONSYS_MOTION_MOVEPATTERN     //liuliang添加
} VisionSys_Motion_T;

typedef enum //liuliang 添加
{
	VISIONSYS_SERIALPORT_INIT = 1,
	VISIONSYS_SERIALPORT_OPEN,
	VISIONSYS_SERIALPORT_SEND,
	VISIONSYS_SERIALPORT_SEND2,
	VISIONSYS_SERIALPORT_SENDORDER,
	VISIONSYS_SERIALPORT_CALLBACK
}VisionSys_SerialPort;

typedef enum 
{
	VISIONSYS_DATAPROCENTER_INIT = 1,
	VISIONSYS_DATAPROCENTER_CLOSE, 
	VISIONSYS_DATAPROCENTER_SETUP,
	VISIONSYS_DATAPROCENTER_INITCALLBACK,
} VisionSys_DataProCenter_T;

typedef enum 
{
	VISIONSYS_CALLBACK_NEWBUFFER = 0
}VisionSys_CallBack_T;

typedef enum 
{
	VISIONSYS_ACQCTRCENTER_INIT = 1,
	VISIONSYS_ACQCTRCENTER_CLOSE, 
	VISIONSYS_ACQCTRCENTER_SETUP,
	VISIONSYS_ACQCTRCENTER_INITCALLBACK,
	VISIONSYS_ACQCTRCENTER_GET_ADDRESS,
	VISIONSYS_ACQCTRCENTER_GET_WIDTH,
	VISIONSYS_ACQCTRCENTER_GET_HEIGHT
} VisionSys_AcqCtrCenter_T;


const int GBMaxFileNameLen = 255;
const int GBMaxTextLen = 255;
//采集回调
typedef struct _GBSignalInfoStruct
{
	PVOID Context;								//存放拥有回调函数的对象的this指针
	int   nErrorCode;								//错误代码（0：正常）
	int   nFrameCount;							//已采集的帧记数
	char  strDescription[GBMaxTextLen];			//描述信息

	int   iReserve1;								// 备用字段1
	int   iReserve2;								// 备用字段2

}s_GBSIGNALINFO;//相机回调信息结构


typedef void (WINAPI *PGBCALLBACK)(const s_GBSIGNALINFO* SignalInfo);//回调函数指针声明

#endif // _FPCSYSDEFINE_H_