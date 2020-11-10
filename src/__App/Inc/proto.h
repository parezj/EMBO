/*
 * CTU/UniLabTool project
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef PROTO_H
#define PROTO_H

#include "scpi/scpi.h"

scpi_result_t ULT_System_Mode(scpi_t * context);
scpi_result_t ULT_System_ModeQ(scpi_t * context);

scpi_result_t ULT_VM_ReadAll(scpi_t * context);

scpi_result_t ULT_SCOPE_ReadAll(scpi_t * context);

scpi_result_t ULT_PWM_SetChQ(scpi_t * context);
scpi_result_t ULT_PWM_SetCh(scpi_t * context);
scpi_result_t ULT_PWM_StartCh(scpi_t * context);
scpi_result_t ULT_PWM_StopCh(scpi_t * context);

#endif /* PROTO_H */
