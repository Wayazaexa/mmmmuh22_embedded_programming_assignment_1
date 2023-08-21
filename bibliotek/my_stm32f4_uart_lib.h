/* Denna fil skall ärva ifrån driver.h filen och sedan gå vidare till att genomföra två
stycken enumerationskonstant-angivelser. En för UART_ComType och en för
UART_BaudrateType. Efter detta skall den även innehålla tre deklarationer av
funktioner:
1. LIB_UART_Write som tar karaktär som input
2. LIB_UART_Read som tar en karaktär ock skriver ut den
3. LIB_UART_Init som tar våra enumerationer för att initiera UART */

#ifndef __MY_STM32F4_UART_LIB_H
#define __MY_STM32F4_UART_LIB_H

#include "../drivrutiner/my_stm32f4_uart_driver.h"
#include "../drivrutiner/my_stm32f4_gpio_driver.h" // Not included in the repo

typedef enum
{
    read = 0,
    write,
    readwrite
}UART_ComType;

typedef enum
{
    br_9600 = 0,
    br_115200
}UART_BaudrateType;

void LIB_UART_Init(UART_ComType comtype, UART_BaudrateType baudrate);
void LIB_UART_Write(char ch);
char LIB_UART_Read();

#endif
