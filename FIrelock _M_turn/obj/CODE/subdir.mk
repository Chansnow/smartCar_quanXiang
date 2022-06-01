################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/Control.c \
../CODE/Flash.c \
../CODE/Get_deta.c \
../CODE/Init.c \
../CODE/Key.c \
../CODE/Motor.c \
../CODE/PIDcontrol.c \
../CODE/encode.c \
../CODE/menu.c \
../CODE/send_data.c \
../CODE/topicm.c 

OBJS += \
./CODE/Control.o \
./CODE/Flash.o \
./CODE/Get_deta.o \
./CODE/Init.o \
./CODE/Key.o \
./CODE/Motor.o \
./CODE/PIDcontrol.o \
./CODE/encode.o \
./CODE/menu.o \
./CODE/send_data.o \
./CODE/topicm.o 

C_DEPS += \
./CODE/Control.d \
./CODE/Flash.d \
./CODE/Get_deta.d \
./CODE/Init.d \
./CODE/Key.d \
./CODE/Motor.d \
./CODE/PIDcontrol.d \
./CODE/encode.d \
./CODE/menu.d \
./CODE/send_data.d \
./CODE/topicm.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/%.o: ../CODE/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"../Libraries/wch_libraries/Core" -I"../Libraries/wch_libraries/Peripheral" -I"../Libraries/wch_libraries/Startup" -I"../Libraries/seekfree_libraries" -I"../Libraries/seekfree_peripheral" -I"../Libraries/board" -I"../CODE" -I"../USER" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

