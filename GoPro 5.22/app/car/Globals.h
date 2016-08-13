#ifndef _Globals_H_
#define _Globals_H_

#ifdef CAR_GLOBALS
    #define CAR_EXT
#else
    #define CAR_EXT extern
#endif 


/**************************/
CAR_EXT	float DirOld;
CAR_EXT	float DirNew;
CAR_EXT	float DifferSub;
CAR_EXT	float DifferOutNew;
CAR_EXT	float DifferOutOld;
//-------------------------�������Ʊ�ʶ----------------------------------
CAR_EXT	int g_nCarControlFlag;
CAR_EXT	int g_nAngleControlFlag;
CAR_EXT	int g_nSpeedControlFlag;
CAR_EXT	int g_nDirectionControlFlag;


//------------------------ѭ������----------------------------------
CAR_EXT int g_nCarCount;//1~5�¼�Ƭѡ

CAR_EXT int g_nSpeedControlCount;//�ٶ�PID���¼���  5ms * 20 =100 ms  ����һ�� ������20���Ƕȿ���������
CAR_EXT int g_nSpeedControlPeriod;//ƽ������ٶ�

CAR_EXT int g_nDirectionControlCount;//����PID���¼��� 5ms * 2 =10ms ����һ��
CAR_EXT int g_nDirectionControlPeriod;//ƽ�������ٶ�

CAR_EXT int g_nDirectionPrior;//����������ȿ���
CAR_EXT int StraightRoadCount;
//------------------------ֱ����--------------------------------
CAR_EXT float g_fAngleControlOut;

CAR_EXT float ENC_03_Value;//������ADC0 A7 ���ٶȼ�ADC0 BO
CAR_EXT float MMA8451_Value;
CAR_EXT int16 ACC_Value  ;//���ٶ�AD
CAR_EXT int16 GYRO_Value ;//������AD


//------------------------�ٶȻ�-------------------------------
CAR_EXT int16 g_nLeftMotorPulse,g_nRightMotorPulse;//int16�������

CAR_EXT float g_fCarSpeed;//������ȡ�����ٶ�

CAR_EXT float g_fCarSpeedSet,g_fCarSpeedTarget;

CAR_EXT float g_fSpeedControlOutNew;
CAR_EXT float g_fSpeedControlOutOld;

CAR_EXT float g_fSpeedControlIntegral;

CAR_EXT float g_fSpeedControlOut;

//-------------------------����------------------------------

CAR_EXT int16 VOLTAGE_RIGHT,VOLTAGE_LEFT;      //���ҵ��AD
CAR_EXT int16 DIR_LEFT_OFFSET,DIR_RIGHT_OFFSET;//����AD

CAR_EXT int16 g_nLeftVoltageSigma,g_nRightVoltageSigma;//���2���ۼ�ֵ

CAR_EXT float g_fDirectionControlOutP;
CAR_EXT float g_fDirectionControlOutD;

CAR_EXT float g_fDirectionControlOutOld;
CAR_EXT float g_fDirectionControlOutNew;

CAR_EXT float g_fDirection;   //��й�һ�����ֵ

CAR_EXT int16 g_nDirectionGyro;//������Ʊ仯��

CAR_EXT float g_fDirectionControlOut;

CAR_EXT int16 CurrentDirError;
CAR_EXT float DirDFeedBack,LastDirErr;


CAR_EXT int16 Encoder_Left;
CAR_EXT int16 Encoder_Right; 
CAR_EXT float speed_straight;
//--------------------------------------------------------------
CAR_EXT float fAngleAndSpeed;

CAR_EXT float g_fLeftMotorOut,g_fRightMotorOut;

CAR_EXT int16 GYRO_OFFSET;              //x����������ƫֵ
CAR_EXT int16 ACC_OFFSET ;               //���ٶȼ���ƫֵ
CAR_EXT int16 DIRECTION_OFFSET;           //y����������ƫֵ


#endif