/************************************************************************************
* keyOLED.c
* ����:�˻������������,������OLED���ʹ�á���ʾһЩ��Ҫ�����磺��������������Լ�ccd�Ĳɼ��������
*************************************************************************************/
#include  "Include_def.h"

#define FLASH_LED_SECTOR0   (27)//�˴���ͬ����ȡ��ֵͬ
#define FLASH_LED_ADDR0     ((FLASH_LED_SECTOR0)*2048)

#define FLASH_LED_SECTOR1   (28)
#define FLASH_LED_ADDR1     ((FLASH_LED_SECTOR1)*2048)

#define FLASH_LED_SECTOR2   (29)
#define FLASH_LED_ADDR2     ((FLASH_LED_SECTOR2)*2048)

#define FLASH_LED_SECTOR3   (30)
#define FLASH_LED_ADDR3     ((FLASH_LED_SECTOR3)*2048)

#define FLASH_LED_SECTOR4   (31)
#define FLASH_LED_ADDR4     ((FLASH_LED_SECTOR4)*2048)

#define SHIFT   1  //��λ
#define INC     2  //����
#define DEC     3  //����
#define ENTER   4  //ȷ��
#define	FLASH_READ(sectorNo,offset,type)	(*(type *)((uint32)(((sectorNo)<<11) + (offset))))
int16 PARA1,PARA2,PARA3,PARA4,PARA5,PARA6,PARA7,PARA8,PARA9,PARA10,PARA11,PARA12,PARA13,PARA14,PARA15,PARA16,PARA17,PARA18,PARA19,PARA20,PARA21,PARA22,PARA23,PARA24; 
uint8  Dials;
int8  buf[4];
uint8 Xianbuf0[24];//��ʾ���ַ���Ϊ0��9
typedef union {
	uint8 Byte;
	struct {
        uint8 B0         :1;                                       // Flag Bit 0
        uint8 B1         :1;                                       // Flag Bit 1
        uint8 B2         :1;                                       // Flag Bit 2
        uint8 B3         :1;                                       // Flag Bit 3
        uint8 B4         :1;                                       // Flag Bit 4
        uint8 B5         :1;                                       // Flag Bit 5
        uint8 B6         :1;                                       // Flag Bit 6
        uint8 B7         :1;                                       // Flag Bit 7
	} Bits;
} BYTE;


//���ļ���ʹ�ñ��� 
uint8 San_X,San_Y;   //��˸����λ��
uint8 LEDPage = 1;   //�����ı�ҳ��ֵ����ֵ����Ȼ�����ֵ��ʾҳ�棨�ñ���λ�����������У�
uint8 SetOK = 0, Set_b = 0;    //Set_b KEY4������ʱ����ֵΪ1����������״̬������״̬ʱ�ٰ��˼����˳�����״̬
                               //����ֵ���ó����ڸ���ҳ���Լ����Բ����������л���SetOK����ʵ�ִ˹��ܵ�����
                               //
uint32 FlashWrite_flag=0;
//�ڲ���������
uint8 ScanKey(void);
/*
 *������:void jiao0(int8 *p,uint8 beg,uint8 num) 
 *����  :У�㣬ʹ�����ַ�����ʾλ����ͬ
 *����  :*p ��У׼�ַ���
 *BY    :zf
 */
void jiao0(int8 *p,uint8 beg,uint8 num) 
{
 uint8 i,j;
 for (i=0;i<num-beg;i++)
 {
   for (j=beg+i+1;j>0;j--)
   {
    *(p+j)=*(p+j-1);
   }
    *p='0';
 }
}
/*
 *������:void ShowParameter(int16* para, uint8 LCD_Row, uint8* ParaName) 
 *����  :�����ı��ȫ�ֱ�����ֵ��ʾ��oled�ϣ�ΪXianbuf0����ֵ
 *����  :paraΪ��ӵ�����;LCD_Row��ʾ������;������ʾ������(���8�ַ�)
 *BY    :zf
 */
void ShowParameter(int16* para, uint8 LCD_Row, uint8* ParaName)
{
  uint8 i;
  LED_P6x8Str(4, LCD_Row, ParaName);  //x=1��ʾ������
  i=Uint_to_S((uint16)*para,&buf[0]); 
  jiao0(&buf[0],i,4);
  LED_P6x8Str(90,LCD_Row,(uint8*)&buf[0]);//x=90��ʾ��ֵ
  Xianbuf0[LCD_Row+0]=buf[0];
  Xianbuf0[LCD_Row+6]=buf[1];
  Xianbuf0[LCD_Row+12]=buf[2];
  Xianbuf0[LCD_Row+18]=buf[3];        //�ĸ������趨
}
/*
 *������:void SetParameter(int16 *para, uint8 LCD_Row)
 *����  :���趨���ַ���ת��Ϊȫ�ֱ�����ֵ��int16��
 *����  :*para ȫ�ֱ����ĵ�ַ��LCD_Row����Ѱ���趨���ַ���
 *BY    :zf
 */
