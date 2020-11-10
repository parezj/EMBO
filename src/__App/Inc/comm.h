/*
 * CTU/UniLabTool project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef COMM_H
#define COMM_H

#include "cfg.h"
#include "scpi/scpi.h"

#define RX_BUFF_LEN    100
#define RX_BUFF_LAST   RX_BUFF_LEN - 1


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

    uint8_t available;
    uint8_t rx_index;
}comm_data_t;


comm_data_t comm_d_usb;
comm_data_t comm_d_uart;


void comm_init(void);
uint8_t comm_main(void);

#endif
