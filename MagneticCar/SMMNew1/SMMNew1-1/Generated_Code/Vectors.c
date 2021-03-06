/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : Vectors.c
**     Project     : SMMNew1
**     Processor   : 56F8013VFAE
**     Version     : Component 01.022, Driver 02.10, CPU db: 2.87.098
**     Compiler    : CodeWarrior DSP C Compiler
**     Date/Time   : 2016-03-02, 22:04, # CodeGen: 0
**     Abstract    :
**
**     Settings    :
**
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
** @file Vectors.c                                                  
** @version 02.10
** @brief
**
*/         
/*!
**  @addtogroup Vectors_module Vectors module documentation
**  @{
*/         

#include "Cpu.h"
#include "LED.h"
#include "AS1.h"
#include "AD1.h"
#include "PWMC1.h"
#include "COUNTER1.h"
#include "COUNTER2.h"
#include "TI1.h"
#include "IFsh1.h"
#include "Events.h"

#ifndef _lint

extern void _EntryPoint(void);         /* Startup routine */

volatile asm void _vectboot(void);
#pragma define_section interrupt_vectorsboot "interrupt_vectorsboot.text"  RX
#pragma section interrupt_vectorsboot begin
volatile asm void _vectboot(void) {
  JMP  _EntryPoint                     /* Reset vector (Used) */
  JMP  _EntryPoint                     /* COP reset vector (Used) */
}
#pragma section interrupt_vectorsboot end

volatile asm void _vect(void);
#pragma define_section interrupt_vectors "interrupt_vectors.text"  RX
#pragma section interrupt_vectors begin
volatile asm void _vect(void) {
  JMP  _EntryPoint                     /* Interrupt no. 0 (Used)   - ivINT_Reset */
  JMP  _EntryPoint                     /* Interrupt no. 1 (Used)   - ivINT_COPReset  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 2 (Unused) - ivINT_Illegal_Instruction  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 3 (Unused) - ivINT_SW3  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 4 (Unused) - ivINT_HWStackOverflow  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 5 (Unused) - ivINT_MisalignedLongWordAccess  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 6 (Unused) - ivINT_OnCE_StepCounter  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 7 (Unused) - ivINT_OnCE_BU0  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 8 (Unused) - ivINT_OnCE_TraceBuffer  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 9 (Unused) - ivINT_OnCE_TxREmpty  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 10 (Unused) - ivINT_OnCE_RxRFull  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 11 (Unused) - ivINT_SW2  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 12 (Unused) - ivINT_SW1  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 13 (Unused) - ivINT_SW0  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 14 (Unused) - ivReserved3  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 15 (Unused) - ivReserved4  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 16 (Unused) - ivINT_LVI  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 17 (Unused) - ivINT_PLL  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 18 (Unused) - ivINT_HFM_ERR  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 19 (Unused) - ivINT_HFM_CC  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 20 (Unused) - ivINT_HFM_CBE  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 21 (Unused) - ivReserved8  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 22 (Unused) - ivINT_GPIO_D  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 23 (Unused) - ivINT_GPIO_C  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 24 (Unused) - ivINT_GPIO_B  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 25 (Unused) - ivINT_GPIO_A  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 26 (Unused) - ivINT_SPI_RxFull  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 27 (Unused) - ivINT_SPI_TxEmpty  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 28 (Unused) - ivINT_SCI_TxEmpty  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 29 (Unused) - ivINT_SCI_TxIdle  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 30 (Unused) - ivINT_SCI_Reserved  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 31 (Unused) - ivINT_SCI_RxError  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 32 (Unused) - ivINT_SCI_RxFull  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 33 (Unused) - ivReserved9  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 34 (Unused) - ivReserved10  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 35 (Unused) - ivINT_I2C  */
  JSR  COUNTER1_Interrupt              /* Interrupt no. 36 (Used)   - ivINT_TMR0  */
  JSR  COUNTER2_Interrupt              /* Interrupt no. 37 (Used)   - ivINT_TMR1  */
  JSR  TI1_Interrupt                   /* Interrupt no. 38 (Used)   - ivINT_TMR2  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 39 (Unused) - ivINT_TMR3  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 40 (Unused) - ivINT_ADCA_Complete  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 41 (Unused) - ivINT_ADCB_Complete  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 42 (Unused) - ivINT_ADC_ZC_LE  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 43 (Unused) - ivINT_PWM_Reload  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 44 (Unused) - ivINT_PWM_Fault  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 45 (Unused) - ivINT_LP  */
}
#pragma section interrupt_vectors end

#endif _lint

/* Disable MISRA rules for interurupt routines */
/*lint -esym(765,Cpu_Interrupt) Disable MISRA rule (8.10) checking for symbols (Cpu_Interrupt). */
/*lint -esym(765,COUNTER1_Interrupt) Disable MISRA rule (8.10) checking for symbols (COUNTER1_Interrupt). */
/*lint -esym(765,COUNTER2_Interrupt) Disable MISRA rule (8.10) checking for symbols (COUNTER2_Interrupt). */
/*lint -esym(765,TI1_Interrupt) Disable MISRA rule (8.10) checking for symbols (TI1_Interrupt). */

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
