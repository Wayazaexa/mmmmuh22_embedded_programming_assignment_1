/* Denna fil skall inledas med att definera våra olika variabler som kommer att behövas
utmed filens funktioner:
Baud rate 9600
Baud rate 115200
Enablea TX
Enablea UART
Diseablea UART
Definera stopbit
Definera flödeskontroll

Sedan går den vidare till att fullt ut definera funktionerna ifrån lib. */

#include "my_stm32f4_uart_lib.h"

#define UART_BR_9600 0x68B; // Used to set baudrate to 9600
#define UART_BR_115200 0x08A; // Used to set baudrate to 115200
#define UART_CR1_EN 0x2000; // Used to toggle UART enabled/disabled
#define UART_CR1_TXEN 0x08; // Used to enable transmitter
#define UART_CR1_RXEN 0x04; // Used to enable reciever
#define UART_CR2_STOPBITS 0x3000; // Used to set number of stopbits
#define UART_CR3_CTS_FLWCTRL 0x200; // Used to set CTS hardware flowcontrol
#define UART_CR3_RTS_FLWCTRL 0x100; // Used to set RTS hardware flowcontrol


void LIB_UART_Init(UART_ComType comtype, UART_BaudrateType baudrate)
{
    UART->CR1 &= ~UART_CR1_EN; // Disable UART
    RCC->AHB1ENR |= 0x1; // Enable GPIOA clock
    RCC->APB1ENR |= 0x20000; // Enable UART2 clock
    GPIOA->MODER &= ~0x00F0; // Reset Pin2 & Pin3 in the GPIOA Mode Register
    GPIOA->MODER |= 0x00A0; // Set Pin2 & Pin3 to alternate function mode
    GPIOA->AFR[0] &= ~0xFF00; // Reset Pin2 & Pin3 in the GPIOA Alternate Function Register
    GPIOA->AFR[0] |= 0x7700; // Set Pin2 & Pin3 to Rx & Tx
    UART->CR2 &= ~UART_CR2_STOPBITS; // Set 1 stopbit
    UART->CR3 &= ~UART_CR3_CTS_FLWCTRL; // Disable CTS flowcontrol
    UART->CR3 &= ~UART_CR3_RTS_FLWCTRL; // Disable RTS flowcontrol

    // Set Tx/Rx depending on the parameter comtype
    if (comtype == read)
    {
        UART->CR1 |= UART_CR1_RXEN;
    }
    else if (comtype == write)
    {
        UART->CR1 |= UART_CR1_TXEN;
    }
    else
    {
        UART->CR1 |= UART_CR1_RXEN;
        UART->CR1 |= UART_CR1_TXEN;
    }

    // Set baudrate depending on the parameter baudrate
    if (baudrate == br_9600)
    {
        UART->BRR = UART_BR_9600;
    }
    else
    {
        UART->BRR = UART_BR_115200;
    }

    UART->CR1 |= UART_CR1_EN; // Enable UART
}

void LIB_UART_Write(char ch)
{
    while (!(UART->SR & 0x80)){} // Wait until the UART transmit data register is empty
    UART->DR = ch; // Write the ch parameter to the UART Data Register
}

char LIB_UART_Read()
{
    while(!(UART-> SR & 0x20)){} // Wait until the UART read data register is not empty
	return UART->DR; // Read the data from the UART Data Register and return it
}
