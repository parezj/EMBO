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
#ifdef PS_USB
#include "usbd_cdc_if.h"
#endif
#include "main.h"


#define SCPI_INPUT_BUFFER_LENGTH    256
#define SCPI_ERROR_QUEUE_SIZE       17


// respond
static void uart_put_str(const char* data, int len);
static void uart_put_char(const char data);


// scpi core
scpi_result_t SCPI_CoreIdnQ(scpi_t * context);
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
    {.pattern = "CNTR:ENABLE", .callback = PS_CNTR_Enable,},
    {.pattern = "CNTR:READ?", .callback = PS_CNTR_ReadQ,},

    /* ULT - Signal Generator */
    {.pattern = "SGEN:SET", .callback = PS_SGEN_Set,},

    /* ULT - PWM */
    {.pattern = "PWM:SET?", .callback = PS_PWM_SetQ,},
    {.pattern = "PWM:SET", .callback = PS_PWM_Set,},


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

    return comm_respond((comm_data_t*)context->comm, data, len);
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
    comm_respond((comm_data_t*)context->comm, buff, len);
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

    comm_respond((comm_data_t*)context->comm, buff, len);
    return SCPI_RES_OK;
}

scpi_result_t SCPI_Reset(scpi_t * context)
{
    (void) context;

    comm_respond((comm_data_t*)context->comm, "**Reset\r\n", 9);
    return SCPI_RES_OK;
}

scpi_result_t SCPI_CoreIdnQ(scpi_t * context)
{
    int i;
    for (i = 0; i < 4; i++) {
        if (context->idn[i])
        {
            int j = i;
            if (i == 1 && ((comm_data_t*)(context->comm))->uart.available)
                j = 4;
            else if (i == 1) // comm_data_usb.available
                j = 5;

            SCPI_ResultMnemonic(context, context->idn[j]);
        } else {
            SCPI_ResultMnemonic(context, "0");
        }
    }
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

/************************* Main Comm *************************/

void comm_init(comm_data_t* self)
{
    self->uart.last = 0;
    self->uart.available = 0;
    self->uart.rx_index = 0;
    self->usb.last = 0;
    self->usb.available = 0;
    self->usb.rx_index = 0;
    comm_ptr = self;

    SCPI_Init(&scpi_context,
              scpi_commands,
              &scpi_interface,
              scpi_units_def,
              SCPI_IDN1, SCPI_IDN2, SCPI_IDN3, SCPI_IDN4,
              scpi_input_buffer, SCPI_INPUT_BUFFER_LENGTH,
              scpi_error_queue_data, SCPI_ERROR_QUEUE_SIZE,
              self);

    LL_USART_EnableIT_RXNE(PS_UART);
    uart_put_text(WELCOME_STR);

    NVIC_SetPriority(PS_IRQN_UART, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), PS_IT_PRI_UART, 0));
    NVIC_EnableIRQ(PS_IRQN_UART);
}

uint8_t comm_main(comm_data_t* self)
{
    if (self->uart.available)
    {
        SCPI_Input(&scpi_context, self->uart.rx_buffer, self->uart.rx_index);

        memset(self->uart.rx_buffer, 0, RX_BUFF_LEN * sizeof(char));
        self->uart.rx_index = 0;
        self->uart.available = 0;
        return 1;
    }
#ifdef PS_USB
    else if (self->usb.available)
    {
        SCPI_Input(&scpi_context, self->usb.rx_buffer, self->usb.rx_index);

        memset(self->usb.rx_buffer, 0, RX_BUFF_LEN * sizeof(char));
        self->usb.rx_index = 0;
        self->usb.available = 0;
        return 1;
    }
#endif
    return 0;
}

int comm_respond(comm_data_t* self, const char* data, int len)
{
    if (self->uart.last)
    {
        uart_put_str(data, len);
        return len;
    }
#ifdef PS_USB
    else if (self->usb.last)
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
#endif
    return 0;
}