void SetParameter(int16 *para, uint8 LCD_Row) 
{
  *para = Xianbuf0[LCD_Row+0]-0x30; 	
  *para = *para * 10+(Xianbuf0[LCD_Row+6]-0x30);
  *para = *para * 10+(Xianbuf0[LCD_Row+12]-0x30);
  *para = *para * 10+(Xianbuf0[LCD_Row+18]-0x30);
}
/*
 *������:void LED_Bei(uint8 x,uint8 y) 
 *����  :��㸲�ǵ�һ���ַ�
 *����  :xΪ��ʾ�ĺ�����0~122��yΪҳ��Χ0��7
 *BY    :zf
 */
void LED_Bei(uint8 x,uint8 y) 
{		//��ʾ���
  uint8 buf[2];
  buf[0]=Xianbuf0[x-90+y];buf[1]='\0';
  LED_Light(x,y,&buf[0]);
}
/* *������:void LED_Clr(uint8 x,uint8 y) 
 *����  :������
 *����  :xΪ��ʾ�ĺ�����0~122��yΪҳ��Χ0��7��chҪ��ʾ���ַ�
 *BY    :zf
 */
void LED_Clr(uint8 x,uint8 y) 
{		//������
  uint8 buf[2];
  buf[0]=Xianbuf0[x-90+y];buf[1]='\0';
  LED_P6x8Str(x,y,&buf[0]);
}
/******************************************************************************/
/****************************4��ҳ�����***************************************/
/******************************************************************************/
/*
 *������:void SetPage1(void)
 *����  :��һ��ҳ�棬������Ӧ��ϵͳ��״̬
 *����  :��
 *BY    :zf
 */
void HOME(void) 
{
  if (Set_b==0)
  {
    LED_CLS(); 
    LED_P6x8Str(5,3,"       SetNeutral?");
  }
  else
  {
    SetOK = 1;
    LED_CLS();
  }
}
/*
 *������:void Angle(void)
 *����  :�ڶ���ҳ�棬�����ı�ֱ��ʱ�ı������Լ�ֱ��ʱ�ı�����ʾ
 */
void Angle_ONE(void)
{    
  uint8 i;
  if (Set_b==0)
  {
    LED_CLS();
    for (i=0;i<24;i++)
      Xianbuf0[i]='\0';
    LED_P8x16Str(25,0,"<<Angle>>");
    ShowParameter(&PARA1, 2, "A_P:");
    ShowParameter(&PARA2, 3, "A_D*0.1:");
    ShowParameter(&PARA3, 4, "CAR_ANGLE_SET:");
    ShowParameter(&PARA4, 5, ":");
    ShowParameter(&PARA5, 6, ":");
    ShowParameter(&PARA6, 7, ":");
    
  }
  else          
  {   
    San_X=90;		
    San_Y=2;  
    LED_Bei(San_X,San_Y);  
    for (;;)
    {
      i = ScanKey();
      switch(i){
      case SHIFT:                            //�ƶ���߶�Ӧ��Ҫ���õı���
        LED_Clr(San_X,San_Y);
        San_X+=6;
        if (San_X>108) 
        {
          San_X=90; 
          San_Y++;
        }
        if (San_Y>7) //���ܵ��������
          San_Y=2;   //����
        LED_Bei(San_X,San_Y); 
        break;
      case INC:                              //�ı�����ָ�������ò�����ֵ0~9
        Xianbuf0[San_X-90+San_Y]++;                                             //�������Ӧ��ֵ
        if (Xianbuf0[San_X-90+San_Y]>0x39)                                      //San_X��LCD_low�ȼ���һ��
          Xianbuf0[San_X-90+San_Y]=0x30;
        buf[0]= Xianbuf0[San_X-90+San_Y];
        buf[1]='\0';
        LED_Bei(San_X,San_Y);
        break;
      case DEC: //��1
        Xianbuf0[San_X-90+San_Y]--;
        if (Xianbuf0[San_X-90+San_Y]<0x30)                
          Xianbuf0[San_X-90+San_Y]=0x39;                
        buf[0]= Xianbuf0[San_X-90+San_Y];
        buf[1]='\0';
        LED_Bei(San_X,San_Y);
        break;
      case ENTER: //ȷ��
        SetParameter(&PARA1, 2);      //�ı��Ӧȫ�ֱ�����ֵ
        SetParameter(&PARA2, 3);      //�ڶ�������Ϊ������
        SetParameter(&PARA3, 4);
        SetParameter(&PARA4, 5);
        SetParameter(&PARA5, 6);
        SetParameter(&PARA6, 7);                  
        
        LPLD_Flash_SectorErase(FLASH_LED_ADDR0);//�������
        
        LPLD_Flash_ByteProgram(FLASH_LED_ADDR0,    (uint32*)&PARA1, 4);//����󱣴�
        LPLD_Flash_ByteProgram(FLASH_LED_ADDR0+32, (uint32*)&PARA2, 4);
        LPLD_Flash_ByteProgram(FLASH_LED_ADDR0+64, (uint32*)&PARA3, 4);
        LPLD_Flash_ByteProgram(FLASH_LED_ADDR0+96, (uint32*)&PARA4, 4);  
        LPLD_Flash_ByteProgram(FLASH_LED_ADDR0+128,(uint32*)&PARA5, 4);
        LPLD_Flash_ByteProgram(FLASH_LED_ADDR0+160,(uint32*)&PARA6, 4); 
        LED_Clr(San_X, San_Y); 
        Set_b=0;   //�˳�����״̬
        return;
        break;
        
      default :  break;
      }
    }
  }
}
/*
 *������:void Speed_ONE(void)
 *����  :ҳ��3�������ı��ܶ�ʱ�ı������Լ��ܶ�ʱ�ı�����ʾ
 */
