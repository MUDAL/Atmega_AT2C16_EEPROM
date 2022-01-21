#include "i2c.h"
#include "uart.h"
#include <util/delay.h>

#define PAGE_SIZE 16

void EEPROM_WritePage(uint8_t pageAddr,uint8_t* pData,uint8_t len)
{
	if (len > PAGE_SIZE)
	{//Page size must not be exceeded.
		return;
	}
	//optional but ensures the user's input doesn't exceed 127
	pageAddr = pageAddr % 128; 
	//extract 3 MSB of EEPROM page address and store in EEPROM slave address
	uint8_t deviceAddr = ((((pageAddr >> 3) & 0x0E) | 0xA0)>>1);
	//extract 4 LSB of EEPROM page address and store in EEPROM word address
	uint8_t wordAddr = ((pageAddr & 0x0F) << 4);
	//I2C communication involving EEPROM slave and word address
	if(I2C_Write(deviceAddr,wordAddr,pData,len) == I2C_SUCCESS)
  {
    UART_WriteChars("I2C Write: Success\n");
  }
  else
  {
    UART_WriteChars("I2C Write: Failure\n");
  }
	//write cycle time
	_delay_ms(5);
}

void EEPROM_ReadPage(uint8_t pageAddr,uint8_t* pBuffer,uint8_t len)
{
	if (len > PAGE_SIZE)
	{//Page size must not be exceeded.
		return;
	}
	//optional but ensures the user's input doesn't exceed 127
	pageAddr = pageAddr % 128; 
	//extract 3 MSB of EEPROM page address and store in EEPROM slave address
	uint8_t deviceAddr = ((((pageAddr >> 3) & 0x0E) | 0xA0)>>1);
	//extract 4 LSB of EEPROM page address and store in EEPROM word address
	uint8_t wordAddr = ((pageAddr & 0x0F) << 4);
	//I2C communication involving EEPROM slave and word address
	if(I2C_Read(deviceAddr,wordAddr,pBuffer,len) == I2C_SUCCESS)
	{
		UART_WriteChars("I2C Read: Success\n");
	}
	else
	{
		UART_WriteChars("I2C Read: Failure\n");
	}
}

int main(void)
{
  //uint8_t txBuffer[4] = {'F','X','P'};
  uint8_t rxBuffer[4] = {0};
  UART_Init(9600,TX_RX_MODE);
  I2C_Init();
  //EEPROM_WritePage(0,txBuffer,4);
  EEPROM_ReadPage(0,rxBuffer,4);
	UART_WriteChars("Stored data = ");
	UART_WriteChars((char*)rxBuffer);
  while(1)
  {

  }
}