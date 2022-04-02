#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "io.h"

// In this exercise, you will use PWM to control the brightness of LEDs.
// Once we have PWM set up, controling the brightness is super easy!
//
// NB: These LEDs are on the OLED1 Xplained board!

void task6()
{
    // Set up the LEDs. You might want to copy this from previous
    // exercises.
    const IO oled_led1 = {&PORTD, PIN4};
    const IO oled_led2 = {&PORTD, PIN5};
    configure_IO(oled_led1, OUTPUT);
    configure_IO(oled_led2, OUTPUT);

    IO debug_led = {&PORTF, PIN5};
    configure_IO(debug_led, OUTPUT);

    // In dataheet:
    // Section 4.1, Multiplexed signals, we see that if we want to use TCA0 with
    // PD4 and PD5, we need to use portmux to change TCA to Port D. Look at the
    // PORTMUX.TCAROUTEA register for this and set it to the appropriate value.
    PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTD_gc;
    // WO4 WO5

    // We will be using timer TCA0 in Split (not Single) mode. We use Split mode
    // to output waveforms on WO4 and WO5, see Figure 4-1 in the Curiosity Nano
    // Hardware User Guide. It is highly recommended that you read
    // chapter 20.3.3.4 and 20.3.3.6 in the megaAVR® 0-series. There you will
    // find a sub-chapter on the single-slope PWM we will be using.
    //
    // First, set the split mode. Look in section 20.7.4 in the data sheet.
    TCA0.SPLIT.CTRLD |= 1;

    // Then, enable the TCA and set the prescaler. See section 20.7.1.
    TCA0.SPLIT.CTRLA |= TCA_SPLIT_CLKSEL_DIV256_gc | TCA_SPLIT_ENABLE_bm;

    // Enable high compare 1 and 2 to get output on WO4 and WO5. See
    // section 20.7.2.
    TCA0.SPLIT.CTRLB |= TCA_SPLIT_HCMP1EN_bp | TCA_SPLIT_HCMP2EN_bp;

    // Set period for high compare. See figures in datasheet. But this is the
    // PWM Period. See section 20.7.13.
    TCA0.SPLIT.HPER = 0xFF; // page 199 PER is resolution?

    // See figures in datasheet. This is the PWM duty cycle.
    TCA0.SPLIT.HCMP1 = 0x0F; // Max brightness (Leds are inverted)
    TCA0.SPLIT.HCMP2 = 0x00; // Min brightness (Leds are inverted)

    while (1)
    {
        _delay_ms(1000);
        toggle_led(debug_led);
        // Have some fun with the leds. Examples:
        // Have them fade between max and min
        // Have them fade in a pattern (Heartbeat?)
        // Change the brightness based on buttons
    }
}
