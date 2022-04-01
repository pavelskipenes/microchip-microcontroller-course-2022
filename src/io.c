#include "io.h"

void set_led(const IO led, const IO_Active active)
{
    led.port->OUT = active ? led.port->OUT & ~(1 << led.pin_number) : led.port->OUT | (1 << led.pin_number);
}

void configure_IO(const IO io, const IO_Direction dir)
{
    io.port->DIR = dir ? io.port->DIR | (1 << io.pin_number) : io.port->DIR & ~(1 << io.pin_number);
}

void toggle_led(const IO led){
    led.port->OUT ^= (1 << led.pin_number);
}

bool read_button_state(const IO button)
{
    return !(button.port->IN & (1 << button.pin_number));
}