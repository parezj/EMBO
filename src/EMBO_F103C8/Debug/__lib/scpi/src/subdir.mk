################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/STM32Cube/EMBO/src/__Lib/scpi/src/error.c \
F:/STM32Cube/EMBO/src/__Lib/scpi/src/expression.c \
F:/STM32Cube/EMBO/src/__Lib/scpi/src/fifo.c \
F:/STM32Cube/EMBO/src/__Lib/scpi/src/ieee488.c \
F:/STM32Cube/EMBO/src/__Lib/scpi/src/lexer.c \
F:/STM32Cube/EMBO/src/__Lib/scpi/src/minimal.c \
F:/STM32Cube/EMBO/src/__Lib/scpi/src/parser.c \
F:/STM32Cube/EMBO/src/__Lib/scpi/src/units.c \
F:/STM32Cube/EMBO/src/__Lib/scpi/src/utils.c 

OBJS += \
./__lib/scpi/src/error.o \
./__lib/scpi/src/expression.o \
./__lib/scpi/src/fifo.o \
./__lib/scpi/src/ieee488.o \
./__lib/scpi/src/lexer.o \
./__lib/scpi/src/minimal.o \
./__lib/scpi/src/parser.o \
./__lib/scpi/src/units.o \
./__lib/scpi/src/utils.o 

C_DEPS += \
./__lib/scpi/src/error.d \
./__lib/scpi/src/expression.d \
./__lib/scpi/src/fifo.d \
./__lib/scpi/src/ieee488.d \
./__lib/scpi/src/lexer.d \
./__lib/scpi/src/minimal.d \
./__lib/scpi/src/parser.d \
./__lib/scpi/src/units.d \
./__lib/scpi/src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
__lib/scpi/src/error.o: F:/STM32Cube/EMBO/src/__Lib/scpi/src/error.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__lib/scpi/src/error.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__lib/scpi/src/expression.o: F:/STM32Cube/EMBO/src/__Lib/scpi/src/expression.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__lib/scpi/src/expression.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__lib/scpi/src/fifo.o: F:/STM32Cube/EMBO/src/__Lib/scpi/src/fifo.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__lib/scpi/src/fifo.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__lib/scpi/src/ieee488.o: F:/STM32Cube/EMBO/src/__Lib/scpi/src/ieee488.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__lib/scpi/src/ieee488.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__lib/scpi/src/lexer.o: F:/STM32Cube/EMBO/src/__Lib/scpi/src/lexer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__lib/scpi/src/lexer.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__lib/scpi/src/minimal.o: F:/STM32Cube/EMBO/src/__Lib/scpi/src/minimal.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__lib/scpi/src/minimal.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__lib/scpi/src/parser.o: F:/STM32Cube/EMBO/src/__Lib/scpi/src/parser.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__lib/scpi/src/parser.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__lib/scpi/src/units.o: F:/STM32Cube/EMBO/src/__Lib/scpi/src/units.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__lib/scpi/src/units.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__lib/scpi/src/utils.o: F:/STM32Cube/EMBO/src/__Lib/scpi/src/utils.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__lib/scpi/src/utils.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

