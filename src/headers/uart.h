#pragma once

#include <stdint.h>

#include "io.h"


/**
 * @brief initialize UART
 * 
 * @param tx_port 
 */
void uart_init(IO tx_port);

/**
 * @brief Transmitt null terminated string
 * 
 * @param string 
 */
void uart_transmit_string(char *string);
