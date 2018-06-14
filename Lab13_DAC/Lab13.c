// Lab13.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// edX Lab 13 
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// Port B bits 3-0 have the 4-bit DAC
// Port E bits 3-0 have 4 piano keys

#include "..//tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "TExaS.h"
#include "DAC.h"


// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void delay(unsigned long msec);
int main(void){ // Real Lab13 
	// for the real board grader to work 
	// you must connect PD3 to your DAC output
	int input,prevInput; 
  TExaS_Init(SW_PIN_PE3210, DAC_PIN_PB3210,ScopeOn); // activate grader and set system clock to 80 MHz
// PortE used for piano keys, PortB used for DAC        
  Sound_Init(); // initialize SysTick timer and DAC
  Piano_Init();
  EnableInterrupts();  // enable after all initialization are done
	
		while(1){  
			//32 element
// input from keys to select tone
			input = Piano_In();
			if(input != prevInput){
				if(input == 0x01){		
						//EnableInterrupts();
						Sound_Tone(4779);
				}else if(input == 0x02){
						//EnableInterrupts();
						Sound_Tone(4257);
				}else if(input == 0x04){
						//EnableInterrupts();
						Sound_Tone(3792);
				}else if(input == 0x08){
					//EnableInterrupts();
					Sound_Tone(3187);
				}else{
					Sound_Off();
				}
				delay(10);
			}
		
		prevInput = input;
  }
		
		
	/*
	//16-element
	while(1){  
	input = Piano_In();	
// input from keys to select tone
		if(input != prevInput){
				if(input == 0x01){
		//EnableInterrupts();
		Sound_Tone(9556);
					//Sound_Tone(2389);
		}else if(input == 0x02){
		//EnableInterrupts();
		Sound_Tone(8513);
			//Sound_Tone(2128);
		}else if(input == 0x04){
		//EnableInterrupts();
		Sound_Tone(7584);
			//Sound_Tone(1896);
		}else if(input == 0x08){
		//EnableInterrupts();
		Sound_Tone(6378);
			//Sound_Tone(1594);
		}else{
		Sound_Off();
		}
		delay(10);
		}
		prevInput = input;
  }  
*/
}

// Inputs: Number of msec to delay
// Outputs: None
void delay(unsigned long msec){ 
  unsigned long count;
  while(msec > 0 ) {  // repeat while there are still delay
    count = 16000;    // about 1ms
    while (count > 0) { 
      count--;
    } // This while loop takes approximately 3 cycles
    msec--;
  }
}


