################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include __OS/include/subdir.mk
-include __OS/subdir.mk
-include __App/Src/scpi/subdir.mk
-include __App/Src/subdir.mk
-include USB_DEVICE/Target/subdir.mk
-include USB_DEVICE/App/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Core/Src/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
EMBO_F103C8.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
EMBO_F103C8.list \

OBJCOPY_HEX += \
EMBO_F103C8.hex \

OBJCOPY_BIN += \
EMBO_F103C8.bin \


# All Target
all: EMBO_F103C8.elf secondary-outputs

# Tool invocations
EMBO_F103C8.elf: $(OBJS) $(USER_OBJS) F:\STM32Cube\EMBO\src\EMBO_F103C8\STM32F103C8TX_FLASH.ld
	arm-none-eabi-gcc -o "EMBO_F103C8.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"F:\STM32Cube\EMBO\src\EMBO_F103C8\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="EMBO_F103C8.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

EMBO_F103C8.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "EMBO_F103C8.list"
	@echo 'Finished building: $@'
	@echo ' '

EMBO_F103C8.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "EMBO_F103C8.hex"
	@echo 'Finished building: $@'
	@echo ' '

EMBO_F103C8.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "EMBO_F103C8.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