void Speed_ONE(void)     
{
  uint8 i;
  if (Set_b==0)
  {
    LED_CLS();
    for (i=0;i<24;i++)
      Xianbuf0[i]='\0';
    LED_P8x16Str(20,0,"<<Speed_ONE>>");
    ShowParameter(&PARA7, 2, "S_P/100:");
    ShowParameter(&PARA8, 3, "S_I/100:");
    ShowParameter(&PARA9, 4, "SpeedTarget:");
    ShowParameter(&PARA10,5, "p1:");
    ShowParameter(&PARA11,6, "P2:");
    ShowParameter(&PARA12,7, ":");
  }
  else          
  {   
    San_X=90;		
    San_Y=2;  
    LED_Bei(San_X,San_Y);  
    for (;;)
    {
      i = ScanKey();
      switch(i){
      case SHIFT:                            //�ƶ���߶�Ӧ��Ҫ���õı���
        LED_Clr(San_X,San_Y);
        San_X+=6;
        if (San_X>108) 
        {
          San_X=90; 
          San_Y++;
        }
        if (San_Y>7) 
          San_X=2;
        LED_Bei(San_X,San_Y); 
        break;
      case INC:                              //�ı�����ָ�������ò�����ֵ0~9
        Xianbuf0[San_X-90+San_Y]++;    //�������Ӧ��ֵ
        if (Xianbuf0[San_X-90+San_Y]>0x39)      //San_X��LCD_low�ȼ���һ��
          Xianbuf0[San_X-90+San_Y]=0x30;
        buf[0]= Xianbuf0[San_X-90+San_Y];
        buf[1]='\0';
        LED_Bei(San_X,San_Y);
        break;
      case DEC: //��1
        Xianbuf0[San_X-90+San_Y]--;
        if (Xianbuf0[San_X-90+San_Y]<0x30)
          Xianbuf0[San_X-90+San_Y]=0x39;
        buf[0]= Xianbuf0[San_X-90+San_Y];
        buf[1]='\0';
        LED_Bei(San_X,San_Y);
        break;
      case ENTER: //ȷ��
        SetParameter(&PARA7, 2);      //�ı��Ӧȫ�ֱ�����ֵ
        SetParameter(&PARA8, 3);
        SetParameter(&PARA9, 4);
        SetParameter(&PARA10, 5);
        SetParameter(&PARA11, 6);
        SetParameter(&PARA12, 7);                  
        
        LPLD_Flash_SectorErase(FLASH_LED_ADDR1);//�������
        
        LPLD_Flash_ByteProgram(FLASH_LED_ADDR1,    (uint32*)&PARA7, 4);
        LPLD_Flash_ByteProgram(FLASH_LED_ADDR1+32, (uint32*)&PARA8, 4);
        LPLD_Flash_ByteProgram(FLASH_LED_ADDR1+64, (uint32*)&PARA9, 4);
        LPLD_Flash_ByteProgram(FLASH_LED_ADDR1+96, (uint32*)&PARA10, 4);  
        LPLD_Flash_ByteProgram(FLASH_LED_ADDR1+128,(uint32*)&PARA11, 4);
        LPLD_Flash_ByteProgram(FLASH_LED_ADDR1+160,(uint32*)&PARA12, 4);  
        LED_Clr(San_X, San_Y); 
        Set_b=0;   //�˳�����״̬
        return;
        break;
        
      default :  break;
      }
    }
  }
}


