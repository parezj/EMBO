################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/STM32Cube/UniLabTool/src/__App/Src/app.c \
F:/STM32Cube/UniLabTool/src/__App/Src/comm.c \
F:/STM32Cube/UniLabTool/src/__App/Src/irq.c \
F:/STM32Cube/UniLabTool/src/__App/Src/periph.c \
F:/STM32Cube/UniLabTool/src/__App/Src/proto.c \
F:/STM32Cube/UniLabTool/src/__App/Src/utils.c 

OBJS += \
./__App/Src/app.o \
./__App/Src/comm.o \
./__App/Src/irq.o \
./__App/Src/periph.o \
./__App/Src/proto.o \
./__App/Src/utils.o 

C_DEPS += \
./__App/Src/app.d \
./__App/Src/comm.d \
./__App/Src/irq.d \
./__App/Src/periph.d \
./__App/Src/proto.d \
./__App/Src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
__App/Src/app.o: F:/STM32Cube/UniLabTool/src/__App/Src/app.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/UniLabTool/src/__App/Inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/app.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__App/Src/comm.o: F:/STM32Cube/UniLabTool/src/__App/Src/comm.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/UniLabTool/src/__App/Inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/comm.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__App/Src/irq.o: F:/STM32Cube/UniLabTool/src/__App/Src/irq.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/UniLabTool/src/__App/Inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/irq.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__App/Src/periph.o: F:/STM32Cube/UniLabTool/src/__App/Src/periph.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/UniLabTool/src/__App/Inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/periph.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__App/Src/proto.o: F:/STM32Cube/UniLabTool/src/__App/Src/proto.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/UniLabTool/src/__App/Inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/proto.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__App/Src/utils.o: F:/STM32Cube/UniLabTool/src/__App/Src/utils.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/UniLabTool/src/__App/Inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__App/Src/utils.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

