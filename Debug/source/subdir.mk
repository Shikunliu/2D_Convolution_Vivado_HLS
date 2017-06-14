################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../core.cpp 

OBJS += \
./source/core.o 

CPP_DEPS += \
./source/core.d 


# Each subdirectory must supply rules for building sources it contributes
source/core.o: C:/Users/baohaochun/2d_convolution_unit/core.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DAESL_TB -D__llvm__ -D__llvm__ -ID:/Xilinx/Vivado_HLS/2016.4/include/ap_sysc -ID:/Xilinx/Vivado_HLS/2016.4/win64/tools/auto_cc/include -ID:/Xilinx/Vivado_HLS/2016.4/win64/tools/systemc/include -ID:/Xilinx/Vivado_HLS/2016.4/include/etc -IC:/Users/baohaochun -ID:/Xilinx/Vivado_HLS/2016.4/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


