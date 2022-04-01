#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#include "io.h"

static const IO oled_led1 = {&PORTD, PIN4};
static const IO oled_led2 = {&PORTD, PIN5};

void task5()
{
    configure_IO(oled_led1, OUTPUT);
    configure_IO(oled_led2, OUTPUT);
    set_led(oled_led1, HIGH);
    set_led(oled_led2, LOW);

    // set prescalar and enable timer. Page 206
    TCA0.SINGLE.CTRLA |= TCA_SINGLE_CLKSEL_DIV256_gc | TCA_SINGLE_ENABLE_bm;
    
    // enable interrupt on overflow. Page 215
    TCA0.SINGLE.INTCTRL |= TCA_SINGLE_OVF_bm;

    // set period. Page 220
    TCA0.SINGLE.PER = 0xFFF; // todo: replace with formula
    
    sei();

    while (true)
    {
        _delay_ms(0xFFFF);
    }
}

ISR(TCA0_OVF_vect)
{
    // clear interrupt bit
    TCA0.SINGLE.INTFLAGS |= (1 << 0);
    
    toggle_led(oled_led1);
    toggle_led(oled_led2);
}
