/*
 * CTU/PillScope project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "cfg.h"
#include "comm.h"
#include "proto.h"
#include "usbd_cdc_if.h"
#include "main.h"


#define SCPI_INPUT_BUFFER_LENGTH    256
#define SCPI_ERROR_QUEUE_SIZE       17


// respond
static void uart_put_str(const char* data, int len);
static void uart_put_char(const char data);


// scpi core
size_t SCPI_Write(scpi_t * context, const char * data, size_t len);
scpi_result_t SCPI_Flush(scpi_t * context);
int SCPI_Error(scpi_t * context, int_fast16_t err);
scpi_result_t SCPI_Control(scpi_t * context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val);
scpi_result_t SCPI_Reset(scpi_t * context);


const scpi_command_t scpi_commands[] = {
    /* IEEE Mandated Commands (SCPI std V1999.0 4.1.1) */
    { .pattern = "*CLS", .callback = SCPI_CoreCls,},
    { .pattern = "*ESE", .callback = SCPI_CoreEse,},
    { .pattern = "*ESE?", .callback = SCPI_CoreEseQ,},
    { .pattern = "*ESR?", .callback = SCPI_CoreEsrQ,},
    { .pattern = "*IDN?", .callback = SCPI_CoreIdnQ,},
    { .pattern = "*OPC", .callback = SCPI_CoreOpc,},
    { .pattern = "*OPC?", .callback = SCPI_CoreOpcQ,},
    { .pattern = "*RST", .callback = PS_Reset,},
    { .pattern = "*SRE", .callback = SCPI_CoreSre,},
    { .pattern = "*SRE?", .callback = SCPI_CoreSreQ,},
    { .pattern = "*STB?", .callback = SCPI_CoreStbQ,},
    //{ .pattern = "*TST?", .callback = My_CoreTstQ,},
    { .pattern = "*WAI", .callback = SCPI_CoreWai,},

    ///* Required SCPI commands (SCPI std V1999.0 4.2.1) */
    {.pattern = "SYSTem:ERRor[:NEXT]?", .callback = SCPI_SystemErrorNextQ,},
    {.pattern = "SYSTem:ERRor:COUNt?", .callback = SCPI_SystemErrorCountQ,},
    {.pattern = "SYSTem:VERSion?", .callback = SCPI_SystemVersionQ,},

    /* ULT - System */
    {.pattern = "SYSTem:MODE?", .callback = PS_System_ModeQ,},
    {.pattern = "SYSTem:MODE", .callback = PS_System_Mode,},
    {.pattern = "SYSTem:LIMits?", .callback = PS_System_LimitsQ,},

    /* ULT - Voltmeter */
    {.pattern = "VM:READ?", .callback = PS_VM_ReadQ,},

    /* ULT - Scope */
    {.pattern = "SCOPe:READ?", .callback = PS_SCOPE_ReadQ,},
    {.pattern = "SCOPe:SET?", .callback = PS_SCOPE_SetQ,},
    {.pattern = "SCOPe:SET", .callback = PS_SCOPE_Set,},

    /* ULT - Logic Analyzer */
    {.pattern = "LA:READ?", .callback = PS_LA_ReadQ,},
    {.pattern = "LA:SET?", .callback = PS_LA_SetQ,},
    {.pattern = "LA:SET", .callback = PS_LA_Set,},

    /* ULT - Counter */
    {.pattern = "CNTR:READ?", .callback = PS_CNTR_ReadQ,},

    /* ULT - Signal Generator */
    {.pattern = "SGEN:SET", .callback = PS_SGEN_Set,},

    /* ULT - PWM */
    {.pattern = "PWM:SET:CH?", .callback = PS_PWM_SetChQ,},
    {.pattern = "PWM:SET:CH", .callback = PS_PWM_SetCh,},
    {.pattern = "PWM:START:CH", .callback = PS_PWM_StartCh,}, // TODO reduce
    {.pattern = "PWM:STOP:CH", .callback = PS_PWM_StopCh,},


    SCPI_CMD_LIST_END
};

