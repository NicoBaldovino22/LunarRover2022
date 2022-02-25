#ifndef _LIDAR_H
#define _LIDAR_H

#include <stdint.h>

/********************************************************************************************************************/
//ͨѶ��ز�������
/********************************************************************************************************************/
#define FRAME_HEAD		                        	0xAA                                        //֡ͷ
#define PROTO_VER 	            								0x04                                        //Э��汾                                     
#define PC_TO_LD	    				        					0x00
#define LD_TO_PC						        						0x40
#define P_NONE                                  0xFF

#define FRAME_POINT_NUM_MAX											110
#define ONE_CIRCLE_POINT_NUM_MAX								FRAME_POINT_NUM_MAX*16
/********************************************************************************************************************/
//����궨��
/********************************************************************************************************************/
#define  CMD_SET_WORK_MODE                      0x01	
#define  CMD_ADJ_ROTA_SPEED											0x04
#define  CMD_REPORT_SCAN_INFO										0x14
#define  CMD_REPORT_DEV_ERR_INFO								0x16

//�����״���ָ���
#define  TOOTH_NUM																	16

//�״�ɨ��״̬
enum SCAN_STATE
{
	GRAB_SCAN_FIRST = 0,//���
	GRAB_SCAN_ELSE_DATA //�����
};	
enum SCAN_RESULT
{
	LIDAR_GRAB_ING = 0,
	LIDAR_GRAB_SUCESS,
	LIDAR_GRAB_ERRO,
	LIDAR_GRAB_ELSE
};
//�״﹤��ģʽ
enum WORK_MODE
{
	IDEL = 0,
	_8K_SCAN_MODE=1,
	SYS_RESET
};
//����֡������
enum ERR_CODE{NO_ERR = 0,CMD_ERR,PARAM_LEN_ERR,PARAM_ERR,CHK_ERR};


/********************************************************************************************************************/
//ͨѶ֡����
/********************************************************************************************************************/
#pragma pack (1)
typedef struct
{
	uint8_t Header;
	uint16_t Len;
	uint8_t ProtoVer;
	uint8_t CmdId;
	uint16_t ParamLen;
	uint8_t *Data;
	uint16_t CheckSum;
}T_PROTOCOL;

//����Ϣ����
typedef struct 
{
	float Angle;
	float Distance;
}T_POINT;
//�ϱ�ɨ�������Ϣ֡����
typedef struct 
{
	float RotaSpeed;
	float FrameStartAngle;
	uint8_t PointNum;//һ֡�ĵ���
	T_POINT Point[FRAME_POINT_NUM_MAX];//һ֡ ����Ϣ
}T_FRAME_MEAS_INFO;

//�ϱ��豸������Ϣ֡����
typedef struct 
{
	uint8_t ErrCode;
}T_DEVICE_ERR_INFO;

//�״�ɨ����Ϣ����
typedef struct
{
	uint8_t WorkMode;
	uint8_t State;
	uint8_t Result;
	float LastScanAngle;
	uint8_t ToothCount;
	uint16_t OneCriclePointNum;//һȦ����
	T_FRAME_MEAS_INFO FrameMeasInfo;//һ֡������Ϣ
	T_POINT OneCriclePoint[ONE_CIRCLE_POINT_NUM_MAX];//һȦ��������Ϣ������㿪ʼ����16֡����Ϣ���
}T_LIDARSCANINFO;
#pragma pack ()

extern T_LIDARSCANINFO lidarscaninfo;

void Lidarscaninfo_Init(void);
uint8_t P_Cmd_Process(void);
uint16_t Big2LittleEndian_u16(uint16_t dat);


#endif
