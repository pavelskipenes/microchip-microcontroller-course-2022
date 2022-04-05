#include "uart.h"

/**
 * The USART transmitter sends data by periodically driving the transmission line low. The data transmission is initiated
 * by loading the Transmit Data (USARTn.TXDATAL and USARTn.TXDATAH) registers with the data to be sent. The
 * data in the Transmit Data registers are moved to the TX Buffer once it is empty and onwards to the Shift register
 * once it is empty and ready to send a new frame. After the Shift register is loaded with data, the data frame will be
 * transmitted.
 * 
 * When the entire frame in the Shift register has been shifted out, and there are no new data present in the Transmit
 * Data registers or the TX Buffer, the Transmit Complete Interrupt Flag (the TXCIF bit in the USARTn.STATUS register)
 * is set, and the interrupt is generated if it is enabled.
 * 
 * The Transmit Data registers can only be written when the Data Register Empty Interrupt Flag (the DREIF bit in the
 * USARTn.STATUS register) is set, indicating that they are empty and ready for new data.
 * 
 * When using frames with fewer than eight bits, the Most Significant bits (MSb) written to the Transmit Data registers
 * are ignored. When the Character Size (CHSIZE) bit field in the Control C (USARTn.CTRLC) register is configured
 * to 9-bit (low byte first), the Transmit Data Register Low Byte (TXDATAL) must be written before the Transmit Data
 * Register High Byte (TXDATAH). When CHSIZE is configured to 9-bit (high byte first), TXDATAH must be written
 * before TXDATAL.
 * 
 */

// static unsigned long get_async_baud_register_value(unsigned long baud_rate){
//     return (64UL * F_CPU) / (16UL * baud_rate); // async / UART
// }

#define BAUD_9600 (4UL * F_CPU/ 9600UL)

void uart_init(IO tx_port)
{
    /*
    Initialization
        Full-Duplex Mode:
        1. Set the baud rate (USARTn.BAUD).
        2. Set the frame format and mode of operation (USARTn.CTRLC).
        3. Configure the TXD pin as an output.
        4. Enable the transmitter and the receiver (USARTn.CTRLB).
    */
    USART3.BAUD = BAUD_9600;

    USART0.CTRLC &= ~(3 << 6); // Communication mode: normal mode

    // USART0.CTRLC &= ~(3 << 4); // Parity: Disabled

    // USART0.CTRLC &= ~(1 << 3); // Stop Bits: 1 Bit

    // USART0.CTRLC |= (3 << 0); // frame size: 8 bits

    configure_IO(tx_port, OUTPUT);

    USART3.CTRLB |= USART_RXEN_bm | USART_TXEN_bm;
}

static void uart_transmit(char data)
{
    bool empty = USART3.STATUS & USART_DREIF_bm;
    while (!empty)
    {
        empty = USART3.STATUS & USART_DREIF_bm;
    }

    USART3.TXDATAL = data;
}

void uart_transmit_string(char *data)
{
    while (*data)
    {
        uart_transmit(*data++);
    }
}
