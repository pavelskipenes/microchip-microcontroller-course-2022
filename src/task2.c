#include <stdbool.h>

#include "io.h"

void task2()
{
    IO led = {&PORTF, PIN5};
    IO button = {&PORTF, PIN6};

    configure_IO(led, OUTPUT);
    configure_IO(button, INPUT);

    PORTF.PIN6CTRL |= (1 << PORT_PULLUPEN_bp);

    while (true)
    {
        if (read_button_state(button))
        {
            set_led(led, HIGH);
        }
        else
        {
            set_led(led, LOW);
        }
    }
}
