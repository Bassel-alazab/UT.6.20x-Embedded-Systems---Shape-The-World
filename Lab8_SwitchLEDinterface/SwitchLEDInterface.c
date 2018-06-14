// ***** 0. Documentation Section *****
// SwitchLEDInterface.c for Lab 8
// Runs on LM4F120/TM4C123
// Use simple programming structures in C to toggle an LED
// while a button is pressed and turn the LED on when the
// button is released.  This lab requires external hardware
// to be wired to the LaunchPad using the prototyping board.
// January 15, 2016
//      Jon Valvano and Ramesh Yerraballi

// ***** 1. Pre-processor Directives Section *****
#include "TExaS.h"
#include "tm4c123gh6pm.h"

// ***** 2. Global Declarations Section *****
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))

unsigned long SW,LED;
// FUNCTION PROTOTYPES: Each subroutine defined
void delay100ms(void );
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

// ***** 3. Subroutines Section *****

// PE0, PB0, or PA2 connected to positive logic momentary switch using 10k ohm pull down resistor
// PE1, PB1, or PA3 connected to positive logic LED through 470 ohm current limiting resistor
// To avoid damaging your hardware, ensure that your circuits match the schematic
// shown in Lab8_artist.sch (PCB Artist schematic file) or 
// Lab8_artist.pdf (compatible with many various readers like Adobe Acrobat).
int main(void){ unsigned long volatile delay;
//**********************************************************************
// The following version tests input on PE0 and output on PE1
//**********************************************************************
  TExaS_Init(SW_PIN_PE0, LED_PIN_PE1, ScopeOn);  // activate grader and set system clock to 80 MHz
  
	SYSCTL_RCGC2_R|=0x10;       //active clock
	delay = SYSCTL_RCGC2_R;           //wait 3-5 bus cycle to active PORT
	GPIO_PORTE_DIR_R |=0x02;      //PE1 output
	GPIO_PORTE_DIR_R &= ~0x01;      //PE0 input
	GPIO_PORTE_AFSEL_R&=~0x03;       //no alternate function
	GPIO_PORTE_AMSEL_R&=~0x03;       //no analog
	GPIO_PORTE_PCTL_R&=~0x000000FF;  
	GPIO_PORTE_DEN_R |=0x03;        //enable PE0,PE1
  EnableInterrupts();           // enable interrupts for the grader
	GPIO_PORTE_DATA_R |= 0x02;
	while(1){
		delay100ms();
  SW = GPIO_PORTE_DATA_R&0x01;
	if(SW == 0x01){
	GPIO_PORTE_DATA_R^=0x02;
	}
	else{
	GPIO_PORTE_DATA_R |= 0x02;
	}
  }
  
}
void delay100ms(void ){
unsigned long time;
	time = 1333333;
	while(time > 1){
	time = time - 1;
	}
}
