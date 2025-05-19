################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_program.c \
../BUZ_program.c \
../EXIT_program.c \
../GIE_program.c \
../GPIO_program.c \
../LCD_program.c \
../LED_program.c \
../SERVO_program.c \
../TIMER_program.c \
../main.c 

OBJS += \
./ADC_program.o \
./BUZ_program.o \
./EXIT_program.o \
./GIE_program.o \
./GPIO_program.o \
./LCD_program.o \
./LED_program.o \
./SERVO_program.o \
./TIMER_program.o \
./main.o 

C_DEPS += \
./ADC_program.d \
./BUZ_program.d \
./EXIT_program.d \
./GIE_program.d \
./GPIO_program.d \
./LCD_program.d \
./LED_program.d \
./SERVO_program.d \
./TIMER_program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O2 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


