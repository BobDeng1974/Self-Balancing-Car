/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Cpu.H
**     Project   : SMMNew1
**     Processor : 56F8013VFAE
**     Component : 56F8013VFAE
**     Version   : Component 01.022, Driver 02.08, CPU db: 2.87.097
**     Datasheet :  MC56F8300UM/D - Rev. 1.0
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 2012-2-2, 11:06
**     Abstract  :
**
**     Settings  :
**
**     Contents  :
**         EnableInt   - void Cpu_EnableInt(void);
**         DisableInt  - void Cpu_DisableInt(void);
**         SetWaitMode - void Cpu_SetWaitMode(void);
**         SetStopMode - void Cpu_SetStopMode(void);
**
**     (c) Freescale Semiconductor
**     2004 All Rights Reserved
**
**     Copyright : 1997 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

#ifndef __Cpu_H
#define __Cpu_H

/* MODULE Cpu. */

/* Active PE project configuration */
#define PEcfg_smmpROMxRAM 1

/* Active CPU bean */
#define PE_CPU_TYPE_56F8013VFAE

/* Active CPU variant */
#define PE_CPU_VARIANT_56F8013VFAE

/* Active CPU family */
#define PE_CPU_FAMILY_56800

/* Active CPU subfamily */
#define PE_CPU_SUBFAMILY_56F801x

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "assert.h"

#ifndef __BWUserType_TShadowRegs
#define __BWUserType_TShadowRegs
  typedef struct {                     /* Shadow register type. */
    word* R0;                          /* Shadow register R0. */
    word* R1;                          /* Shadow register R1. */
    int16_t N;                         /* Shadow register N. */
    int16_t M01;                       /* Shadow register M01. */
  } TShadowRegs;
#endif

/*lint -esym(765,SR_reg,SR_lock,_EntryPoint,_vect,_vectboot,Cpu_Interrupt) Disable MISRA rule (23) checking for symbols (SR_reg,SR_lock,_EntryPoint,_vect,_vectboot,Cpu_Interrupt). */
/* Global variables */
extern volatile word SR_lock;          /* Lock */
extern volatile word SR_reg;           /* Current value of the SR register */

#define   Cpu_SetStopMode()  asm(STOP) /* Set STOP mode */
/*
** ===================================================================
**     Method      :  Cpu_SetStopMode (component 56F8013VFAE)
**
**     Description :
**         Sets low power mode - Stop mode.
**         For more information about the stop mode see this CPU
**         documentation.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define   Cpu_SetWaitMode()  asm(WAIT) /* Set WAIT mode */
/*
** ===================================================================
**     Method      :  Cpu_SetWaitMode (component 56F8013VFAE)
**
**     Description :
**         Sets low power mode - Wait mode.
**         For more information about the wait mode see this CPU
**         documentation.
**         Release from wait mode: Reset or interrupt
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/


/*Shadow variables*/
extern word Shadow_GPIO_A_DR;          /* Shadow variable for I/O beans */


#define   Cpu_DisableInt()  __DI()     /* Disable interrupts */
/*
** ===================================================================
**     Method      :  Cpu_DisableInt (component 56F8013VFAE)
**
**     Description :
**         Disables all maskable interrupts
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define   Cpu_EnableInt()  __EI(0)     /* Enable interrupts */
/*
** ===================================================================
**     Method      :  Cpu_EnableInt (component 56F8013VFAE)
**
**     Description :
**         Enables all maskable interrupts
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void PE_low_level_init(void);
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
void Cpu_Interrupt(void);
/*
** ===================================================================
**     Method      :  Cpu_Interrupt (component 56F8013VFAE)
**
**     Description :
**         The method services unhandled interrupt vectors.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/


void _EntryPoint(void);
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

/* END Cpu. */

#endif
/* __Cpu_H */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.00 [04.35]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
