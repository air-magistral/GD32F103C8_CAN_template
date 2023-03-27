################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../System/Src/newlib/assert.c \
../System/Src/newlib/exit.c \
../System/Src/newlib/sbrk.c \
../System/Src/newlib/startup.c \
../System/Src/newlib/syscalls.c 

CPP_SRCS += \
../System/Src/newlib/cxx.cpp 

OBJS += \
./System/Src/newlib/assert.o \
./System/Src/newlib/cxx.o \
./System/Src/newlib/exit.o \
./System/Src/newlib/sbrk.o \
./System/Src/newlib/startup.o \
./System/Src/newlib/syscalls.o 

C_DEPS += \
./System/Src/newlib/assert.d \
./System/Src/newlib/exit.d \
./System/Src/newlib/sbrk.d \
./System/Src/newlib/startup.d \
./System/Src/newlib/syscalls.d 

CPP_DEPS += \
./System/Src/newlib/cxx.d 


# Each subdirectory must supply rules for building sources it contributes
System/Src/newlib/%.o: ../System/Src/newlib/%.c System/Src/newlib/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra -g3 -DDEBUG -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"../Inc" -I"../System/Inc" -I"../System/Inc/CMSIS" -I"../System/Inc/gd32f10x" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

System/Src/newlib/%.o: ../System/Src/newlib/%.cpp System/Src/newlib/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra -g3 -DDEBUG -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"../Inc" -I"../System/Inc" -I"../System/Inc/CMSIS" -I"../System/Inc/gd32f10x" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


