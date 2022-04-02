#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include <stdio.h>

#define BAUD_9600         ((4UL * F_CPU) / 9600)
#define TX_PORT           PORTB
#define TX_PIN            0
#define KLAKK_ADC_CHANNEL 0x0

// In this exercise we will set up and use USART communication to send ADC
// values from the KLAKK. The embedded debugger has a virtual com port that we
// will use to communicate with the computer.

void usart_init(unsigned long baud) {

    // In this function, we want to initialize the USART.
    // Chapter 23.3 in datasheet tells us how this is done:
    // You can see on the datasheet for Curiosity Nano that USART3 connects to
    // the usb.

    // Set TX pin as output

    // Fill in the baud rate in the 2 BAUD registers. (High and Low, you will
    // need to do some bit shifting here)

    // TX and RX in the CTRLB register
}

void usart_transmit(char data) {
    // In this function we will send data.

    // First we should check that there isn't already data being sent
    // if there is, we should wait for it to finish first. Check the STATUS
    // register for in order to see how this is checked. The idea is to run a
    // while loop while some bit in this register is low

    // Put our new data into the TXDATAL register
}

void usart_transmit_string(char *data) {
    // This function can take in a string and use the transmit function above
    // to transmit all the characters in this string
}

/**
 * This helper function is given to you in order to convert the ADC data to a
 * printable format.
 */
void usart_print_voltage(uint16_t data) {
    // We have 4 samples, so we want to divide by 4
    // Right shifting by 2 is equivalent to dividing an integer by 4
    data = data >> 2;

    // We have a 10-bit ADC measurement, so we have a value between 0 and 1023.
    // In order to go from the ADC value to voltage one thus has to do
    // (data / 1023) * 3.3V.
    //
    // But, as doing arithmetic with floats take a lot more space and time, we
    // do a trick in order to use integers.
    //    ((data * 1000) * (3.3 * 100) / 1023) = voltage * 1000 * 100
    // => (data * 330) / (1023 * 100) = voltage
    //
    // This is approximately:
    // (data * 323) / 100000 for the integer fraction

    uint8_t voltage_integer = data * 323ul / 100000ul;
    uint8_t voltage_fraction = (data * 323ul % 100000ul) / 1000;

    char uart_str[64] = "";
    // Format string and put voltage
    sprintf(
        uart_str, "Voltage: %u.%02u V\r\n", voltage_integer, voltage_fraction);

    usart_transmit_string(uart_str);
}

void adc_init() {
    // Here you need to initialize the ADC

    // Set resolution, we can choose 10 bits. Look in the ADC0.CTRLA register
    // (29.5.1)

    // Set number of samples to 4, look in the ADC0.CTRLB register

    // Select to use the supply voltage (VDD) as voltage reference. Look in the
    // ADC0.CTRLC register

    // Enable the ADC
}

uint16_t adc_read(uint8_t channel) {
    // Choose the channel to read, look in ADC0.MUXPOS for how this is done

    // Clear the results ready flag in ADC0.INTFLAGS

    // Start the conversion by modifying the ADC0.COMMAND register

    // In a while loop, you want to wait for the results to be ready. This can
    // be done by checking the ADC0.INTFLAGS register

    // Finally, return the ADC results by returning the ADC0.RES register
}

void task7() {
    // Initialize the USART with our function.
    // We will be using a baudrate of 9600 (defined as BAUD_9600 at the top of
    // the file)

    // Initialize the ADC
	
    while (1) {
        // Read the ADC value from the KLAKK_ADC_CHANNEl. Remember that the
        // function returns a 16-bit integer

        // Print the ADC value by using usart_print_voltage
    }
}