/*
 *������:void Speed_TWO(void)
 *����  :�����ı��ܶ�ʱ�ı������Լ��ܶ�ʱ�ı�����ʾ
 */
void Speed_TWO(void)     
{
  uint8 i;
  if (Set_b==0)
  {
    LED_CLS();
    for (i=0;i<24;i++)
      Xianbuf0[i]='\0';
    LED_P8x16Str(20,0,"<<Speed_TWO>>");
    ShowParameter(&PARA19, 2, ":");
    ShowParameter(&PARA20, 3, ":");
    ShowParameter(&PARA21, 4, ":");
    ShowParameter(&PARA22, 5, ":");
    ShowParameter(&PARA23, 6, ":");
    ShowParameter(&PARA24, 7, ":");
  }
  else          
  {   
    San_X=90;		
    San_Y=2;  
    LED_Bei(San_X,San_Y);  
    for (;;)
    {
      i = ScanKey();
      switch(i){
      case SHIFT:                            //�ƶ���߶�Ӧ��Ҫ���õı���
        LED_Clr(San_X,San_Y);
        San_X+=6;
        if (San_X>108) 
        {
          San_X=90; 
          San_Y++;
        }
        if (San_Y>7) 
          San_X=2;
        LED_Bei(San_X,San_Y); 
        break;
      case INC:                              //�ı�����ָ�������ò�����ֵ0~9
        Xianbuf0[San_X-90+San_Y]++;    //�������Ӧ��ֵ
        if (Xianbuf0[San_X-90+San_Y]>0x39)      //San_X��LCD_low�ȼ���һ��
          Xianbuf0[San_X-90+San_Y]=0x30;
        buf[0]= Xianbuf0[San_X-90+San_Y];
        buf[1]='\0';
        LED_Bei(San_X,San_Y);
        break;
      case DEC: //��1
        Xianbuf0[San_X-90+San_Y]--;
        if (Xianbuf0[San_X-90+San_Y]<0x30)
          Xianbuf0[San_X-90+San_Y]=0x39;
        buf[0]= Xianbuf0[San_X-90+San_Y];
        buf[1]='\0';
        LED_Bei(San_X,San_Y);
        break;
      case ENTER: //ȷ��
        SetParameter(&PARA19, 2);      //�ı��Ӧȫ�ֱ�����ֵ
        SetParameter(&PARA20, 3);
        SetParameter(&PARA21, 4);
        SetParameter(&PARA22, 5);
        SetParameter(&PARA23, 6);
        SetParameter(&PARA24, 7);                  
        
        LPLD_Flash_SectorErase(FLASH_LED_ADDR4);//�������
        
        LPLD_Flash_ByteProgram(FLASH_LED_ADDR4,    (uint32*)&PARA19, 4);
        LPLD_Flash_ByteProgram(FLASH_LED_ADDR4+32, (uint32*)&PARA20, 4);
        LPLD_Flash_ByteProgram(FLASH_LED_ADDR4+64, (uint32*)&PARA21, 4);
        LPLD_Flash_ByteProgram(FLASH_LED_ADDR4+96, (uint32*)&PARA22, 4);  
        LPLD_Flash_ByteProgram(FLASH_LED_ADDR4+128,(uint32*)&PARA23, 4);
        LPLD_Flash_ByteProgram(FLASH_LED_ADDR4+160,(uint32*)&PARA24, 4);  
        LED_Clr(San_X, San_Y); 
        Set_b=0;   //�˳�����״̬
        return;
        break;
        
      default :  break;
      }
    }
  }
}






/*
 *������:void Direction(void) 
 *����  :�ֶ��������ҳ����������flash������ݽ�ȫ��ɾ��
 */

