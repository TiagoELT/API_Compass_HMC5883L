################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f103rbtx.s 

OBJS += \
./Core/Startup/startup_stm32f103rbtx.o 

S_DEPS += \
./Core/Startup/startup_stm32f103rbtx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/startup_stm32f103rbtx.o: ../Core/Startup/startup_stm32f103rbtx.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m3 -c -x assembler-with-cpp -MMD -MP -MF"Core/Startup/startup_stm32f103rbtx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

