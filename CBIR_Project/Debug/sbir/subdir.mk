################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../sbir/orb.cpp 

OBJS += \
./sbir/orb.o 

CPP_DEPS += \
./sbir/orb.d 


# Each subdirectory must supply rules for building sources it contributes
sbir/%.o: ../sbir/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I/usr/local/include/opencv4 -I/usr/local/cuda-11.0/targets/x86_64-linux/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


