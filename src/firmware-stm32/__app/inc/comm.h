/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef COMM_H
#define COMM_H

#include "cfg.h"

#include "scpi/scpi.h"

#define RX_BUFF_LEN    200
#define RX_BUFF_LAST   RX_BUFF_LEN - 1

#define APP_RX_DATA_SIZE  RX_BUFF_LEN
#define APP_TX_DATA_SIZE  1

#ifndef EMBO
#define EM_TRUE                1
#define EM_FALSE               0
#define SCPI_IDN1              "Author"
#define SCPI_IDN2              "Device"
#define SCPI_IDN3              "0.0.1"
#define SCPI_IDN4              "0"
#define EM_UART                USART2               // UART periph
#define EM_UART_RX_IRQHandler  USART2_IRQHandler    // UART IRQ handler
#define EM_UART_CLEAR_FLAG(x)  LL_USART_ClearFlag_RTO(x);  // RTO flags needs clearing
//#define EM_UART_CLEAR_FLAG(x)  LL_USART_ClearFlag_RXNE(x);  // RXNE flags needs clearing
#define EM_USB                                      // if emulated USB enabled
#define EM_UART_POLLINIT                            // if defined poll for init
#endif


void uart_put_text(const char* data);

extern const scpi_command_t scpi_commands[];
extern scpi_interface_t scpi_interface;
extern char scpi_input_buffer[];
extern scpi_error_t scpi_error_queue_data[];
extern scpi_t scpi_context;

size_t SCPI_Write(scpi_t * context, const char * data, size_t len);
int SCPI_Error(scpi_t * context, int_fast16_t err);
scpi_result_t SCPI_Reset(scpi_t * context);
scpi_result_t SCPI_Flush(scpi_t * context);


typedef struct
{
    char rx_buffer[RX_BUFF_LEN];

    uint8_t last;
    uint8_t available;
    uint8_t rx_index;
}comm_ch_t;

typedef struct
{
    comm_ch_t usb;
    comm_ch_t uart;
}comm_data_t;


comm_data_t* comm_ptr;

void comm_init(comm_data_t* self);
uint8_t comm_main(comm_data_t* self);
int comm_respond(comm_data_t* self, const char* data, int len);
void comm_daq_ready(comm_data_t* self, const char* rdy, uint32_t pos_frst);

#endif
