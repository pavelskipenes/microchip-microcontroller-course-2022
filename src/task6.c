#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#include "io.h"

void task6()
{
    const IO oled_led1 = {&PORTD, PIN4};
    const IO oled_led2 = {&PORTD, PIN5};
    configure_IO(oled_led1, OUTPUT);
    configure_IO(oled_led2, OUTPUT);

    IO debug_led = {&PORTF, PIN5};
    configure_IO(debug_led, OUTPUT);

    // reroute output to port D
    PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTD_gc;

    // Set TCA in split mode
    TCA0.SPLIT.CTRLD |= TCA_SPLIT_ENABLE_bm;
    
    // Then, enable the TCA and set the prescaler. See section 20.7.1.
    TCA0.SPLIT.CTRLA |= TCA_SPLIT_CLKSEL_DIV256_gc | TCA_SPLIT_ENABLE_bm;

    // Enable high compare 1 and 2 to get output on WO4 and WO5. See
    // section 20.7.2.
    TCA0.SPLIT.CTRLB |= TCA_SPLIT_HCMP1EN_bm | TCA_SPLIT_HCMP2EN_bm;

    // set period
    TCA0.SPLIT.HPER = 0xFF;

    TCA0.SPLIT.HCMP1 = 0x00; // Max brightness (Leds are inverted)
    TCA0.SPLIT.HCMP2 = 0xFF; // Min brightness (Leds are inverted)

    while (true)
    {
        if (!TCA0.SPLIT.HCNT)
        {
            TCA0.SPLIT.HCMP1 += 0x1;
            TCA0.SPLIT.HCMP2 -= 0x1;
        }
        _delay_us(100);
    }
}
