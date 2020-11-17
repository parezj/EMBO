/*
 * CTU/PillScope project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef PROTO_H
#define PROTO_H

#include "scpi/scpi.h"

scpi_result_t PS_System_Mode(scpi_t * context);
scpi_result_t PS_System_ModeQ(scpi_t * context);

scpi_result_t PS_VM_ReadQ(scpi_t * context);

scpi_result_t PS_SCOPE_Set(scpi_t * context);
scpi_result_t PS_SCOPE_SetQ(scpi_t * context);
scpi_result_t PS_SCOPE_ReadQ(scpi_t * context);

scpi_result_t PS_LA_Set(scpi_t * context);
scpi_result_t PS_LA_SetQ(scpi_t * context);
scpi_result_t PS_LA_ReadQ(scpi_t * context);

scpi_result_t PS_CNTR_ReadQ(scpi_t * context);

scpi_result_t PS_SGEN_Set(scpi_t * context);

scpi_result_t PS_PWM_SetChQ(scpi_t * context);
scpi_result_t PS_PWM_SetCh(scpi_t * context);
scpi_result_t PS_PWM_StartCh(scpi_t * context);
scpi_result_t PS_PWM_StopCh(scpi_t * context);

#endif /* PROTO_H */
