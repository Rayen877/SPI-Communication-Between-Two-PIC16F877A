/*
 * File:   Master_main.c
 * Author: Rayen
 *
 * Created on April 13, 2025, 11:07 PM
 */
#pragma config FOSC = XT  // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF  // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit
                          // (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF  // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF  // Flash Program Memory Write Enable bits 
                          // (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF   // Flash Program Memory Code Protection bit (Code protection off)
 


#include <xc.h>


#include <stdint.h>
#define _XTAL_FREQ 4000000

#define UP RB0
#define Down RB1
#define Send RB2

void SPI_Master_Init();
void SPI_Write(uint8_t);

void main(void)
{
  SPI_Master_Init(); 
  uint8_t Data = 0; 
  TRISB = 0x07; 
  TRISD = 0x00; 
  PORTD = 0x00; 
  
  while(1)
  {
    if (UP) 
    {
      Data++;
      __delay_ms(250);
    }
    if (Down) 
    {
      Data--;
      __delay_ms(250);
    }
    if (Send) 
    {
      SPI_Write(Data);
      __delay_ms(250);
    }
    PORTD = Data; 
  }
  return;
}
 
void SPI_Master_Init()
{
  SSPM0 = 0;
  SSPM1 = 0;
  SSPM2 = 0;
  SSPM3 = 0;
  
  SSPEN = 1;
  CKP = 0;
  CKE = 0;
  
  SMP = 0;
  
  TRISC5 = 0;
  TRISC4 = 1; 
  TRISC3 = 0; 

}
 
void SPI_Write(uint8_t Data)
{
  SSPBUF = Data; 
   while(!SSPSTATbits.BF); 
}