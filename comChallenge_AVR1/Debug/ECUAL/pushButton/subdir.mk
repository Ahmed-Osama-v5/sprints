################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ECUAL/pushButton/pushButton.c 

OBJS += \
./ECUAL/pushButton/pushButton.o 

C_DEPS += \
./ECUAL/pushButton/pushButton.d 


# Each subdirectory must supply rules for building sources it contributes
ECUAL/pushButton/%.o: ../ECUAL/pushButton/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\My own work\github\Projects\comChallenge_AVR1\appal" -I"D:\My own work\github\Projects\comChallenge_AVR1\common" -I"D:\My own work\github\Projects\comChallenge_AVR1\mcal\dio" -I"D:\My own work\github\Projects\comChallenge_AVR1\mcal\spi" -I"D:\My own work\github\Projects\comChallenge_AVR1\mcal\uart" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


