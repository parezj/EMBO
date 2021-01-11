################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/STM32Cube/PillScope/src/__OS/croutine.c \
F:/STM32Cube/PillScope/src/__OS/event_groups.c \
F:/STM32Cube/PillScope/src/__OS/list.c \
F:/STM32Cube/PillScope/src/__OS/port.c \
F:/STM32Cube/PillScope/src/__OS/queue.c \
F:/STM32Cube/PillScope/src/__OS/tasks.c \
F:/STM32Cube/PillScope/src/__OS/timers.c 

OBJS += \
./__OS/croutine.o \
./__OS/event_groups.o \
./__OS/list.o \
./__OS/port.o \
./__OS/queue.o \
./__OS/tasks.o \
./__OS/timers.o 

C_DEPS += \
./__OS/croutine.d \
./__OS/event_groups.d \
./__OS/list.d \
./__OS/port.d \
./__OS/queue.d \
./__OS/tasks.d \
./__OS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
__OS/croutine.o: F:/STM32Cube/PillScope/src/__OS/croutine.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F303xE -DDEBUG -DUSE_HAL_DRIVER -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I"F:/STM32Cube/PillScope/src/__App/Inc" -I"F:/STM32Cube/PillScope/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__OS/croutine.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__OS/event_groups.o: F:/STM32Cube/PillScope/src/__OS/event_groups.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F303xE -DDEBUG -DUSE_HAL_DRIVER -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I"F:/STM32Cube/PillScope/src/__App/Inc" -I"F:/STM32Cube/PillScope/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__OS/event_groups.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__OS/list.o: F:/STM32Cube/PillScope/src/__OS/list.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F303xE -DDEBUG -DUSE_HAL_DRIVER -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I"F:/STM32Cube/PillScope/src/__App/Inc" -I"F:/STM32Cube/PillScope/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__OS/list.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__OS/port.o: F:/STM32Cube/PillScope/src/__OS/port.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F303xE -DDEBUG -DUSE_HAL_DRIVER -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I"F:/STM32Cube/PillScope/src/__App/Inc" -I"F:/STM32Cube/PillScope/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__OS/port.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__OS/queue.o: F:/STM32Cube/PillScope/src/__OS/queue.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F303xE -DDEBUG -DUSE_HAL_DRIVER -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I"F:/STM32Cube/PillScope/src/__App/Inc" -I"F:/STM32Cube/PillScope/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__OS/queue.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__OS/tasks.o: F:/STM32Cube/PillScope/src/__OS/tasks.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F303xE -DDEBUG -DUSE_HAL_DRIVER -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I"F:/STM32Cube/PillScope/src/__App/Inc" -I"F:/STM32Cube/PillScope/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__OS/tasks.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__OS/timers.o: F:/STM32Cube/PillScope/src/__OS/timers.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F303xE -DDEBUG -DUSE_HAL_DRIVER -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I"F:/STM32Cube/PillScope/src/__App/Inc" -I"F:/STM32Cube/PillScope/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__OS/timers.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

