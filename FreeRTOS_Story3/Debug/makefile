################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include SERVICE/RTOS/subdir.mk
-include MCAL/Sleep/subdir.mk
-include MCAL/DIO/subdir.mk
-include ECUAL/pushButton/subdir.mk
-include APP/subdir.mk
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
FreeRTOS_Story3.lss \

FLASH_IMAGE += \
FreeRTOS_Story3.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: FreeRTOS_Story3.elf secondary-outputs

# Tool invocations
FreeRTOS_Story3.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,FreeRTOS_Story3.map -mmcu=atmega32 -o "FreeRTOS_Story3.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

FreeRTOS_Story3.lss: FreeRTOS_Story3.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S FreeRTOS_Story3.elf  >"FreeRTOS_Story3.lss"
	@echo 'Finished building: $@'
	@echo ' '

FreeRTOS_Story3.hex: FreeRTOS_Story3.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex FreeRTOS_Story3.elf  "FreeRTOS_Story3.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: FreeRTOS_Story3.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 FreeRTOS_Story3.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) FreeRTOS_Story3.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
