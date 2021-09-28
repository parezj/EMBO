/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef COMM_PROTO_H
#define COMM_PROTO_H

#include "scpi/scpi.h"

scpi_result_t EM_Reset(scpi_t * context);

scpi_result_t EM_SYS_Mode(scpi_t * context);
scpi_result_t EM_SYS_ModeQ(scpi_t * context);
scpi_result_t EM_SYS_LimitsQ(scpi_t * context);
scpi_result_t EM_SYS_InfoQ(scpi_t * context);
scpi_result_t EM_SYS_UptimeQ(scpi_t* context);

scpi_result_t EM_VM_ReadQ(scpi_t * context);

scpi_result_t EM_SCOPE_Set(scpi_t * context);
scpi_result_t EM_SCOPE_SetQ(scpi_t * context);
scpi_result_t EM_SCOPE_ReadQ(scpi_t * context);
scpi_result_t EM_SCOPE_ForceTrig(scpi_t * context);

scpi_result_t EM_LA_Set(scpi_t * context);
scpi_result_t EM_LA_SetQ(scpi_t * context);
scpi_result_t EM_LA_ReadQ(scpi_t * context);
scpi_result_t EM_LA_ForceTrig(scpi_t * context);

scpi_result_t EM_CNTR_SetQ(scpi_t * context);
scpi_result_t EM_CNTR_Set(scpi_t * context);
scpi_result_t EM_CNTR_ReadQ(scpi_t * context);

scpi_result_t EM_SGEN_SetQ(scpi_t * context);
scpi_result_t EM_SGEN_Set(scpi_t * context);

scpi_result_t EM_PWM_SetQ(scpi_t * context);
scpi_result_t EM_PWM_Set(scpi_t * context);


#endif /* COMM_PROTO_H */
