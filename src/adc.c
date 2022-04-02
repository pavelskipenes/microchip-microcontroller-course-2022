#include <avr/io.h>

void adc_init() {
    // Set resolution, we choose 10 bits
    ADC0.CTRLA |= (ADC_RESSEL_10BIT_gc);

    // 4 samples
    ADC0.CTRLB |= (ADC_SAMPNUM_ACC4_gc);

    // Select to use the supply voltage (VDD) as voltage reference
    ADC0.CTRLC |= (ADC_REFSEL_VDDREF_gc);

    // Enable the ADC
    ADC0.CTRLA |= (ADC_ENABLE_bm);
}

uint16_t adc_read(uint8_t channel) {
    ADC0.MUXPOS |= channel;

    // Clear the results ready flag
    ADC0.INTFLAGS |= (ADC_RESRDY_bm);

    // Start a conversion
    ADC0.COMMAND |= (ADC_STCONV_bm);

    while (!(ADC0.INTFLAGS & ADC_RESRDY_bm)) {
        // Wait for the results ready flag to be set
    }

    return ADC0.RES;
}
