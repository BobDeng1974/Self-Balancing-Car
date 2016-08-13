#include "Include_Def.h"

void SetMotorVoltage(float fLeftVoltage, float fRightVoltage)
{
  int16 nOut;                         

  if(fLeftVoltage > 0)
  {
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch5, 0);
    nOut = (int)(fLeftVoltage);
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch4, nOut);
  }
  else
  {
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch4, 0);
    fLeftVoltage = -fLeftVoltage;
    nOut = (int)(fLeftVoltage);
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch5, nOut);
  }
  //--------------------------------------------//
  if(fRightVoltage > 0)
  {
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch7, 0);
    nOut = (int)(fRightVoltage);
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch6, nOut);
  }
  else
  {
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch6, 0);
    fRightVoltage = -fRightVoltage;//����ֵ�����ֵ
    nOut = (int)(fRightVoltage);
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch7, nOut);  
  }
}

//--------------------------------------------------------------------------//
void MotorSpeedOut()
{
  float fLeftVal, fRightVal;
  
  fLeftVal  = g_fLeftMotorOut;
  fRightVal = g_fRightMotorOut;
  
  /*������������*/
  if(fLeftVal > 0) 			
    fLeftVal += MOTOR_OUT_L_DEAD_VAL;
  else if(fLeftVal < 0) 		
    fLeftVal -= MOTOR_OUT_L_DEAD_VAL;
  
  if(fRightVal > 0)			
    fRightVal += MOTOR_OUT_R_DEAD_VAL;
  else if(fRightVal < 0)		
    fRightVal -= MOTOR_OUT_R_DEAD_VAL;
  
  /*������ʹ�����ֹ����PWM��Χ*/	
  if(fLeftVal > MOTOR_OUT_MAX)	fLeftVal = MOTOR_OUT_MAX;
  if(fLeftVal < MOTOR_OUT_MIN)	fLeftVal = MOTOR_OUT_MIN;
  
  if(fRightVal > MOTOR_OUT_MAX)	fRightVal = MOTOR_OUT_MAX;
  if(fRightVal < MOTOR_OUT_MIN)	fRightVal = MOTOR_OUT_MIN;
  
   SetMotorVoltage(fLeftVal, fRightVal);
}

/***************************************************************
** ��������: MotorOutput
** ��������: ����������            
** �䡡  ��:   
** �䡡  ��:   
** ��    ע: ��ֱ�����ơ��ٶȿ��ơ�������Ƶ���������е���,����
	     �����������������������������
***************************************************************/
void MotorOutput(void)
{
  //  float fLeft, fRight;
  
  //  fLeft  = g_fAngleControlOut*6-g_fSpeedControlOut - g_fDirectionControlOut;
  //  fRight = g_fAngleControlOut*6-g_fSpeedControlOut + g_fDirectionControlOut;
  
  //--------------------------------------�ǶȻ����---------------------------  
  //  fLeft  = g_fAngleControlOut*6- g_fDirectionControlOut;
  //  fRight = g_fAngleControlOut*6+ g_fDirectionControlOut;
  //--------------------------------------�ǶȻ��ٶȻ��������------------------ 
  //  fLeft  = g_fAngleControlOut*6-g_fSpeedControlOut;
  //  fRight = g_fAngleControlOut*6-g_fSpeedControlOut;
  //  
  float fLeft, fRight;//fAngleAndSpeed
  fAngleAndSpeed = g_fAngleControlOut-g_fSpeedControlOut;
  
 
  if(g_nDirectionPrior==0)// �ٶȡ��Ƕȿ�������
  {
    fLeft  = fAngleAndSpeed - g_fDirectionControlOut;
    fRight = fAngleAndSpeed + g_fDirectionControlOut;
  }
  else if(g_nDirectionPrior==1)// �����������
  {
    
    if((fAngleAndSpeed)>MOTOR_OUT_MAX)
    {
      if(g_fDirectionControlOut>=0)
      {
        fLeft  = MOTOR_OUT_MAX-g_fDirectionControlOut
          +(fAngleAndSpeed-MOTOR_OUT_MAX)/2;
        fRight = MOTOR_OUT_MAX;
      }
      else
      {
        fLeft  = MOTOR_OUT_MAX;
        fRight = MOTOR_OUT_MAX+g_fDirectionControlOut
          +(fAngleAndSpeed-MOTOR_OUT_MAX)/2;
      }
    }
    else
    {
      fLeft  = fAngleAndSpeed	- g_fDirectionControlOut;
      fRight = fAngleAndSpeed	+ g_fDirectionControlOut;
    }
  }

  if(fLeft > MOTOR_OUT_MAX)		fLeft = MOTOR_OUT_MAX;
  if(fLeft < MOTOR_OUT_MIN)		fLeft = MOTOR_OUT_MIN;
  
  if(fRight > MOTOR_OUT_MAX)		fRight = MOTOR_OUT_MAX;
  if(fRight < MOTOR_OUT_MIN)		fRight = MOTOR_OUT_MIN;
  
  g_fLeftMotorOut  = fLeft;
  g_fRightMotorOut = fRight;
  MotorSpeedOut();
}