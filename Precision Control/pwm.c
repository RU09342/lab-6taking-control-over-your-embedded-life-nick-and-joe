/*
 *       pwm.c
 *
 *   Created on:  November 8, 2017
 *  Last Edited:  November 8, 2017
 *       Author:  Nick Gorab
 *        Board:  5529
 */





/************************************************************************************************\
*                                                                                               *
*  IF YOU'RE USING THIS CODE AS REFERENCE AND HAVE QUESTIONS, FEEL FREE TO SLACK ME @nickgorab  *
*                                                                                               *
\************************************************************************************************/





#include <msp430.h>



/*************************\
 *                       *
 *  UART Initialization  *
 *                       *
\*************************/

void uartInit(void) {
    P3SEL    |=  BIT3;      // UART TX
    P3SEL    |=  BIT4;      // UART RX
    UCA0CTL1 |=  UCSWRST;   // Resets state machine
    UCA0CTL1 |=  UCSSEL_2;  // SMCLK
    UCA0BR0   =  6;         // 9600 Baud Rate
    UCA0BR1   =  0;         // 9600 Baud Rate
    UCA0MCTL |=  UCBRS_0;   // Modulation
    UCA0MCTL |=  UCBRF_13;  // Modulation
    UCA0MCTL |=  UCOS16;    // Modulation
    UCA0CTL1 &= ~UCSWRST;   // Initializes the state machine
    UCA0IE   |=  UCRXIE;    // Enables USCI_A0 RX Interrupt
}



/************************\
 *                      *
 *  PWM Initialization  *
 *                      *
\************************/

void pwmInit(void){
    P1DIR   |=  BIT2;       // P1.2 to output
    P1SEL   |=  BIT2;       // P1.2 to TA0.1
    TA0CCR0  = 0x0064;      // CCR0 value is 100
    TA0CCTL1 = OUTMOD_7;    // Reset/Set behavior
    TA0CTL   = TASSEL_2     // SMCLK
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
    uartInit();                         // Initializes UART
    pwmInit();                          // Initializes PWM
    __bis_SR_register(LPM0_bits + GIE); // Low-Power Mode 0 and Global Interrupt Enable
}



/************************\
 *                      *
 *    UART Interrupt    *
 *                      *
\************************/

#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void) {    // Interrupt function decleration
    while(!(UCA0IFG & UCTXIFG));        // Waits for TX buffer to be ready
    UCA0TXBUF = UCA0RXBUF;              // Sends bit back for debugging
    TA0CCR1 = (UCA0RXBUF);              // Sets CCR1 value to incoming byte
}