void Direction(void)     
{
  uint8 i;
  if (Set_b==0)
  {
    LED_CLS();
    for (i=0;i<24;i++)
      Xianbuf0[i]='\0';
    LED_P8x16Str(15,0,"<<Direction>>");
    ShowParameter(&PARA13, 2, "D_P:");
    ShowParameter(&PARA14, 3, "D_D/100:");
    ShowParameter(&PARA15, 4, "L_R_OFF:");
    ShowParameter(&PARA16, 5, ":");
    ShowParameter(&PARA17, 6, ":");
    ShowParameter(&PARA18, 7, ":");
    
  }
  else          
  {   
    San_X=90;		
    San_Y=2;  
    LED_Bei(San_X,San_Y);  
    for (;;)
    {
      i = ScanKey();
      switch(i){
      case SHIFT:                            //�ƶ���߶�Ӧ��Ҫ���õı���
        LED_Clr(San_X,San_Y);
        San_X+=6;
        if (San_X>108) 
        {
          San_X=90; 
          San_Y++;
        }
        if (San_Y>7) 
          San_Y=2;
        LED_Bei(San_X,San_Y); 
        break;
      case INC:                              //�ı�����ָ�������ò�����ֵ0~9
        Xianbuf0[San_X-90+San_Y]++;    //�������Ӧ��ֵ
        if (Xianbuf0[San_X-90+San_Y]>0x39)      //San_X��LCD_low�ȼ���һ��
          Xianbuf0[San_X-90+San_Y]=0x30;
        buf[0]= Xianbuf0[San_X-90+San_Y];
        buf[1]='\0';
        LED_Bei(San_X,San_Y);
        break;
      case DEC: //��1
        Xianbuf0[San_X-90+San_Y]--;
        if (Xianbuf0[San_X-90+San_Y]<0x30)
          Xianbuf0[San_X-90+San_Y]=0x39;
        buf[0]= Xianbuf0[San_X-90+San_Y];
        buf[1]='\0';
        LED_Bei(San_X,San_Y);
        break;
      case ENTER: //ȷ��
        SetParameter(&PARA13, 2);      //�ı��Ӧȫ�ֱ�����ֵ
        SetParameter(&PARA14, 3);
        SetParameter(&PARA15, 4);
        SetParameter(&PARA16, 5);
        SetParameter(&PARA17, 6);
        SetParameter(&PARA18, 7);                  
        
        LPLD_Flash_SectorErase(FLASH_LED_ADDR3);//�������
        
        LPLD_Flash_ByteProgram(FLASH_LED_ADDR3,    (uint32*)&PARA13, 4);
        LPLD_Flash_ByteProgram(FLASH_LED_ADDR3+32, (uint32*)&PARA14, 4);
        LPLD_Flash_ByteProgram(FLASH_LED_ADDR3+64, (uint32*)&PARA15, 4);
        LPLD_Flash_ByteProgram(FLASH_LED_ADDR3+96, (uint32*)&PARA16, 4);  
        LPLD_Flash_ByteProgram(FLASH_LED_ADDR3+128,(uint32*)&PARA17, 4);
        LPLD_Flash_ByteProgram(FLASH_LED_ADDR3+160,(uint32*)&PARA18, 4);  
        LED_Clr(San_X, San_Y); 
        Set_b=0;   //�˳�����״̬
        return;
        break;
        
      default :  break;
      }
    }
  }
}
/******************************************************************************/
/****************************4��ҳ�������ϣ�����*****************************/
/******************************************************************************/
/*
 *������:uint8 ScanKey(void)
 *����  :ɨ�谲��,���ҷ��ذ���ֵ��ӦֵΪ1~4,0Ϊû�м�����
 *����  :��
 *BY    :zf
 */
uint8 ScanKey(void)
{
  uint8 Key;    
  BYTE key;          //�ṹ������
  key.Byte=0xff;     //ͨ������ͬ�ļ����Ըı��ֵ����λ�����Ӷ������ж�
  key.Bits.B0=KEY1;
  key.Bits.B1=KEY2;
  key.Bits.B2=KEY3;
  key.Bits.B3=KEY4;
  Dials=key.Byte;
  if((key.Byte & 0x0f)!=0x0f)//1��4������һ������ 
  {
    for(int32 j=0;j<=10000;j++)
        {
          volatile uint8 i ;
          for(i=0;i<1;i++) {
           asm("nop");
           asm("nop");}
        }
    if (KEY4==0) 
      Key=ENTER;
    else if (KEY3==0)
      Key=DEC;
    else if (KEY2==0)
      Key=INC;
    else 
      Key=SHIFT;
    while((key.Byte & 0x0f)!=0x0f)//֧��������������
    {
      key.Bits.B0=KEY1;
      key.Bits.B1=KEY2;
      key.Bits.B2=KEY3;
      key.Bits.B3=KEY4;
    }
    for(int32 j=0;j<=10000;j++)
        {
          volatile uint8 i ;
          for(i=0;i<1;i++) {
           asm("nop");
           asm("nop");}
        }
  }
  else 
    Key=0;
  return(Key);
}
/*
 *������:void ShowPage(void) 
 *����  :��ȡҳ��ֵ��������ʾ��Ӧ��ҳ��
 */
