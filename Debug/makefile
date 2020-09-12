################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32G4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
EX_UNPLR_SINE_MDLTN_10KHZ_PWM_200911R01.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
EX_UNPLR_SINE_MDLTN_10KHZ_PWM_200911R01.list \

OBJCOPY_BIN += \
EX_UNPLR_SINE_MDLTN_10KHZ_PWM_200911R01.bin \


# All Target
all: EX_UNPLR_SINE_MDLTN_10KHZ_PWM_200911R01.elf secondary-outputs

# Tool invocations
EX_UNPLR_SINE_MDLTN_10KHZ_PWM_200911R01.elf: $(OBJS) $(USER_OBJS) C:\Users\napst\OneDrive\Documentos\STM32\EX_UNPLR_SINE_MDLTN_10KHZ_PWM_200911R01\STM32G474RETX_FLASH.ld
	arm-none-eabi-gcc -o "EX_UNPLR_SINE_MDLTN_10KHZ_PWM_200911R01.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\napst\OneDrive\Documentos\STM32\EX_UNPLR_SINE_MDLTN_10KHZ_PWM_200911R01\STM32G474RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="EX_UNPLR_SINE_MDLTN_10KHZ_PWM_200911R01.map" -Wl,--gc-sections -static -L"C:\Users\napst\OneDrive\Documentos\STM32\EX_UNPLR_SINE_MDLTN_10KHZ_PWM_200911R01\libs" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

EX_UNPLR_SINE_MDLTN_10KHZ_PWM_200911R01.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "EX_UNPLR_SINE_MDLTN_10KHZ_PWM_200911R01.list"
	@echo 'Finished building: $@'
	@echo ' '

EX_UNPLR_SINE_MDLTN_10KHZ_PWM_200911R01.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "EX_UNPLR_SINE_MDLTN_10KHZ_PWM_200911R01.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
