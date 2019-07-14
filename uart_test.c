/*
 * UART_Test.c
 *
 * Created: 06-Mar-19 5:04:35 PM
 * Author : TEP SOVICHEA
 * Description: In this tutorial you will learn how to use UART interface
 *  to communicate between microcontroller and PC by sending command such as:
 *      - led on: to turn on LED on pin 13
 *      - led off: to turn off LED on pin 13
 *      - led blink: to blink LED every 100ms
 */


#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    // initialize UART with baud rate 250kbps
    uart_init(250000);
    char rx_buf[RX_BUFSIZE];
    int8_t mode = -1;
    
    cli_reset();
    puts("Initializing UART tutorial...");
    // set pin 13 on Arduino board to output
    DDRB |= (1 << PORTB5);
    
    puts("------------------- Application Started -------------------");
    while (1)
    {
        // print ">>" only once when console is accepting command
        cli_print();
        if (uart_available())
        {
            // read character by character until '\n' is found
            if (gets_nb(rx_buf) != 0)
            {
                // initialize argument placeholder
                char arg[10] = "";
                
                // read argument from command line
                sscanf(rx_buf, "led %s", arg);
                
                if (strcmp(arg, "on") == 0)
                {
                    puts(BG "Turning on LED" RESET);
                    mode = 0;
                }
                else if (strcmp(arg, "off") == 0)
                {
                    puts(BG "Turning off LED" RESET);
                    mode = 1;
                }
                else if (strcmp(arg, "blink") == 0)
                {
                    puts(BG "Blinking LED" RESET);
                    mode = 2;
                }
                else
                {
                    puts(BR "error: command not found" RESET);
                }

                // reset console so that it can accept new command
                cli_done();
            }
        }
        
        switch (mode)
        {
            case 0:
            PORTB |= (1 << PORTB5);
            break;
            
            case 1:
            PORTB &= ~(1 << PORTB5);
            break;
            
            case 2:
            PORTB ^= (1 << PORTB5);
            _delay_ms(100);
            break;
            
            default: break;
        }
    }
}
