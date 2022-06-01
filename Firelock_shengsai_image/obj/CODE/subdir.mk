################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/Gete_image.c \
../CODE/Image_cross.c \
../CODE/Image_process.c \
../CODE/Image_ring.c \
../CODE/Init.c \
../CODE/Key.c \
../CODE/Main_control.c \
../CODE/Send_date.c \
../CODE/flash.c \
../CODE/menu.c \
../CODE/sancha.c 

OBJS += \
./CODE/Gete_image.o \
./CODE/Image_cross.o \
./CODE/Image_process.o \
./CODE/Image_ring.o \
./CODE/Init.o \
./CODE/Key.o \
./CODE/Main_control.o \
./CODE/Send_date.o \
./CODE/flash.o \
./CODE/menu.o \
./CODE/sancha.o 

C_DEPS += \
./CODE/Gete_image.d \
./CODE/Image_cross.d \
./CODE/Image_process.d \
./CODE/Image_ring.d \
./CODE/Init.d \
./CODE/Key.d \
./CODE/Main_control.d \
./CODE/Send_date.d \
./CODE/flash.d \
./CODE/menu.d \
./CODE/sancha.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/%.o: ../CODE/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"../Libraries/wch_libraries/Core" -I"../Libraries/wch_libraries/Peripheral" -I"../Libraries/wch_libraries/Startup" -I"../Libraries/seekfree_libraries" -I"../Libraries/seekfree_peripheral" -I"../Libraries/board" -I"../CODE" -I"../USER" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