scpi_interface_t scpi_interface = {
    .error = SCPI_Error,
    .write = SCPI_Write,
    .control = SCPI_Control,
    .flush = SCPI_Flush,
    .reset = SCPI_Reset,
};

char scpi_input_buffer[SCPI_INPUT_BUFFER_LENGTH];
scpi_error_t scpi_error_queue_data[SCPI_ERROR_QUEUE_SIZE];
scpi_t scpi_context;


/************************* SCPI Core *************************/

size_t SCPI_Write(scpi_t * context, const char * data, size_t len)
{
    (void) context;

    return respond(data, len);
}

scpi_result_t SCPI_Flush(scpi_t * context)
{
    (void) context;

    return SCPI_RES_OK;
}

int SCPI_Error(scpi_t * context, int_fast16_t err)
{
    (void) context;

    char buff[100];
    int len = sprintf(buff, "**ERROR: %d, \"%s\"\r\n", (int16_t) err, SCPI_ErrorTranslate(err));
    respond(buff, len);
    return 0;
}

scpi_result_t SCPI_Control(scpi_t * context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val)
{
    (void) context;

    char buff[100];
    int len = 0;
    if (SCPI_CTRL_SRQ == ctrl)
        len = sprintf(buff, "**SRQ: 0x%X (%d)\r\n", val, val);
    else
        len = sprintf(buff, "**CTRL %02x: 0x%X (%d)\r\n", ctrl, val, val);

    respond(buff, len);
    return SCPI_RES_OK;
}

scpi_result_t SCPI_Reset(scpi_t * context)
{
    (void) context;

    respond("**Reset\r\n", 9);
    return SCPI_RES_OK;
}

/************************* Write Respond *************************/

void uart_put_text(const char* data)
{
    for (int i = 0; i < strlen(data); i++)
        uart_put_char(data[i]);
}

static void uart_put_char(const char data)
{
    while(!LL_USART_IsActiveFlag_TXE(PS_UART));
    LL_USART_TransmitData8(PS_UART, data);
}

static void uart_put_str(const char* data, int len)
{
    for (int i = 0; i < len; i++)
        uart_put_char(data[i]);
}

int respond(const char* data, int len)
{
    if (comm_d_uart.last)
    {
        uart_put_str(data, len);
        return len;
    }
    else if (comm_d_usb.last)
    {
        int cntr = 1000000;
        uint8_t ret = USBD_BUSY;
        while (ret == USBD_BUSY && cntr > 0)
        {
            ret = CDC_Transmit_FS((uint8_t *)data, len);
            cntr--;
        }

        return len;
    }
    return 0;
}

/************************* Main Comm *************************/

void comm_init(void)
{
    comm_d_uart.last = 0;
    comm_d_uart.available = 0;
    comm_d_uart.rx_index = 0;
    comm_d_usb.last = 0;
    comm_d_usb.available = 0;
    comm_d_usb.rx_index = 0;

    SCPI_Init(&scpi_context,
             scpi_commands,
             &scpi_interface,
             scpi_units_def,
             SCPI_IDN1, SCPI_IDN2, SCPI_IDN3, SCPI_IDN4,
             scpi_input_buffer, SCPI_INPUT_BUFFER_LENGTH,
             scpi_error_queue_data, SCPI_ERROR_QUEUE_SIZE);
}

uint8_t comm_main(void)
{
    if (comm_d_uart.available)
    {
        SCPI_Input(&scpi_context, comm_d_uart.rx_buffer, comm_d_uart.rx_index);

        memset(comm_d_uart.rx_buffer, 0, RX_BUFF_LEN * sizeof(char));
        comm_d_uart.rx_index = 0;
        comm_d_uart.available = 0;
        return 1;
    }
    else if (comm_d_usb.available)
    {
        SCPI_Input(&scpi_context, comm_d_usb.rx_buffer, comm_d_usb.rx_index);

        memset(comm_d_usb.rx_buffer, 0, RX_BUFF_LEN * sizeof(char));
        comm_d_usb.rx_index = 0;
        comm_d_usb.available = 0;
        return 1;
    }
    return 0;
}

