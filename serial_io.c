/**
*****************************************************************************
**
**  File        : serial_io.c
**
**  Abstract    : System Workbench functions to set the serial port as
**  			  characters input/output
**
**  Environment : System Workbench for MCU
**
**  Distribution: The file is distributed �as is,� without any warranty
**                of any kind.
**
*****************************************************************************
**
** <h2><center>&copy; COPYRIGHT(c) 2014 Ac6</center></h2>
**
** Redistribution and use in source and binary forms, with or without modification,
** are permitted provided that the following conditions are met:
**   1. Redistributions of source code must retain the above copyright notice,
**      this list of conditions and the following disclaimer.
**   2. Redistributions in binary form must reproduce the above copyright notice,
**      this list of conditions and the following disclaimer in the documentation
**      and/or other materials provided with the distribution.
**   3. Neither the name of Ac6 nor the names of its contributors
**      may be used to endorse or promote products derived from this software
**      without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
** DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
** SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
** CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
** OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**
*****************************************************************************
*/


#include "stm32f2xx.h"
#include "stm322xg_eval.h"
			

#include "serial_io.h"

int __io_putchar(int ch) __attribute__((weak, alias ("__serial_io_putchar")));
int __io_getchar(void) __attribute__((weak, alias ("__serial_io_getchar")));

/* UART handler declaration */
UART_HandleTypeDef UartHandle;

void __serial_io_init() {
	/*## Configure the UART peripheral ##############################*/
	/* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	/* UART configured as follow:
	    - BaudRate = 115200 baud
	    - Word Length = 8 Bits
	    - Stop Bit = One Stop bit
	    - Parity = none
	    - Hardware flow control disabled (RTS and CTS signals) */

	UartHandle.Init.BaudRate   = 115200;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits   = UART_STOPBITS_1;
	UartHandle.Init.Parity     = UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode       = UART_MODE_TX_RX;

	BSP_COM_Init(COM1, &UartHandle);

	// This is just to keep Eclipse happy, but generates no code; without this
	// Eclipse will generate an "unused" warning for the weak declarations above.
	if (0) __io_putchar(__io_getchar());
}


int __serial_io_putchar(int ch)
{
	/* Write a character to the EVAL_COM1 and Loop until transmitted */
	HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
   	return ch;
}

int __serial_io_getchar(void)
{
	int ch;
	/* Read a character from the EVAL_COM1 and Loop until received */
	HAL_UART_Receive(&UartHandle, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
   	return ch;
}
