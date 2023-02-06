/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	uint32_t *pClkCtrlreg = (uint32_t*) 0x40023830;
	uint32_t *pPortDModeReg = (uint32_t*) 0x40020C00;
	uint32_t *pPortDOutReg = (uint32_t*) 0x40020C14;

	uint32_t *pPortAModeReg = (uint32_t*) 0x40020000;
	uint32_t *pPortAInReg = (uint32_t*) 0x40020010;

	//enable clock for GPOID and GPIOA peripherals in the AHB1ENR

	// unit32_t temp = *pClkCtrlreg; // read operation
	// temp = temp | 0x08; // modify
	// *pClkCtrlreg = temp;


	*pClkCtrlreg |= (1<<3);  // Same as *pClkCtrlreg = *pClkCtrlreg | 0x08;
	*pClkCtrlreg |= (1<<0);


	// configuring PD12 as output
	*pPortDModeReg &= ~(3 << 24); 	// Same as *pPortDModeReg = *pPortDModeReg  & 0xFCFFFFFF;

	// b. make 24th bit position as 1 (set)
	*pPortDModeReg |= (1 << 24); // Same as 	*pPortDModeReg = *pPortDModeReg  | 0x01000000;

	// configure PA0 as input mode (GPIOA MODE REGISTER)
	*pPortAModeReg = *pPortAModeReg & ~(3 << 0);

	while(1)
	{
		// read pin status of the pin PA0 (GPIOA INPUT DATA REGISTER)
			uint8_t pinStatus = (uint8_t)(*pPortAInReg & 0x1); // zero out all other bits except bit 0

			if(pinStatus)
			{
				// turn on LED
				*pPortDOutReg |= (1<<12);
			}
			else
			{
				// turn off LED
				*pPortDOutReg &= ~(1<<12);
			}
	}

}
