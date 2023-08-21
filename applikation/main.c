/* Här är exekveringen av vår applikation där vi ärver lib.h och därmed kan initiera
UART för att sedan skriva med UART-funktionen write i en while-loop. */

#include "../bibliotek/my_stm32f4_uart_lib.h"

int main(void)
{
    LIB_UART_Init(readwrite, br_115200);
    char message[] = "message to stm-chip";
    int i = 0;

    while (message[i] != '\0')
    {
        LIB_UART_Write(message[i]);
    }
    return 0;
}
