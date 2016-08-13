#include "Include_Def.h"
/*���ٶȼ� ������ �ɼ� ���� �˲�*/
void AngleCalculate(void)
{

  //������AD�ɼ�
  GYRO_Value = (int16)LPLD_ADC_Get(ADC0, AD10);                                             //ADC0  A7 X��

  //ģ����ٶȼ�AD�ɼ�  ��һ��
  ACC_Value = (int16)LPLD_ADC_Get(ADC0, AD8);                                               //ADC0  A8  ZOUT

  //������ٶȼ����
  MMA8451_Value = ( ACC_Value - ACC_OFFSET ) * 0.098;

  //�����Ǽ����
  ENC_03_Value = ( GYRO_Value - GYRO_OFFSET ) * 0.26;

  //������
  Kalman_Filter(MMA8451_Value,ENC_03_Value);

}



/*ֱ������ ���PWM���*/
void AngleControl(void)
{
  if(g_nAngleControlFlag == 0) 
  {
    g_fAngleControlOut = 0;
    return;//��ǰ����������
  }
  
  g_fAngleControlOut = CAR_ANGLE_NOW * ANGLE_CONTROL_P + Angle_dot* ANGLE_CONTROL_D*0.1;
  
  if(g_fAngleControlOut>ANGLE_CONTROL_OUT_MAX) 
    g_fAngleControlOut=ANGLE_CONTROL_OUT_MAX;
  else if(g_fAngleControlOut<ANGLE_CONTROL_OUT_MIN)
    g_fAngleControlOut=ANGLE_CONTROL_OUT_MIN;

}


