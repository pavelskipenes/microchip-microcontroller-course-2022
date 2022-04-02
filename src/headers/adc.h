/*
 * adc.h
 *
 * Created: 27.02.2017 16:51:27
 *  Author: Petter
 */ 
#pragma once
#include <stdint.h>

void adc_init(void);

uint16_t adc_read(uint8_t channel);
