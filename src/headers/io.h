#pragma once
#include <avr/io.h>
#include <stdbool.h>

typedef struct IO_t
{
    PORT_t *port;
    int pin_number;
} IO;

typedef enum IO_Direction_t
{
    INPUT,
    OUTPUT
} IO_Direction;

typedef enum IO_Active_t
{
    LOW,
    HIGH
} IO_Active;

/**
 * @brief Set the led HIGH or LOW
 * 
 * @param led of the target pin. Pin needs to be configured as output. @see configure_IO
 * @param active HIGH or LOW
 */
void set_led(const IO led, const IO_Active active);

/**
 * @brief 
 * 
 * @param io of the target pin
 * @param dir INPUT or OUTPUT
 */
void configure_IO(const IO io, const IO_Direction dir);

/**
 * @brief toggle led
 * 
 * @param led 
 */
void toggle_led(const IO led);

/**
 * @brief 
 * 
 * @param button 
 * @return true 
 * @return false 
 */
bool read_button_state(const IO button);
