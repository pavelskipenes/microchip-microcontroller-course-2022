#include "adc.h"
#include "io.h"

void adc_init()
{
    // Here you need to initialize the ADC

    // Set resolution, we can choose 10 bits. Look in the ADC0.CTRLA register
    // (29.5.1)

    // Default is 10 bits
    // ADC0.CTRLA &= ~(ADC_RESSEL_10BIT_gc << 2);

    // Set number of samples to 4, look in the ADC0.CTRLB register
    ADC0.CTRLB |= ADC_SAMPNUM_ACC4_gc; // 4 samples

    // Select to use the supply voltage (VDD) as voltage reference. Look in the
    // ADC0.CTRLC register
    ADC0.CTRLC |= ADC_REFSEL_VDDREF_gc;
    // Enable the ADC
    ADC0.CTRLA |= ADC_ENABLE_bm;
}

uint16_t adc_read(uint8_t channel)
{
    // Choose the channel to read, look in ADC0.MUXPOS for how this is done
    ADC0.MUXPOS |= channel; // PD0 or AIN0

    // Clear the results ready flag in ADC0.INTFLAGS
    ADC0.INTFLAGS &= ~(1 << 0);
    // Start the conversion by modifying the ADC0.COMMAND register
    ADC0.COMMAND |= 1;

    // In a while loop, you want to wait for the results to be ready. This can
    // be done by checking the ADC0.INTFLAGS register
    while(!(ADC0.INTFLAGS & 0x1));

    // Finally, return the ADC results by returning the ADC0.RES register
    return (uint16_t)ADC0.RES;
}
