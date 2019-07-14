/*
* ----------------------------------------------------------------------------
* "THE BEER-WARE LICENSE" (Revision 42):
* <joerg@FreeBSD.ORG> wrote this file.  As long as you retain this notice you
* can do whatever you want with this stuff. If we meet some day, and you think
* this stuff is worth it, you can buy me a beer in return.        Joerg Wunsch
* ----------------------------------------------------------------------------
*
* Stdio demo, UART declarations
*
* $Id: uart.h,v 1.1 2005/12/28 21:38:59 joerg_wunsch Exp $
*/


#ifndef UART_H_
#define UART_H_

#define F_CPU 16000000UL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <avr/io.h>

#define ESC          "\033"
#define RESET        ESC "[0m"
#define CLEAR_SCREEN ESC "c"
#define CLEAR_SCROLL ESC "[3J"
#define CLEAR_LINE   ESC "[2K"

#define CURSOR_RIGHT(col)   ESC "[" col "C"
#define CURSOR_LEFT(col)    ESC "[" col "D"

#define BY          ESC "[33;1m"  // Light Yellow.
#define BG          ESC "[32;1m"  // Light Green.
#define BR          ESC "[31;1m"  // Light Green.

/*
* Perform UART startup initialization.
*/
void uart_init(uint32_t baudrate);

/*
* Send one character to the UART.
*/
int	uart_putchar(char c, FILE *stream);

/*
* Size of internal line buffer used by uart_getchar().
*/
#define RX_BUFSIZE 80
#define TX_BUFSIZE 80

/*
* Receive one character from the UART.  The actual reception is
* line-buffered, and one character is returned from the buffer at
* each invocation.
*/

int	uart_getchar(FILE *stream);

/*
* Check if UART buffer is available
*/
int uart_available(void);

/*
* gets_nb is similar to the function gets provided by stdlib.h
* However, it provides non-blocking functionality so that the CPU
* doesn't stall for input, instead it will only read a character
* when UART is available and give result once it receive '\n' character
*/
int gets_nb(char* buf);

/*
* Print console start indicator ">>" only once
*/
void cli_print(void);

/*
* Tells the console it's ready to take another command
*/
void cli_done(void);

/*
* Send an ANSI escape sequence to clear the terminal
*/
void cli_reset(void);

#endif /* UART_H_ */