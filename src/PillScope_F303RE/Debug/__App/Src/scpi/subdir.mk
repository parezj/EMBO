################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/STM32Cube/PillScope/src/__App/Src/scpi/error.c \
F:/STM32Cube/PillScope/src/__App/Src/scpi/expression.c \
F:/STM32Cube/PillScope/src/__App/Src/scpi/fifo.c \
F:/STM32Cube/PillScope/src/__App/Src/scpi/ieee488.c \
F:/STM32Cube/PillScope/src/__App/Src/scpi/lexer.c \
F:/STM32Cube/PillScope/src/__App/Src/scpi/minimal.c \
F:/STM32Cube/PillScope/src/__App/Src/scpi/parser.c \
F:/STM32Cube/PillScope/src/__App/Src/scpi/units.c \
F:/STM32Cube/PillScope/src/__App/Src/scpi/utils.c 

OBJS += \
./__App/Src/scpi/error.o \
./__App/Src/scpi/expression.o \
./__App/Src/scpi/fifo.o \
./__App/Src/scpi/ieee488.o \
./__App/Src/scpi/lexer.o \
./__App/Src/scpi/minimal.o \
./__App/Src/scpi/parser.o \
./__App/Src/scpi/units.o \
./__App/Src/scpi/utils.o 

C_DEPS += \
./__App/Src/scpi/error.d \
./__App/Src/scpi/expression.d \
./__App/Src/scpi/fifo.d \
./__App/Src/scpi/ieee488.d \
./__App/Src/scpi/lexer.d \
./__App/Src/scpi/minimal.d \
./__App/Src/scpi/parser.d \
./__App/Src/scpi/units.d \
./__App/Src/scpi/utils.d 


# Each subdirectory must supply rules for building sources it contributes
__App/Src/scpi/error.o: F:/STM32Cube/PillScope/src/__App/Src/scpi/error.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F303xE -DDEBUG -DUSE_HAL_DRIVER -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I"F:/STM32Cube/PillScope/src/__App/Inc" -I"F:/STM32Cube/PillScope/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/scpi/error.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__App/Src/scpi/expression.o: F:/STM32Cube/PillScope/src/__App/Src/scpi/expression.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F303xE -DDEBUG -DUSE_HAL_DRIVER -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I"F:/STM32Cube/PillScope/src/__App/Inc" -I"F:/STM32Cube/PillScope/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/scpi/expression.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__App/Src/scpi/fifo.o: F:/STM32Cube/PillScope/src/__App/Src/scpi/fifo.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F303xE -DDEBUG -DUSE_HAL_DRIVER -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I"F:/STM32Cube/PillScope/src/__App/Inc" -I"F:/STM32Cube/PillScope/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/scpi/fifo.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__App/Src/scpi/ieee488.o: F:/STM32Cube/PillScope/src/__App/Src/scpi/ieee488.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F303xE -DDEBUG -DUSE_HAL_DRIVER -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I"F:/STM32Cube/PillScope/src/__App/Inc" -I"F:/STM32Cube/PillScope/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/scpi/ieee488.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__App/Src/scpi/lexer.o: F:/STM32Cube/PillScope/src/__App/Src/scpi/lexer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F303xE -DDEBUG -DUSE_HAL_DRIVER -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I"F:/STM32Cube/PillScope/src/__App/Inc" -I"F:/STM32Cube/PillScope/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/scpi/lexer.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__App/Src/scpi/minimal.o: F:/STM32Cube/PillScope/src/__App/Src/scpi/minimal.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F303xE -DDEBUG -DUSE_HAL_DRIVER -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I"F:/STM32Cube/PillScope/src/__App/Inc" -I"F:/STM32Cube/PillScope/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/scpi/minimal.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__App/Src/scpi/parser.o: F:/STM32Cube/PillScope/src/__App/Src/scpi/parser.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F303xE -DDEBUG -DUSE_HAL_DRIVER -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I"F:/STM32Cube/PillScope/src/__App/Inc" -I"F:/STM32Cube/PillScope/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/scpi/parser.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__App/Src/scpi/units.o: F:/STM32Cube/PillScope/src/__App/Src/scpi/units.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F303xE -DDEBUG -DUSE_HAL_DRIVER -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I"F:/STM32Cube/PillScope/src/__App/Inc" -I"F:/STM32Cube/PillScope/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/scpi/units.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
__App/Src/scpi/utils.o: F:/STM32Cube/PillScope/src/__App/Src/scpi/utils.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F303xE -DDEBUG -DUSE_HAL_DRIVER -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I"F:/STM32Cube/PillScope/src/__App/Inc" -I"F:/STM32Cube/PillScope/src/__OS/include" -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/scpi/utils.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

