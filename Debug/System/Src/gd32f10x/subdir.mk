################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../System/Src/gd32f10x/gd32f10x_adc.c \
../System/Src/gd32f10x/gd32f10x_bkp.c \
../System/Src/gd32f10x/gd32f10x_can.c \
../System/Src/gd32f10x/gd32f10x_crc.c \
../System/Src/gd32f10x/gd32f10x_dac.c \
../System/Src/gd32f10x/gd32f10x_dbg.c \
../System/Src/gd32f10x/gd32f10x_dma.c \
../System/Src/gd32f10x/gd32f10x_enet.c \
../System/Src/gd32f10x/gd32f10x_exmc.c \
../System/Src/gd32f10x/gd32f10x_exti.c \
../System/Src/gd32f10x/gd32f10x_fmc.c \
../System/Src/gd32f10x/gd32f10x_fwdgt.c \
../System/Src/gd32f10x/gd32f10x_gpio.c \
../System/Src/gd32f10x/gd32f10x_i2c.c \
../System/Src/gd32f10x/gd32f10x_it.c \
../System/Src/gd32f10x/gd32f10x_misc.c \
../System/Src/gd32f10x/gd32f10x_pmu.c \
../System/Src/gd32f10x/gd32f10x_rcu.c \
../System/Src/gd32f10x/gd32f10x_rtc.c \
../System/Src/gd32f10x/gd32f10x_sdio.c \
../System/Src/gd32f10x/gd32f10x_spi.c \
../System/Src/gd32f10x/gd32f10x_timer.c \
../System/Src/gd32f10x/gd32f10x_usart.c \
../System/Src/gd32f10x/gd32f10x_wwdgt.c 

OBJS += \
./System/Src/gd32f10x/gd32f10x_adc.o \
./System/Src/gd32f10x/gd32f10x_bkp.o \
./System/Src/gd32f10x/gd32f10x_can.o \
./System/Src/gd32f10x/gd32f10x_crc.o \
./System/Src/gd32f10x/gd32f10x_dac.o \
./System/Src/gd32f10x/gd32f10x_dbg.o \
./System/Src/gd32f10x/gd32f10x_dma.o \
./System/Src/gd32f10x/gd32f10x_enet.o \
./System/Src/gd32f10x/gd32f10x_exmc.o \
./System/Src/gd32f10x/gd32f10x_exti.o \
./System/Src/gd32f10x/gd32f10x_fmc.o \
./System/Src/gd32f10x/gd32f10x_fwdgt.o \
./System/Src/gd32f10x/gd32f10x_gpio.o \
./System/Src/gd32f10x/gd32f10x_i2c.o \
./System/Src/gd32f10x/gd32f10x_it.o \
./System/Src/gd32f10x/gd32f10x_misc.o \
./System/Src/gd32f10x/gd32f10x_pmu.o \
./System/Src/gd32f10x/gd32f10x_rcu.o \
./System/Src/gd32f10x/gd32f10x_rtc.o \
./System/Src/gd32f10x/gd32f10x_sdio.o \
./System/Src/gd32f10x/gd32f10x_spi.o \
./System/Src/gd32f10x/gd32f10x_timer.o \
./System/Src/gd32f10x/gd32f10x_usart.o \
./System/Src/gd32f10x/gd32f10x_wwdgt.o 

C_DEPS += \
./System/Src/gd32f10x/gd32f10x_adc.d \
./System/Src/gd32f10x/gd32f10x_bkp.d \
./System/Src/gd32f10x/gd32f10x_can.d \
./System/Src/gd32f10x/gd32f10x_crc.d \
./System/Src/gd32f10x/gd32f10x_dac.d \
./System/Src/gd32f10x/gd32f10x_dbg.d \
./System/Src/gd32f10x/gd32f10x_dma.d \
./System/Src/gd32f10x/gd32f10x_enet.d \
./System/Src/gd32f10x/gd32f10x_exmc.d \
./System/Src/gd32f10x/gd32f10x_exti.d \
./System/Src/gd32f10x/gd32f10x_fmc.d \
./System/Src/gd32f10x/gd32f10x_fwdgt.d \
./System/Src/gd32f10x/gd32f10x_gpio.d \
./System/Src/gd32f10x/gd32f10x_i2c.d \
./System/Src/gd32f10x/gd32f10x_it.d \
./System/Src/gd32f10x/gd32f10x_misc.d \
./System/Src/gd32f10x/gd32f10x_pmu.d \
./System/Src/gd32f10x/gd32f10x_rcu.d \
./System/Src/gd32f10x/gd32f10x_rtc.d \
./System/Src/gd32f10x/gd32f10x_sdio.d \
./System/Src/gd32f10x/gd32f10x_spi.d \
./System/Src/gd32f10x/gd32f10x_timer.d \
./System/Src/gd32f10x/gd32f10x_usart.d \
./System/Src/gd32f10x/gd32f10x_wwdgt.d 


# Each subdirectory must supply rules for building sources it contributes
System/Src/gd32f10x/%.o: ../System/Src/gd32f10x/%.c System/Src/gd32f10x/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra -g3 -DDEBUG -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"../Inc" -I"../System/Inc" -I"../System/Inc/CMSIS" -I"../System/Inc/gd32f10x" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


