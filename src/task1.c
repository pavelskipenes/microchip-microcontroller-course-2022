#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#include "io.h"

void task1()
{
    IO led = {&PORTF, PIN5};
    configure_IO(led, OUTPUT);

    while (true)
    {
        toggle_led(led);
        _delay_ms(1000);
    }
}
