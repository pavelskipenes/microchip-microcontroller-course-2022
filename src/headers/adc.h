#pragma once

#include <stdint.h>
#include <avr/io.h>

/**
 * @brief 
 * 
 */
void adc_init();

/**
 * @brief 
 * 
 * @param channel 
 * @return uint16_t 
 */
uint16_t adc_read(uint8_t channel);
