/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : Cpu.c
**     Project     : SMMNew1
**     Processor   : 56F8013VFAE
**     Component   : 56F8013VFAE
**     Version     : Component 01.022, Driver 02.10, CPU db: 2.87.098
**     Datasheet   :  MC56F8300UM/D - Rev. 1.0
**     Compiler    : CodeWarrior DSP C Compiler
**     Date/Time   : 2016-03-02, 22:04, # CodeGen: 0
**     Abstract    :
**
**     Settings    :
**
**     Contents    :
**         EnableInt   - void Cpu_EnableInt(void);
**         DisableInt  - void Cpu_DisableInt(void);
**         SetWaitMode - void Cpu_SetWaitMode(void);
**         SetStopMode - void Cpu_SetStopMode(void);
**
**     (c) Freescale Semiconductor, Inc.
**     2004 All Rights Reserved
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file Cpu.c
** @version 02.10
** @brief
**
*/         
/*!
**  @addtogroup Cpu_module Cpu module documentation
**  @{
*/         

/* MODULE Cpu. */
#include "LED.h"
#include "AS1.h"
#include "AD1.h"
#include "PWMC1.h"
#include "COUNTER1.h"
#include "COUNTER2.h"
#include "TI1.h"
#include "IFsh1.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Events.h"
#include "Cpu.h"

/*lint -save  -e950 Disable MISRA rule (1.1) checking. */


/* Global variables */
volatile word SR_lock = 0U;            /* Lock */
volatile word SR_reg;                  /* Current value of the SR register */

/*Definition of global shadow variables*/
word Shadow_GPIO_A_DR;

/*
** ===================================================================
**     Method      :  Cpu_Interrupt (component 56F8013VFAE)
**
**     Description :
**         The method services unhandled interrupt vectors.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
#pragma interrupt alignsp
void Cpu_Interrupt(void)
{
  asm(DEBUGHLT);                       /* Halt the core and placing it in the debug processing state */
}

/*
** ===================================================================
**     Method      :  Cpu_DisableInt (component 56F8013VFAE)
**     Description :
**         Disables all maskable interrupts
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_DisableInt(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  Cpu_EnableInt (component 56F8013VFAE)
**     Description :
**         Enables all maskable interrupts
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_EnableInt(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  Cpu_SetStopMode (component 56F8013VFAE)
**     Description :
**         Sets low power mode - Stop mode.
**         For more information about the stop mode see this CPU
**         documentation.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_SetStopMode(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  Cpu_SetWaitMode (component 56F8013VFAE)
**     Description :
**         Sets low power mode - Wait mode.
**         For more information about the wait mode see this CPU
**         documentation.
**         Release from wait mode: Reset or interrupt
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_SetWaitMode(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  _EntryPoint (component 56F8013VFAE)
**
**     Description :
**         Initializes the whole system like timing and so on. At the end 
**         of this function, the C startup is invoked to initialize stack,
**         memory areas and so on.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
extern void init_56800_(void);         /* Forward declaration of external startup function declared in startup file */

/*** !!! Here you can place your own code using property "User data declarations" on the build options tab. !!! ***/

void _EntryPoint(void)
{
  #pragma constarray off

  /*** !!! Here you can place your own code before PE initialization using property "User code before PE initialization" on the build options tab. !!! ***/

  /*** ### 56F8013VFAE "Cpu" init code ... ***/
  /*** PE initialization code after reset ***/
  /* System clock initialization */
  setRegBitGroup(OSCTL, TRIM, (word)getReg(FMOPT1)); /* Set the trim osc freq with factory programmed value */
  clrRegBit(PLLCR, PRECS);             /* Select an internal clock source for the CPU core */
  setReg(PLLCR, (PLLCR_LCKON_MASK | PLLCR_ZSRC0_MASK)); /* Enable PLL, LCKON and select clock source from prescaler */
  /* PLLDB: LORTP=2,??=0,PLLCOD=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  setReg16(PLLDB, 8192U);              /* Set the clock prescalers */ 
  while(!getRegBit(PLLSR, LCK0)){}     /* Wait for PLL lock */
  setReg(PLLCR, (PLLCR_LCKON_MASK | PLLCR_ZSRC1_MASK)); /* Select clock source from postscaler */
  /* FMCLKD: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,DIVLD=0,PRDIV8=0,DIV=40 */
  setReg16(FMCLKD, 40U);               /* Set the flash clock prescaler */ 
  /*** End of PE initialization code after reset ***/

  /*** !!! Here you can place your own code after PE initialization using property "User code after PE initialization" on the build options tab. !!! ***/

  asm(JMP init_56800_);                /* Jump to C startup code */
}

