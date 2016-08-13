#include "Include_Def.h"

void PIT_Signal(void)
{   
  DisableInterrupts;
  
  //--------------------------------------------------------------------------
  g_nSpeedControlPeriod++;
  SpeedControlOutput();  
  g_nDirectionControlPeriod ++;
  DirectionControlOutput();
  //---------------------------------------------------------------------------  
  g_nCarCount++;//�жϷ���Ƭѡ
  switch(g_nCarCount)
  {
    //---------------------------������0   
  case 1:
   {   
      asm("nop"); 
      
   }; break;
    
     //---------------------------������1   AD�ɼ�                   ��1��1ms  
  case 2:          
   {
      asm("nop");
      AngleCalculate(); 
      g_nDirectionGyro = (int16)LPLD_ADC_Get(ADC0, AD11); //���������ǲɼ�
   }; break;
    
    //----------------------------������2   ֱ������ ���PWM���     ��2��1ms
  case 3:
    { 
       asm("nop");
       AngleControl();
       MotorOutput();
    };  break;
    
    //----------------------------������3    ��ģ�ٶȿ���            ��3��1ms
  case 4:
    {  
       asm("nop");
       g_nSpeedControlCount++;  
      if(g_nSpeedControlCount>=20)        //�����Ƿ�����ٶȸ��»���
      { 
        SpeedControl();
        g_nSpeedControlCount = 0;
        g_nSpeedControlPeriod = 0; 
      }
    };break;
    
    //----------------------------������4    ��ģ�������           ��4��1ms
  case 5:   
    {  
      asm("nop");
      g_nCarCount=0; 
      
      g_nDirectionControlCount ++;
      DirectionVoltageSigma();           //��вɼ����˲�                                             
      
      if( g_nDirectionControlCount >= 2)//�����Ƿ���뷽����»���
       {
          DirectionControl();
          g_nDirectionControlCount = 0;
          g_nDirectionControlPeriod = 0;
       }
    };break;
  }
  
  
  EnableInterrupts;
}