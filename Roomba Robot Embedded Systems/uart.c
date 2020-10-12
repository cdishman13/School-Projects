/**
*
* 	@file  uart.c
*
*
*
*
*
*   @author
*   @date
*/

#include "uart.h"
#include "button.h"

/**
 * @brief sets all necessary registers to enable the uart 1 module.
 */
void uart_init(void){
	//TODO
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;

    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1;

    GPIO_PORTB_AFSEL_R |= (BIT0 | BIT1);

    GPIO_PORTB_PCTL_R |= 0x00000011;

    GPIO_PORTB_DEN_R |= (BIT0 | BIT1);

    GPIO_PORTB_DIR_R &= ~BIT0;

    GPIO_PORTB_DIR_R |= BIT1;

    uint16_t iBRD= 8;
    uint16_t fBRD= 44;

    UART1_CTL_R &= ~(UART_CTL_UARTEN);

    UART1_IBRD_R = iBRD;
    UART1_FBRD_R = fBRD;

    UART1_LCRH_R = UART_LCRH_WLEN_8 ;

    UART1_CC_R = UART_CC_CS_SYSCLK;

    UART1_CTL_R = (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
}

/**
 * @brief Sends a single 8 bit character over the uart 1 module.
 * @param data the data to be sent out over uart 1
 */
void uart_sendChar(char data){

    while(UART1_FR_R & 0x20)
    {
    }

    UART1_DR_R = data;
}

/**
 * @brief polling receive an 8 bit character over uart 1 module.
 * @return the character received or a -1 if error occured
 */
int uart_receive(void){

    char data = 0;

    while(UART1_FR_R & UART_FR_RXFE)
    {
    }
    data = (char)(UART1_DR_R & 0xFF);
    return data;
}

/**
 * @brief polling receive an 8 bit character over uart 1 module.
 * @return the character received or a -1 if error occured
 */
int fancy_uart_receive(int* gimme){

    char data = -1;
    while(UART1_FR_R & UART_FR_RXFE)
    {
        *gimme = button_getButton();

        return -1;
    }

    data = (char)(UART1_DR_R & 0xFF);

    return data;
}

/**
 * @brief sends an entire string of character over uart 1 module
 * @param data pointer to the first index of the string to be sent
 */
void uart_sendStr(const char *data){
	//TODO
    char count =0;
    while(count < strlen(data)){
        while(UART1_FR_R & 0x20){}
        uart_sendChar(data[count]);
        count++;
    }
}
