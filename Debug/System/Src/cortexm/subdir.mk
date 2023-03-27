################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../System/Src/cortexm/exception-handlers.c \
../System/Src/cortexm/initialize-hardware.c \
../System/Src/cortexm/reset-hardware.c 

OBJS += \
./System/Src/cortexm/exception-handlers.o \
./System/Src/cortexm/initialize-hardware.o \
./System/Src/cortexm/reset-hardware.o 

C_DEPS += \
./System/Src/cortexm/exception-handlers.d \
./System/Src/cortexm/initialize-hardware.d \
./System/Src/cortexm/reset-hardware.d 


# Each subdirectory must supply rules for building sources it contributes
System/Src/cortexm/%.o: ../System/Src/cortexm/%.c System/Src/cortexm/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra -g3 -DDEBUG -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"../Inc" -I"../System/Inc" -I"../System/Inc/CMSIS" -I"../System/Inc/gd32f10x" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


