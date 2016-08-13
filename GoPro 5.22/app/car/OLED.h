#ifndef _OLED_H_
#define _OLED_H_

#include "common.h"
#include "HW_GPIO.h"
#include "HW_LPTMR.h"

#define LED_SCLH  PTC16_O = 1// ʱ�Ӷ��� 
#define LED_SCLL  PTC16_O = 0

#define LED_SDAH  PTC17_O = 1//���ݿ�D0
#define LED_SDAL  PTC17_O = 0

#define LED_RSTH  PTC18_O = 1//��λ���ܵ�ƽ
#define LED_RSTL  PTC18_O = 0

#define LED_DCH   PTC19_O = 1
#define LED_DCL   PTC19_O = 0//ƫ�ó���


void LED_Init(void);                                                            //��ʼ��
void LED_CLS(void);                                                             //��������
void LED_Set_Pos(uint8 x, uint8 y);                                             //�������꺯��
void LED_WrDat(uint8 data);                                                     //д���ݺ���
void LED_P6x8Char(uint8 x,uint8 y,uint8 ch);                                    //��ʾһ��6x8��׼ASCII�ַ�������48��������ɣ�
void LED_P6x8Str(uint8 x,uint8 y,uint8 ch[]);                                   //д��һ��6x8��׼ASCII�ַ���
void LED_Light(uint8 x,uint8 y,uint8 ch[]);                                     //����һ��6x8��׼ASCII�ַ���
void LED_P8x16Str(uint8 x,uint8 y,uint8 ch[]);
void LED_P14x16Str(uint8 x,uint8 y,uint8 ch[]);                                  //
void LED_PXx16MixStr(uint8 x, uint8 y, uint8 ch[]);
void LED_PrintBMP(uint8 x0,uint8 y0,uint8 x1,uint8 y1,uint8 bmp[]);
void LED_Fill(uint8 dat);                                                       //������Ļд��
void LED_PrintValueC(uint8 x, uint8 y,int8 data);                               //��һ��char����ת����3λ��������ʾ
void LED_PrintValueI(uint8 x, uint8 y, int32 data);
void LED_PrintValueF(uint8 x, uint8 y, float32 data, uint8 num);                //��һ��float����ת������������5λ��С���ͷ��ŵ����ݲ�������ʾ
void LED_PrintEdge(void);
void LED_Cursor(uint8 cursor_column, uint8 cursor_row);
void LED_PrintLine(void);
uint8 Uint_to_S(uint16 data, int8 *p);

void LED_INT_PRINT(uint8 x, uint8 y, uint8 ch[], int32 data);
void LED_FLOAT_PRINT(uint8 x, uint8 y, uint8 ch[], float32 data, uint8 num);
#endif