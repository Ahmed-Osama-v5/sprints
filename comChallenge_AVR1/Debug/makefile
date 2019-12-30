################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include mcal/uart/subdir.mk
-include mcal/timer/subdir.mk
-include mcal/spi/subdir.mk
-include mcal/dio/subdir.mk
-include common/subdir.mk
-include ECUAL/pushButton/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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
LSS += \
comChallenge_AVR1.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: comChallenge_AVR1.elf secondary-outputs

# Tool invocations
comChallenge_AVR1.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,comChallenge_AVR1.map -mmcu=atmega32 -o "comChallenge_AVR1.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

comChallenge_AVR1.lss: comChallenge_AVR1.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S comChallenge_AVR1.elf  >"comChallenge_AVR1.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: comChallenge_AVR1.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 comChallenge_AVR1.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) comChallenge_AVR1.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
