#ifndef _Com_Def_H
#define _Com_Def_H
//---------------------------KALMAN�˲�����-------------------------------
#define Q_angle                0.001        //���ٶȼ��ڽǶ��е����Ŷ�
#define Q_gyro                 0.005        //�������ڽǶ��ش����Ŷ�
#define R_angle                 4           //�������ڽ��ٶ��е����Ŷ�
#define dt                     0.00615      //ʱ���һ��ϵ��

//---------------------------ֱ����---------------------------------------
#define ANGLE_CONTROL_P       PARA1
#define ANGLE_CONTROL_D       PARA2

#define CAR_ANGLE_SET         PARA3
#define CAR_ANGLE_NOW         (Angle - CAR_ANGLE_SET)

#define CAR_STAND_ANGLE_MIN   -2  //Wait Car Stant
#define CAR_STAND_ANGLE_MAX    2

#define CAR_FAILURE_ANGLE_MAX  30
#define CAR_FAILURE_ANGLE_MIN  -30


#define ANGLE_CONTROL_OUT_MAX   8000
#define ANGLE_CONTROL_OUT_MIN  -8000
//-----------------------------�ٶȻ�-------------------------------------

#define SPEED_CONTROL_PERIOD   100 
#define SPEED_CONTROL_P        PARA7
#define SPEED_CONTROL_I        PARA8
#define CarSpeedTarget         PARA9
#define SPEED_CONTROL_D       PARA21


#define CAR_SPEED_CONSTANT   1000.0/100/1024





//-----------------------------����-------------------------------------
#define DIRECTION_CONTROL_PERIOD 20

#define DIR_CONTROL_P   PARA13
#define DIR_CONTROL_D   PARA14

#define OFFSET PARA15


//---------------------------------���ֿ���������--------------------------

//�������//

#define MOTOR_OUT_MAX        10000
#define MOTOR_OUT_MIN       -10000

#define MOTOR_OUT_L_DEAD_VAL  600
#define MOTOR_OUT_R_DEAD_VAL  600


//����
#define KEY1 PTE7_I
#define KEY2 PTE6_I
#define KEY3 PTE5_I
#define KEY4 PTE4_I


#endif