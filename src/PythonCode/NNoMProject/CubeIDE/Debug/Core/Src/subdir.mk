################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/CycleCounter.c \
../Core/Src/main.c \
../Core/Src/stm32l4xx_hal_msp.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l4xx.c 

OBJS += \
./Core/Src/CycleCounter.o \
./Core/Src/main.o \
./Core/Src/stm32l4xx_hal_msp.o \
./Core/Src/stm32l4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l4xx.o 

C_DEPS += \
./Core/Src/CycleCounter.d \
./Core/Src/main.d \
./Core/Src/stm32l4xx_hal_msp.d \
./Core/Src/stm32l4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/CycleCounter.o: ../Core/Src/CycleCounter.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/CycleCounter.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/main.o: ../Core/Src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32l4xx_hal_msp.o: ../Core/Src/stm32l4xx_hal_msp.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32l4xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32l4xx_it.o: ../Core/Src/stm32l4xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32l4xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/syscalls.o: ../Core/Src/syscalls.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/sysmem.o: ../Core/Src/sysmem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/system_stm32l4xx.o: ../Core/Src/system_stm32l4xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/system_stm32l4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

