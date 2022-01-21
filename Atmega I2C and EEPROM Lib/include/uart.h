#ifndef UART_H
#define UART_H

#include <avr/io.h>
//Communication mode
enum Mode
{
  TX_MODE = 1<<TXEN0,
  RX_MODE = 1<<RXEN0,
  TX_RX_MODE = (TX_MODE | RX_MODE)
};
//Functions
extern void UART_Init(uint32_t baud,uint8_t mode);
extern void UART_WriteChar(char data);
extern void UART_WriteChars(char* pData);
extern char UART_ReadChar(void);

#endif 
