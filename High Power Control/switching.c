/*
 *       switching.c
 *
 *   Created on:  November 11, 2017
 *  Last Edited:  November 11, 2017
 *       Author:  Nick Gorab
 *        Board:  2553
 */





/************************************************************************************************\
*                                                                                               *
*  IF YOU'RE USING THIS CODE AS REFERENCE AND HAVE QUESTIONS, FEEL FREE TO SLACK ME @nickgorab  *
*                                                                                               *
\************************************************************************************************/





#include <msp430.h>



/************************\
 *                      *
 *  DOC Initialization  *
 *                      *
\************************/

void dcoInit(void){
    DCOCTL  = 0;                               // Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
    DCOCTL  = CALDCO_1MHZ;
}




/*************************\
 *                       *
 *  UART Initialization  *
 *                       *
\*************************/

void uartInit(void) {
    P1SEL     = BIT1          // UART RX
              + BIT2 ;        // UART TX
    P1SEL2    = BIT1          // UART RX
              + BIT2 ;        // UART TX
    UCA0CTL1 |=  UCSSEL_2;    // SMCLK
    UCA0BR0   =  104;         // 9600 Baud Rate
    UCA0BR1   =  0;           // 9600 Baud Rate
    UCA0MCTL  =  UCBRS0;      // Modulation
    UCA0CTL1 &= ~UCSWRST;     // Initializes the state machine
    IE2      |=  UCA0RXIE;    // Enables USCI_A0 RX interrupt
}



/************************\
 *                      *
 *  PWM Initialization  *
 *                      *
\************************/

void pwmInit(void){
    P1DIR |=  BIT6;       // P1.2 to output
    P1SEL |=  BIT6;       // P1.2 to TA0.1
    CCR0   = 0x0064;      // CCR0 value is 100
    CCTL1  = OUTMOD_7;    // Reset/Set behavior
    TA0CTL = TASSEL_2     // SMCLK
           + MC_1         // Up-Mode
           + ID_3;        // Predivider of 8
}



/***********************\
 *                     *
 *    Main Function    *
 *                     *
\***********************/

void main(void){
    WDTCTL = WDTPW + WDTHOLD;           // Disables Watchdog Timer
    dcoInit();                          // Initializes DCO
    uartInit();                         // Initializes UART
    pwmInit();                          // Initializes PWM
    __bis_SR_register(LPM0_bits + GIE); // Low-Power Mode 0 and Global Interrupt Enable
}



/************************\
 *                      *
 *    UART Interrupt    *
 *                      *
\************************/

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI_A0_ISR(void) {    // Interrupt function decleration
    while(!(UC0IFG & UCA0TXIFG));        // Waits for TX buffer to be ready
    UCA0TXBUF = UCA0RXBUF;              // Sends bit back for debugging
    CCR1      = (UCA0RXBUF);            // Sets CCR1 value to incoming byte
}
