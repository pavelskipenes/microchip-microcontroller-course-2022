#include <stdbool.h>
#include <util/delay.h>

#include "io.h"

void task4()
{
    const IO oled_led1 = {&PORTD, PIN4};
    const IO oled_led2 = {&PORTD, PIN5};
    const IO oled_led3 = {&PORTC, PIN5};

    const IO oled_button1 = {&PORTC, PIN2};
    const IO oled_button2 = {&PORTD, PIN1};
    const IO oled_button3 = {&PORTD, PIN2};

    configure_IO(oled_led1, OUTPUT);
    configure_IO(oled_led2, OUTPUT);
    configure_IO(oled_led3, OUTPUT);

    configure_IO(oled_button1, INPUT);
    configure_IO(oled_button2, INPUT);
    configure_IO(oled_button3, INPUT);

    // Enable pull-ups on the buttons
    PORTC_PIN2CTRL = PORTD_PIN1CTRL = PORTD_PIN2CTRL = PORT_PULLUPEN_bm;

    set_led(oled_led1, LOW);
    set_led(oled_led2, LOW);
    set_led(oled_led3, LOW);

    while (true)
    {
        if (read_button_state(oled_button1))
        {
            set_led(oled_led1, HIGH);
            set_led(oled_led2, LOW);
            set_led(oled_led3, LOW);
            continue;
        }
        if (read_button_state(oled_button2))
        {
            set_led(oled_led1, LOW);
            set_led(oled_led2, HIGH);
            set_led(oled_led3, LOW);
            continue;
        }
        if (read_button_state(oled_button3))
        {
            set_led(oled_led1, LOW);
            set_led(oled_led2, LOW);
            set_led(oled_led3, HIGH);
        }
        _delay_us(1000);
    }
}
