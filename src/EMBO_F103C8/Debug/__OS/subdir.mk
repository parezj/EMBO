################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/STM32Cube/EMBO/src/__OS/croutine.c \
F:/STM32Cube/EMBO/src/__OS/event_groups.c \
F:/STM32Cube/EMBO/src/__OS/list.c \
F:/STM32Cube/EMBO/src/__OS/port.c \
F:/STM32Cube/EMBO/src/__OS/queue.c \
F:/STM32Cube/EMBO/src/__OS/tasks.c \
F:/STM32Cube/EMBO/src/__OS/timers.c 

OBJS += \
./__os/croutine.o \
./__os/event_groups.o \
./__os/list.o \
./__os/port.o \
./__os/queue.o \
./__os/tasks.o \
./__os/timers.o 

C_DEPS += \
./__os/croutine.d \
./__os/event_groups.d \
./__os/list.d \
./__os/port.d \
./__os/queue.d \
./__os/tasks.d \
./__os/timers.d 


# Each subdirectory must supply rules for building sources it contributes
__os/croutine.o: F:/STM32Cube/EMBO/src/__OS/croutine.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__os/croutine.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__os/event_groups.o: F:/STM32Cube/EMBO/src/__OS/event_groups.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__os/event_groups.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__os/list.o: F:/STM32Cube/EMBO/src/__OS/list.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__os/list.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__os/port.o: F:/STM32Cube/EMBO/src/__OS/port.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__os/port.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__os/queue.o: F:/STM32Cube/EMBO/src/__OS/queue.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__os/queue.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__os/tasks.o: F:/STM32Cube/EMBO/src/__OS/tasks.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__os/tasks.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__os/timers.o: F:/STM32Cube/EMBO/src/__OS/timers.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__os/timers.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

