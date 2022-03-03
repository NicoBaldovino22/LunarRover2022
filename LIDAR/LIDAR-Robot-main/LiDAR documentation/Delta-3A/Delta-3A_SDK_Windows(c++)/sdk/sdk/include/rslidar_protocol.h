/*
*  RSLIDAR System
*  Driver Interface
*
*  Copyright 2015 RS Team
*  All rights reserved.
*
*	Author: ruishi, Data:2015-12-25
*
*/


#pragma once

// RP-Lidar Input Packets

#if defined(_WIN32)
#pragma pack(1)
#endif

//added by ruishi
//----------------------------------------
// Commands
//-----------------------------------------
#define COMM_HEAD_FLAGE				0xAA	//Frame header
#define COMM_FRAME_PC_TO_DEV		0x00	//attribute frame
#define COMM_FRAME_DEV_TO_PC		0x40	//command farme
#define COMM_FRAME_ERROR			0x80    //error frame

// MACRO
//-----------------------------------------
#define MAX_SAMPLE_NUMBERS_PER_NOTE		128
#define NUMBER_OF_TEETH					16
#define NOTE_BUFFER_PING				0x00
#define NOTE_BUFFER_PONG				0x01
#define	COMM_MASK						0x3F

/////////////����֡�����ֶ���////////////////////////
typedef enum _cmd_code
{
	CMD_WORK_MODE = 0x01,						//ֹͣ
	CMD_SET_MOTOR_SPEED = 0x04,					//�����״�ת��
	CMD_READ_DEV_VER = 0x0D,					//��ȡ�豸�汾��Ϣ
	CMD_REPORT_DIST = 0x14,						//�״�ɨ�������Ϣ
	CMD_REPORT_DEV_ERROR = 0x16,				//���׹���
}CMD_CODE;

/////////////����֡�궨��////////////////////////
typedef enum _work_mode_
{
	IDEL_MODE = 0x00,
	SLOW_SCAN_MODE = 0x01,
	RAPID_SCAN_MODE = 0x01,//����ֻ��һ��ģʽ
	RESET_MODE = 0x07,
}WORK_MODE;

/////////////�������궨��////////////////////////
typedef enum _running_state
{
	PORT_RDY = 0,
	WORK_WELL,
	RX_DATA_TIMOUT,
	CHKSUM_ERROR,
	MOTOR_STALL,
}RUNNING_STATE;

/////////////ͨ��֡�ṹ////////////////////////////
typedef struct _comm_frame_t
{
	uint8_t		framehead;			//֡ͷ
	uint16_t	frameLen;			//֡����
	uint8_t		protocolver;		//Э��汾
	uint8_t		command;			//������
	uint16_t	paramLen;			//��������
	uint8_t		paramBuf[0];		//����
} __attribute__((packed)) COMM_FRAME_T;

//��ȡ�豸��Ϣ������Ӧ֡�ṹ
typedef struct _lidar_response_devive_info_t {
	_u8		productsn[26];			//��ƷSN
	_u8		softwarever[15];		//����汾
} __attribute__((packed)) LIDAR_RESPONSE_DEV_INFO_T;

//�����״ﵥ�����������Ϣ
typedef struct _lidar_signal_distance_unit_t {
	_u8			signal;	//�Ƕ�ֵ
	float		motorspeed;
	float		angleoffset;
	_u16		angle;			//�Ƕ�
	_u16		distance;	//����ֵ
} __attribute__((packed)) LIDAR_MEASURE_INFO_T;

#if defined(_WIN32)
#pragma pack()
#endif
