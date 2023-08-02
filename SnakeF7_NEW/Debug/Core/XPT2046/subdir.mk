################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/XPT2046/LCD.c \
../Core/XPT2046/Touch.c \
../Core/XPT2046/XPT2046.c 

OBJS += \
./Core/XPT2046/LCD.o \
./Core/XPT2046/Touch.o \
./Core/XPT2046/XPT2046.o 

C_DEPS += \
./Core/XPT2046/LCD.d \
./Core/XPT2046/Touch.d \
./Core/XPT2046/XPT2046.d 


# Each subdirectory must supply rules for building sources it contributes
Core/XPT2046/%.o: ../Core/XPT2046/%.c Core/XPT2046/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-XPT2046

clean-Core-2f-XPT2046:
	-$(RM) ./Core/XPT2046/LCD.d ./Core/XPT2046/LCD.o ./Core/XPT2046/Touch.d ./Core/XPT2046/Touch.o ./Core/XPT2046/XPT2046.d ./Core/XPT2046/XPT2046.o

.PHONY: clean-Core-2f-XPT2046

