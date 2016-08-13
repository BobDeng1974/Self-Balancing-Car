#include "Include_Def.h"

void DirectionControl(void)
 {  
    float fLeftRightAdd, fLeftRightSub,fValue; 
    int16 nLeft, nRight;
    
    //-----------------------�����Ƿ�ʼ����------------------------
    if(g_nDirectionControlFlag == 0) 
     {
        g_fDirectionControlOut = 0;
        g_fDirectionControlOutOld =0;
        g_fDirectionControlOutNew = 0;
        return;//��ǰ����������
     }
    
    //-------------------------AD Handle----------------------------------------
    nLeft = g_nLeftVoltageSigma/4;
    nRight= g_nRightVoltageSigma/4;
    
    g_nLeftVoltageSigma  = 0;
    g_nRightVoltageSigma = 0;
    
    fLeftRightAdd= nLeft+nRight;
    fLeftRightSub= nLeft-nRight;
    
    if( fabs(fLeftRightAdd)<0.00001 )
     {
        fValue=0;
     }else fValue = fLeftRightSub*22/fLeftRightAdd;
    
    //------------------------Dir Handle-----------------------------------------
    g_fDirection = fValue;
    g_fDirectionControlOutOld = g_fDirectionControlOutNew;
    fValue = fabs(fValue);
    //---------------------------------------------------------------------------
    if(fValue<1)
     {
        StraightRoadCount++;
     }
    else StraightRoadCount=0;
    
    
    if(StraightRoadCount > 20){
       
       g_fDirectionControlOutP = g_fDirection*DIR_CONTROL_P*0.7;
       g_fDirectionControlOutD = (g_nDirectionGyro-DIRECTION_OFFSET) * DIR_CONTROL_D*0.7*0.01; 
       g_fDirectionControlOutNew = g_fDirectionControlOutP + g_fDirectionControlOutD;
    }
    else if(fValue<10){
       
       g_fDirectionControlOutP = g_fDirection*DIR_CONTROL_P;
       g_fDirectionControlOutD = (g_nDirectionGyro-DIRECTION_OFFSET) * DIR_CONTROL_D*0.01; 
       g_fDirectionControlOutNew = g_fDirectionControlOutP + g_fDirectionControlOutD;
    }
    else{ 
       
#define     P1   PARA10  //10
#define     P2   PARA11  //΢�� ����б�� 
       
       if( g_fDirection>0 )
          g_fDirectionControlOutP =  P1*g_fDirection*g_fDirection+P2*g_fDirection+600;//���κ���
       else 
          g_fDirectionControlOutP = -P1*g_fDirection*g_fDirection+P2*g_fDirection-600;
       
       g_fDirectionControlOutD = (g_nDirectionGyro-DIRECTION_OFFSET) * DIR_CONTROL_D*0.01; 
       g_fDirectionControlOutNew = g_fDirectionControlOutP + g_fDirectionControlOutD;
    }
    
    
    //=============================================�����޷�=======================================================
    if(g_fDirectionControlOutNew >  6000)  g_fDirectionControlOutNew  =  6000;
    if(g_fDirectionControlOutNew < -6000)  g_fDirectionControlOutNew  = -6000;
    //=============================================================================================================
    
 }

void DirectionControlOutput(void) 
 {
    float fValue;
    fValue = g_fDirectionControlOutNew - g_fDirectionControlOutOld;
      
    g_fDirectionControlOut = fValue * g_nDirectionControlPeriod/ DIRECTION_CONTROL_PERIOD 
       + g_fDirectionControlOutOld;
    
 }

void DirectionVoltageSigma(void) 
 {
    int16 nLeft, nRight;
    
    VOLTAGE_LEFT   = (int16)LPLD_ADC_Get(ADC1, AD14); //���ҵ�вɼ�
    VOLTAGE_RIGHT  = (int16)LPLD_ADC_Get(ADC1, AD15);
    
    if(VOLTAGE_LEFT > OFFSET) 	nLeft  = VOLTAGE_LEFT  -  OFFSET;
    else  nLeft  = 0;
    if(VOLTAGE_RIGHT > OFFSET) 	nRight = VOLTAGE_RIGHT -  OFFSET;
    else  nRight = 0;
    
    g_nLeftVoltageSigma += nLeft;
    g_nRightVoltageSigma += nRight;
 }
