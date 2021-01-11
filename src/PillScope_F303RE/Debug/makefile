################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include __OS/subdir.mk
-include __App/Src/scpi/subdir.mk
-include __App/Src/subdir.mk
-include Drivers/STM32F3xx_HAL_Driver/Src/subdir.mk
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
PillScope_F303RE.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
PillScope_F303RE.list \

OBJCOPY_HEX += \
PillScope_F303RE.hex \

OBJCOPY_BIN += \
PillScope_F303RE.bin \


# All Target
all: PillScope_F303RE.elf secondary-outputs

# Tool invocations
PillScope_F303RE.elf: $(OBJS) $(USER_OBJS) F:\STM32Cube\PillScope\src\PillScope_F303RE\STM32F303RETX_FLASH.ld
	arm-none-eabi-gcc -o "PillScope_F303RE.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"F:\STM32Cube\PillScope\src\PillScope_F303RE\STM32F303RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="PillScope_F303RE.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

PillScope_F303RE.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "PillScope_F303RE.list"
	@echo 'Finished building: $@'
	@echo ' '

PillScope_F303RE.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "PillScope_F303RE.hex"
	@echo 'Finished building: $@'
	@echo ' '

PillScope_F303RE.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "PillScope_F303RE.bin"
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
