################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../System/Src/diag/trace-impl.c \
../System/Src/diag/trace.c 

OBJS += \
./System/Src/diag/trace-impl.o \
./System/Src/diag/trace.o 

C_DEPS += \
./System/Src/diag/trace-impl.d \
./System/Src/diag/trace.d 


# Each subdirectory must supply rules for building sources it contributes
System/Src/diag/%.o: ../System/Src/diag/%.c System/Src/diag/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra -g3 -DDEBUG -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"../Inc" -I"../System/Inc" -I"../System/Inc/CMSIS" -I"../System/Inc/gd32f10x" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


