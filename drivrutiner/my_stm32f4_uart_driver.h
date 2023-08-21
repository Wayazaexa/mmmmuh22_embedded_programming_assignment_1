/* Denna fil skall definera våra så kallade utgångsbaser för korrekt
kommunikationsbuss samt USART-periferin. Den skall sedan gå vidare och definera
en struct som innehåller registrena för USART */

#ifndef __MY_STM32F4_UART_DRIVER_H
#define __MY_STM32F4_UART_DRIVER_H

#include <stdint.h>

#define PERIPH_BASE 0x40000000U // Start address of the peripherals bus (APB1)
#define USART2_BASE (PERIPH_BASE + 0x4400U) // Start address of USART registers

#define __IO volatile

typedef struct // Defines the different parts that make up an UART
{
    __IO uint32_t SR; // Status Register
    __IO uint32_t DR; // Data Register
    __IO uint32_t BRR; // Baudrate Register
    __IO uint32_t CR1; // Control Register 1
    __IO uint32_t CR2; // Control Register 2
    __IO uint32_t CR3; // Control Register 3
    __IO uint32_t GTPR; // Guard Time and Prescaler Register
}UART_Typedef;

#define UART ((UART_Typedef *) USART2_BASE)

#endif
