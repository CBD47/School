
// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = EXTRC_CLKOUT// Oscillator Selection bits (RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define _XTAL_FREQ 4000000
#include <xc.h>
main(){

ANSEL = 0;			               // Intialize A/D ports off
CM1CON0 = 0;			               // Initialize Comparator 1 off
CM2CON0 = 0;			               // Initialize Comparator 2 off
PORTA = 0b00000000;			       // Clear PORTA Register
PORTB = 0b00000000;			       // Clear PORTB Register
PORTC = 0b00000000;			       // Clear PORTC Register
PORTD = 0b00000000;			       // Clear PORTD Register
TRISA = 0b00000111;        		   // All PORTA I/O onputs
TRISB = 0b00000000;        		   // All PORTC I/O outputs
TRISC = 0b00000000;			       // All PORTD I/O outputs
TRISD = 0b00000001;                // RD0 to input

unsigned int state_led; //create variable named state_led data type int
state_led = 0;
while(1==1)                //loop forever
{
if (RD0 == 1)            // if a button press is detected,
     {                    
    state_led++;        //  increment the LED state variable
    switch (state_led)
         {
            case 1:                    // STATE0: turn only the D0 LED on
                RB3 = 1;
                RA0 = 0;
                RA1 = 0;
                RA2 = 0;
                break;
            case 2:                    // STATE1: turn only the D1 LED on
                RB3 = 0;
                RA0 = 1;
                RA1 = 0;
                RA2 = 0;
                break;
            case 3:                    // STATE2: turn only the D2 LED on
                RB3 = 0;
                RA0 = 0;
                RA1 = 1;
                RA2 = 0;
                break;
            case 4:                    // STATE3: turn only the D3 LED on
                RB3 = 0;
                RA0 = 0;
                RA1 = 0;
                RA2 = 1;
                break;
            default:                // If state_led > 3 reset switch count to zero
                state_led = 0;        // All LEDs off    
                RB3 = 0;
                RA0 = 0;
                RA1 = 0;
                RA2 = 0;                
                break;
            } //end switch
        while (RD0==1);                // Hold here until switch is released
        __delay_ms (100);                    // Delay 10 milliseconds and check again 
    } //End If
}    //End while
} //end main
