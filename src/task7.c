#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include <stdio.h>

#include "io.h"
#include "uart.h"
#include "adc.h"

#define KLAKK_ADC_CHANNEL 0x0

void uart_print_voltage(uint16_t data)
{
    data = data >> 2;

    uint8_t voltage_integer = data * 323ul / 100000ul;
    uint8_t voltage_fraction = (data * 323ul % 100000ul) / 1000;

    char uart_str[64] = "";

    sprintf(
        uart_str, "Voltage: %u.%02u V\r\n", voltage_integer, voltage_fraction);

    uart_transmit_string(uart_str);
}

void task7()
{
    IO uart_transmit_port = {&PORTB, PIN0};
    uart_init(uart_transmit_port);

    adc_init();
    uint16_t data;
    uart_transmit_string("Hello World!\r\n");

    while (true)
    {
        data = adc_read(KLAKK_ADC_CHANNEL);

        uart_print_voltage(data);
        _delay_ms(1000);
    }
}