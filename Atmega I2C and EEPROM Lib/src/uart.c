#include "uart.h"

#define TX_BUFFER_EMPTY 1<<UDRE0
#define RX_BUFFER_FULL  1<<RXC0

/**
 * @brief 
 * 
 * @param baud 
 * @param mode 
 */
void UART_Init(uint32_t baud,uint8_t mode)
{
  uint16_t ubrr = (F_CPU / (16 * baud)) - 1;
  UBRR0H = ubrr>>8;
  UBRR0L = ubrr;
  UCSR0B = mode; //Enable TX, RX or both modes
  UCSR0C = (3<<UCSZ00); //8-bit data frame, 1 stop bit
}

/**
 * @brief 
 * 
 * @param data 
 */
void UART_WriteChar(char data)
{
  //wait for empty Tx buffer, then write data
  while ((UCSR0A & TX_BUFFER_EMPTY) != TX_BUFFER_EMPTY);  
  UDR0 = data;
}

/**
 * @brief 
 * 
 * @param pData 
 */
void UART_WriteChars(char* pData)
{
  while(*pData != '\0')
  {
    UART_WriteChar(*pData);
    pData++;
  }
}

/**
 * @brief 
 * 
 * @return char 
 */
char UART_ReadChar(void)
{
  //wait for non-empty Rx buffer, then read data
  while((UCSR0A & RX_BUFFER_FULL) != RX_BUFFER_FULL);
  return UDR0;
}
