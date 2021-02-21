################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/STM32Cube/EMBO/src/__App/Src/app.c \
F:/STM32Cube/EMBO/src/__App/Src/cfg.c \
F:/STM32Cube/EMBO/src/__App/Src/cntr.c \
F:/STM32Cube/EMBO/src/__App/Src/cntr_irq.c \
F:/STM32Cube/EMBO/src/__App/Src/comm.c \
F:/STM32Cube/EMBO/src/__App/Src/comm_irq.c \
F:/STM32Cube/EMBO/src/__App/Src/daq.c \
F:/STM32Cube/EMBO/src/__App/Src/daq_irq.c \
F:/STM32Cube/EMBO/src/__App/Src/daq_trig.c \
F:/STM32Cube/EMBO/src/__App/Src/irq.c \
F:/STM32Cube/EMBO/src/__App/Src/led.c \
F:/STM32Cube/EMBO/src/__App/Src/periph.c \
F:/STM32Cube/EMBO/src/__App/Src/proto.c \
F:/STM32Cube/EMBO/src/__App/Src/pwm.c \
F:/STM32Cube/EMBO/src/__App/Src/sgen.c \
F:/STM32Cube/EMBO/src/__App/Src/utility.c 

OBJS += \
./__App/Src/app.o \
./__App/Src/cfg.o \
./__App/Src/cntr.o \
./__App/Src/cntr_irq.o \
./__App/Src/comm.o \
./__App/Src/comm_irq.o \
./__App/Src/daq.o \
./__App/Src/daq_irq.o \
./__App/Src/daq_trig.o \
./__App/Src/irq.o \
./__App/Src/led.o \
./__App/Src/periph.o \
./__App/Src/proto.o \
./__App/Src/pwm.o \
./__App/Src/sgen.o \
./__App/Src/utility.o 

C_DEPS += \
./__App/Src/app.d \
./__App/Src/cfg.d \
./__App/Src/cntr.d \
./__App/Src/cntr_irq.d \
./__App/Src/comm.d \
./__App/Src/comm_irq.d \
./__App/Src/daq.d \
./__App/Src/daq_irq.d \
./__App/Src/daq_trig.d \
./__App/Src/irq.d \
./__App/Src/led.d \
./__App/Src/periph.d \
./__App/Src/proto.d \
./__App/Src/pwm.d \
./__App/Src/sgen.d \
./__App/Src/utility.d 


# Each subdirectory must supply rules for building sources it contributes
__App/Src/app.o: F:/STM32Cube/EMBO/src/__App/Src/app.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Core/Inc -I"F:/STM32Cube/EMBO/src/__App/Inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/app.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__App/Src/cfg.o: F:/STM32Cube/EMBO/src/__App/Src/cfg.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Core/Inc -I"F:/STM32Cube/EMBO/src/__App/Inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/cfg.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__App/Src/cntr.o: F:/STM32Cube/EMBO/src/__App/Src/cntr.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Core/Inc -I"F:/STM32Cube/EMBO/src/__App/Inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/cntr.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__App/Src/cntr_irq.o: F:/STM32Cube/EMBO/src/__App/Src/cntr_irq.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Core/Inc -I"F:/STM32Cube/EMBO/src/__App/Inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/cntr_irq.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__App/Src/comm.o: F:/STM32Cube/EMBO/src/__App/Src/comm.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Core/Inc -I"F:/STM32Cube/EMBO/src/__App/Inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/comm.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__App/Src/comm_irq.o: F:/STM32Cube/EMBO/src/__App/Src/comm_irq.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Core/Inc -I"F:/STM32Cube/EMBO/src/__App/Inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/comm_irq.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__App/Src/daq.o: F:/STM32Cube/EMBO/src/__App/Src/daq.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Core/Inc -I"F:/STM32Cube/EMBO/src/__App/Inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/daq.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__App/Src/daq_irq.o: F:/STM32Cube/EMBO/src/__App/Src/daq_irq.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Core/Inc -I"F:/STM32Cube/EMBO/src/__App/Inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/daq_irq.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__App/Src/daq_trig.o: F:/STM32Cube/EMBO/src/__App/Src/daq_trig.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Core/Inc -I"F:/STM32Cube/EMBO/src/__App/Inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/daq_trig.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__App/Src/irq.o: F:/STM32Cube/EMBO/src/__App/Src/irq.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Core/Inc -I"F:/STM32Cube/EMBO/src/__App/Inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/irq.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__App/Src/led.o: F:/STM32Cube/EMBO/src/__App/Src/led.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Core/Inc -I"F:/STM32Cube/EMBO/src/__App/Inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/led.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__App/Src/periph.o: F:/STM32Cube/EMBO/src/__App/Src/periph.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Core/Inc -I"F:/STM32Cube/EMBO/src/__App/Inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/periph.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__App/Src/proto.o: F:/STM32Cube/EMBO/src/__App/Src/proto.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Core/Inc -I"F:/STM32Cube/EMBO/src/__App/Inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/proto.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__App/Src/pwm.o: F:/STM32Cube/EMBO/src/__App/Src/pwm.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Core/Inc -I"F:/STM32Cube/EMBO/src/__App/Inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/pwm.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__App/Src/sgen.o: F:/STM32Cube/EMBO/src/__App/Src/sgen.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Core/Inc -I"F:/STM32Cube/EMBO/src/__App/Inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/sgen.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__App/Src/utility.o: F:/STM32Cube/EMBO/src/__App/Src/utility.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../Core/Inc -I"F:/STM32Cube/EMBO/src/__App/Inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/utility.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

