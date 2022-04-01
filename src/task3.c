#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

#include "io.h"

void task3()
{
    IO button = {&PORTF, PIN6};
    IO led = {&PORTF, PIN5};

    configure_IO(button, INPUT);
    configure_IO(led, OUTPUT);

    PORTF.PIN6CTRL |= (1 << PORT_PULLUPEN_bp);

    while (true)
    {
        while (!read_button_state(button))
        {
            _delay_us(1000);
        };
        toggle_led(led);
        while (read_button_state(button))
        {
            _delay_us(1000);
        };
    }
}
