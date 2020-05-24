################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/nnom/nnom.c \
../Core/Src/nnom/nnom_activation.c \
../Core/Src/nnom/nnom_avgpool.c \
../Core/Src/nnom/nnom_baselayer.c \
../Core/Src/nnom/nnom_concat.c \
../Core/Src/nnom/nnom_conv2d.c \
../Core/Src/nnom/nnom_cropping.c \
../Core/Src/nnom/nnom_dense.c \
../Core/Src/nnom/nnom_dw_conv2d.c \
../Core/Src/nnom/nnom_flatten.c \
../Core/Src/nnom/nnom_global_pool.c \
../Core/Src/nnom/nnom_input.c \
../Core/Src/nnom/nnom_lambda.c \
../Core/Src/nnom/nnom_layers.c \
../Core/Src/nnom/nnom_local.c \
../Core/Src/nnom/nnom_matrix.c \
../Core/Src/nnom/nnom_maxpool.c \
../Core/Src/nnom/nnom_output.c \
../Core/Src/nnom/nnom_rnn.c \
../Core/Src/nnom/nnom_softmax.c \
../Core/Src/nnom/nnom_sumpool.c \
../Core/Src/nnom/nnom_tensor.c \
../Core/Src/nnom/nnom_upsample.c \
../Core/Src/nnom/nnom_utils.c \
../Core/Src/nnom/nnom_zero_padding.c 

OBJS += \
./Core/Src/nnom/nnom.o \
./Core/Src/nnom/nnom_activation.o \
./Core/Src/nnom/nnom_avgpool.o \
./Core/Src/nnom/nnom_baselayer.o \
./Core/Src/nnom/nnom_concat.o \
./Core/Src/nnom/nnom_conv2d.o \
./Core/Src/nnom/nnom_cropping.o \
./Core/Src/nnom/nnom_dense.o \
./Core/Src/nnom/nnom_dw_conv2d.o \
./Core/Src/nnom/nnom_flatten.o \
./Core/Src/nnom/nnom_global_pool.o \
./Core/Src/nnom/nnom_input.o \
./Core/Src/nnom/nnom_lambda.o \
./Core/Src/nnom/nnom_layers.o \
./Core/Src/nnom/nnom_local.o \
./Core/Src/nnom/nnom_matrix.o \
./Core/Src/nnom/nnom_maxpool.o \
./Core/Src/nnom/nnom_output.o \
./Core/Src/nnom/nnom_rnn.o \
./Core/Src/nnom/nnom_softmax.o \
./Core/Src/nnom/nnom_sumpool.o \
./Core/Src/nnom/nnom_tensor.o \
./Core/Src/nnom/nnom_upsample.o \
./Core/Src/nnom/nnom_utils.o \
./Core/Src/nnom/nnom_zero_padding.o 

C_DEPS += \
./Core/Src/nnom/nnom.d \
./Core/Src/nnom/nnom_activation.d \
./Core/Src/nnom/nnom_avgpool.d \
./Core/Src/nnom/nnom_baselayer.d \
./Core/Src/nnom/nnom_concat.d \
./Core/Src/nnom/nnom_conv2d.d \
./Core/Src/nnom/nnom_cropping.d \
./Core/Src/nnom/nnom_dense.d \
./Core/Src/nnom/nnom_dw_conv2d.d \
./Core/Src/nnom/nnom_flatten.d \
./Core/Src/nnom/nnom_global_pool.d \
./Core/Src/nnom/nnom_input.d \
./Core/Src/nnom/nnom_lambda.d \
./Core/Src/nnom/nnom_layers.d \
./Core/Src/nnom/nnom_local.d \
./Core/Src/nnom/nnom_matrix.d \
./Core/Src/nnom/nnom_maxpool.d \
./Core/Src/nnom/nnom_output.d \
./Core/Src/nnom/nnom_rnn.d \
./Core/Src/nnom/nnom_softmax.d \
./Core/Src/nnom/nnom_sumpool.d \
./Core/Src/nnom/nnom_tensor.d \
./Core/Src/nnom/nnom_upsample.d \
./Core/Src/nnom/nnom_utils.d \
./Core/Src/nnom/nnom_zero_padding.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/nnom/nnom.o: ../Core/Src/nnom/nnom.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nnom/nnom.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/nnom/nnom_activation.o: ../Core/Src/nnom/nnom_activation.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nnom/nnom_activation.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/nnom/nnom_avgpool.o: ../Core/Src/nnom/nnom_avgpool.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nnom/nnom_avgpool.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/nnom/nnom_baselayer.o: ../Core/Src/nnom/nnom_baselayer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nnom/nnom_baselayer.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/nnom/nnom_concat.o: ../Core/Src/nnom/nnom_concat.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nnom/nnom_concat.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/nnom/nnom_conv2d.o: ../Core/Src/nnom/nnom_conv2d.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nnom/nnom_conv2d.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/nnom/nnom_cropping.o: ../Core/Src/nnom/nnom_cropping.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nnom/nnom_cropping.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/nnom/nnom_dense.o: ../Core/Src/nnom/nnom_dense.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nnom/nnom_dense.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/nnom/nnom_dw_conv2d.o: ../Core/Src/nnom/nnom_dw_conv2d.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nnom/nnom_dw_conv2d.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/nnom/nnom_flatten.o: ../Core/Src/nnom/nnom_flatten.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nnom/nnom_flatten.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/nnom/nnom_global_pool.o: ../Core/Src/nnom/nnom_global_pool.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nnom/nnom_global_pool.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/nnom/nnom_input.o: ../Core/Src/nnom/nnom_input.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nnom/nnom_input.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/nnom/nnom_lambda.o: ../Core/Src/nnom/nnom_lambda.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nnom/nnom_lambda.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/nnom/nnom_layers.o: ../Core/Src/nnom/nnom_layers.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nnom/nnom_layers.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/nnom/nnom_local.o: ../Core/Src/nnom/nnom_local.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nnom/nnom_local.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/nnom/nnom_matrix.o: ../Core/Src/nnom/nnom_matrix.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nnom/nnom_matrix.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/nnom/nnom_maxpool.o: ../Core/Src/nnom/nnom_maxpool.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nnom/nnom_maxpool.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/nnom/nnom_output.o: ../Core/Src/nnom/nnom_output.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nnom/nnom_output.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/nnom/nnom_rnn.o: ../Core/Src/nnom/nnom_rnn.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nnom/nnom_rnn.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/nnom/nnom_softmax.o: ../Core/Src/nnom/nnom_softmax.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nnom/nnom_softmax.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/nnom/nnom_sumpool.o: ../Core/Src/nnom/nnom_sumpool.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nnom/nnom_sumpool.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/nnom/nnom_tensor.o: ../Core/Src/nnom/nnom_tensor.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nnom/nnom_tensor.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/nnom/nnom_upsample.o: ../Core/Src/nnom/nnom_upsample.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nnom/nnom_upsample.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/nnom/nnom_utils.o: ../Core/Src/nnom/nnom_utils.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nnom/nnom_utils.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/nnom/nnom_zero_padding.o: ../Core/Src/nnom/nnom_zero_padding.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DARM_MATH_DSP -DDEBUG '-D__FPU_PRESENT=1' -DSTM32L475xx -c -I../nnom-master/inc -I../Drivers/CMSIS/Include -I../nnom-master/port -I../Core/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I.././CMSISINC -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nnom/nnom_zero_padding.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

