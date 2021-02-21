################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/STM32Cube/EMBO/src/__App/src/app.c \
F:/STM32Cube/EMBO/src/__App/src/cfg.c \
F:/STM32Cube/EMBO/src/__App/src/cntr.c \
F:/STM32Cube/EMBO/src/__App/src/cntr_irq.c \
F:/STM32Cube/EMBO/src/__App/src/comm.c \
F:/STM32Cube/EMBO/src/__App/src/comm_irq.c \
F:/STM32Cube/EMBO/src/__App/src/daq.c \
F:/STM32Cube/EMBO/src/__App/src/daq_irq.c \
F:/STM32Cube/EMBO/src/__App/src/daq_trig.c \
F:/STM32Cube/EMBO/src/__App/src/irq.c \
F:/STM32Cube/EMBO/src/__App/src/led.c \
F:/STM32Cube/EMBO/src/__App/src/periph.c \
F:/STM32Cube/EMBO/src/__App/src/proto.c \
F:/STM32Cube/EMBO/src/__App/src/pwm.c \
F:/STM32Cube/EMBO/src/__App/src/sgen.c \
F:/STM32Cube/EMBO/src/__App/src/utility.c 

OBJS += \
./__app/src/app.o \
./__app/src/cfg.o \
./__app/src/cntr.o \
./__app/src/cntr_irq.o \
./__app/src/comm.o \
./__app/src/comm_irq.o \
./__app/src/daq.o \
./__app/src/daq_irq.o \
./__app/src/daq_trig.o \
./__app/src/irq.o \
./__app/src/led.o \
./__app/src/periph.o \
./__app/src/proto.o \
./__app/src/pwm.o \
./__app/src/sgen.o \
./__app/src/utility.o 

C_DEPS += \
./__app/src/app.d \
./__app/src/cfg.d \
./__app/src/cntr.d \
./__app/src/cntr_irq.d \
./__app/src/comm.d \
./__app/src/comm_irq.d \
./__app/src/daq.d \
./__app/src/daq_irq.d \
./__app/src/daq_trig.d \
./__app/src/irq.d \
./__app/src/led.d \
./__app/src/periph.d \
./__app/src/proto.d \
./__app/src/pwm.d \
./__app/src/sgen.d \
./__app/src/utility.d 


# Each subdirectory must supply rules for building sources it contributes
__app/src/app.o: F:/STM32Cube/EMBO/src/__App/src/app.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__app/src/app.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__app/src/cfg.o: F:/STM32Cube/EMBO/src/__App/src/cfg.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__app/src/cfg.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__app/src/cntr.o: F:/STM32Cube/EMBO/src/__App/src/cntr.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__app/src/cntr.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__app/src/cntr_irq.o: F:/STM32Cube/EMBO/src/__App/src/cntr_irq.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__app/src/cntr_irq.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__app/src/comm.o: F:/STM32Cube/EMBO/src/__App/src/comm.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__app/src/comm.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__app/src/comm_irq.o: F:/STM32Cube/EMBO/src/__App/src/comm_irq.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__app/src/comm_irq.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__app/src/daq.o: F:/STM32Cube/EMBO/src/__App/src/daq.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__app/src/daq.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__app/src/daq_irq.o: F:/STM32Cube/EMBO/src/__App/src/daq_irq.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__app/src/daq_irq.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__app/src/daq_trig.o: F:/STM32Cube/EMBO/src/__App/src/daq_trig.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__app/src/daq_trig.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__app/src/irq.o: F:/STM32Cube/EMBO/src/__App/src/irq.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__app/src/irq.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__app/src/led.o: F:/STM32Cube/EMBO/src/__App/src/led.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__app/src/led.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__app/src/periph.o: F:/STM32Cube/EMBO/src/__App/src/periph.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__app/src/periph.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__app/src/proto.o: F:/STM32Cube/EMBO/src/__App/src/proto.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__app/src/proto.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__app/src/pwm.o: F:/STM32Cube/EMBO/src/__App/src/pwm.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__app/src/pwm.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__app/src/sgen.o: F:/STM32Cube/EMBO/src/__App/src/sgen.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__app/src/sgen.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
__app/src/utility.o: F:/STM32Cube/EMBO/src/__App/src/utility.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DDEBUG -c -I"F:/STM32Cube/EMBO/src/__App/inc" -I"F:/STM32Cube/EMBO/src/__OS/include" -I"F:/STM32Cube/EMBO/src/__Lib/scpi/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"__app/src/utility.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

