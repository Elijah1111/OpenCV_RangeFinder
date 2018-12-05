################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/RangeFinder.cpp \
../src/cvrange.cpp 

O_SRCS += \
../src/RangeFinder.o \
../src/RangeFinder2.o \
../src/cvrange.o 

OBJS += \
./src/RangeFinder.o \
./src/cvrange.o 

CPP_DEPS += \
./src/RangeFinder.d \
./src/cvrange.d 


# Each subdirectory must supply rules for building sources it contributes
src/RangeFinder.o: ../src/RangeFinder.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/lib64/opencv -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/RangeFinder.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/include/opencv -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