/*
** ===================================================================
**     Method      :  PE_low_level_init (component 56F8013VFAE)
**
**     Description :
**         Initializes beans and provides common register initialization. 
**         The method is called automatically as a part of the 
**         application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void PE_low_level_init(void)
{
  /* GPIO_A_DRIVE: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,DRIVE=0 */
  setReg16(GPIO_A_DRIVE, 0U);          /* Set High/Low drive strength on GPIOA pins according to the CPU bean settings */ 
  /* GPIO_B_DRIVE: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,DRIVE=0 */
  setReg16(GPIO_B_DRIVE, 0U);          /* Set High/Low drive strength on GPIOB pins according to the CPU bean settings */ 
  /* GPIO_C_DRIVE: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,DRIVE6=0,DRIVE5=0,DRIVE4=0,??=0,DRIVE2=0,DRIVE1=0,DRIVE0=0 */
  setReg16(GPIO_C_DRIVE, 0U);          /* Set High/Low drive strength on GPIOC pins according to the CPU bean settings */ 
  /* GPIO_D_DRIVE: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,DRIVE=0 */
  setReg16(GPIO_D_DRIVE, 0U);          /* Set High/Low drive strength on GPIOD pins according to the CPU bean settings */ 
  /* SIM_PCE: I2C=0,??=0,ADC=1,??=0,??=0,??=0,??=0,??=0,??=0,TMR=1,??=0,SCI=1,??=0,SPI=0,??=0,PWM=1 */
  setReg16(SIM_PCE, 8273U);            /* Set up the peripheral clock enable register */ 
  /* SIM_CTRL: TC3_SD=0,TC2_SD=0,TC1_SD=0,TC0_SD=0,SCI_SD=0,??=0,TC3_INP=0,??=0,??=0,??=0,ONCEEBL=0,SWRST=0,STOP_DISABLE=0,WAIT_DISABLE=0 */
  setReg16(SIM_CTRL, 0U);              /* Set up the SIM control register */ 
  /* SIM_CLKOUT: ??=0,??=0,??=0,??=0,??=0,??=0,PWM3_b=0,PWM2_b=0,PWM1_b=0,PWM0_b=0,CLKDIS=1,CLKOSEL=0 */
  setReg16(SIM_CLKOUT, 32U);           /* Set up the SIM clock output select register */ 
  /* Common initialization of the CPU registers */
  /* GPIO_A_IENR: IEN&=~64 */
  clrReg16Bits(GPIO_A_IENR, 64U);       
  /* GPIO_A_IAR: IA&=~64 */
  clrReg16Bits(GPIO_A_IAR, 64U);        
  /* GPIO_A_IESR: IES|=64 */
  setReg16Bits(GPIO_A_IESR, 64U);       
  /* GPIO_A_PUR: PU&=~80 */
  clrReg16Bits(GPIO_A_PUR, 80U);        
  /* GPIO_A_PPMODE: PPMODE|=64 */
  setReg16Bits(GPIO_A_PPMODE, 64U);     
  /* GPIO_A_DR: D&=~64 */
  clrReg16Bits(GPIO_A_DR, 64U);         
  /* GPIO_A_DDR: DD|=64 */
  setReg16Bits(GPIO_A_DDR, 64U);        
  /* GPIO_A_PER: PE&=~64,PE|=63 */
  clrSetReg16Bits(GPIO_A_PER, 64U, 63U); 
  /* SIM_GPS: CFG_B7=0,CFG_B6=0,CFG_B4=0,CFG_A5=2,CFG_A4=3 */
  clrSetReg16Bits(SIM_GPS, 3332U, 11U); 
  /* GPIO_B_PER: PE|=208 */
  setReg16Bits(GPIO_B_PER, 208U);       
  /* GPIO_C_PER: PE6=1,PE5=1,PE4=1,PE2=1,PE1=1,PE0=1 */
  setReg16Bits(GPIO_C_PER, 119U);       
  /* SIM_CLKOUT: PWM3_b=0,PWM2_b=0,PWM1_b=0,PWM0_b=0 */
  clrReg16Bits(SIM_CLKOUT, 960U);       
  /* INTC_IPR3: TMR_2_IPL=2,TMR_1_IPL=2,TMR_0_IPL=2 */
  clrSetReg16Bits(INTC_IPR3, 1344U, 2688U); 
  /* GPIO_B_PUR: PU&=~16 */
  clrReg16Bits(GPIO_B_PUR, 16U);        
  /* FMCR: AEIE=0 */
  clrReg16Bits(FMCR, 256U);             
  /* ### BitIO "LED" init code ... */
  Shadow_GPIO_A_DR &= ~(word)64U;      /* Initialize shadow variable */
  /* ### Asynchro serial "AS1" init code ... */
  AS1_Init();
  /* ### ADC "AD1" init code ... */
  AD1_Init();
  /* ### PWMMC "PWMC1" init code ... */
  PWMC1_Init();


  /* ### EventCntr16 "COUNTER1" init code ... */
  COUNTER1_Init();
  /* ### EventCntr16 "COUNTER2" init code ... */
  COUNTER2_Init();
  /* ### TimerInt "TI1" init code ... */
  TI1_Init();
  IFsh1_Init();
  __EI(0);                             /* Enable interrupts of the selected priority level */
}

/* END Cpu. */