void ShowPage(void)
 {
    switch (LEDPage)
     {
       case 1: HOME();          break;
       case 2: Angle_ONE();     break;
       case 3: Speed_ONE();     break;
       case 4: Direction();     break;
       //case 5: Speed_TWO();     break;
       default :                break;
     } 
 }
/*
 *������:void SetLCD() 
 *����  :ɨ���ֵ�����Ҷ�ȡҳ��ֵ��ͨ��oled��ʾҳ��
 *����  :��
 *BY    :zf
 */
void SetLED(void)
{
  uint8 k;
  while(SetOK == 0)
  {
    k = ScanKey();
    switch(k)
    {
    case SHIFT:
      ShowPage();         break;
    case INC:
      if (LEDPage < 5)   //��ǰ��
        LEDPage++;
      else
        LEDPage = 1;
      ShowPage();         break;
    case DEC:
      if (LEDPage > 1)   //���
        LEDPage--;
      else
        LEDPage = 4;
      ShowPage();         break;
    case ENTER:
      Set_b=1;           //���뻭�����
      ShowPage();         break;
    default :             break;
    }
  }
}
/*
 *������:void InitFlashLcd(void) 
 *����  :��ʼ��flash����
 *����  :��
 *BY    :zf
 */
void InitFlashLed(void) 
{
  LPLD_Flash_Init();
  FlashWrite_flag=FLASH_READ(FLASH_LED_SECTOR0,0,uint32);
  if(FlashWrite_flag!=0xffffffff)//flash��ȫ��������򲻶�ȡflash������ʹ�ó�����ı���ֵ
   { 
      PARA1=FLASH_READ(FLASH_LED_SECTOR0,0,uint32);
      PARA2=FLASH_READ(FLASH_LED_SECTOR0,32,uint32);
      PARA3=FLASH_READ(FLASH_LED_SECTOR0,64,uint32);
      PARA4=FLASH_READ(FLASH_LED_SECTOR0,96,uint32);
      PARA5=FLASH_READ(FLASH_LED_SECTOR0,128,uint32);
      PARA6=FLASH_READ(FLASH_LED_SECTOR0,160,uint32);
      
      PARA7=FLASH_READ(FLASH_LED_SECTOR1,0,uint32);
      PARA8=FLASH_READ(FLASH_LED_SECTOR1,32,uint32);
      PARA9=FLASH_READ(FLASH_LED_SECTOR1,64,uint32);
      PARA10=FLASH_READ(FLASH_LED_SECTOR1,96,uint32);
      PARA11=FLASH_READ(FLASH_LED_SECTOR1,128,uint32);
      PARA12=FLASH_READ(FLASH_LED_SECTOR1,160,uint32);   
      
      PARA13=FLASH_READ(FLASH_LED_SECTOR3,0,uint32);
      PARA14=FLASH_READ(FLASH_LED_SECTOR3,32,uint32);
      PARA15=FLASH_READ(FLASH_LED_SECTOR3,64,uint32);
      PARA16=FLASH_READ(FLASH_LED_SECTOR3,96,uint32);
      PARA17=FLASH_READ(FLASH_LED_SECTOR3,128,uint32);
      PARA18=FLASH_READ(FLASH_LED_SECTOR3,160,uint32);
      
      PARA19=FLASH_READ(FLASH_LED_SECTOR4,0,uint32);
      PARA20=FLASH_READ(FLASH_LED_SECTOR4,32,uint32);
      PARA21=FLASH_READ(FLASH_LED_SECTOR4,64,uint32);
      PARA22=FLASH_READ(FLASH_LED_SECTOR4,96,uint32);
      PARA23=FLASH_READ(FLASH_LED_SECTOR4,128,uint32);
      PARA24=FLASH_READ(FLASH_LED_SECTOR4,160,uint32);
   }
}

