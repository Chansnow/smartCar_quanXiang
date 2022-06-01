################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include USER/subdir.mk
-include Libraries/wch_libraries/Startup/subdir.mk
-include Libraries/wch_libraries/Peripheral/subdir.mk
-include Libraries/wch_libraries/Core/subdir.mk
-include Libraries/seekfree_peripheral/subdir.mk
-include Libraries/seekfree_libraries/subdir.mk
-include Libraries/board/subdir.mk
-include CODE/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
FIrelock\ _M_turn.hex \

SECONDARY_LIST += \
FIrelock\ _M_turn.lst \

SECONDARY_SIZE += \
FIrelock\ _M_turn.siz \


# All Target
all: FIrelock\ _M_turn.elf secondary-outputs

# Tool invocations
FIrelock\ _M_turn.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -T .ld -nostartfiles -Xlinker --gc-sections -L"../" -Wl,-Map,"FIrelock _M_turn.map" --specs=nano.specs --specs=nosys.specs -o "FIrelock _M_turn.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
FIrelock\ _M_turn.hex: FIrelock\ _M_turn.elf
	@	riscv-none-embed-objcopy -O ihex "FIrelock _M_turn.elf"  "FIrelock _M_turn.hex"
	@	@
FIrelock\ _M_turn.lst: FIrelock\ _M_turn.elf
	@	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "FIrelock _M_turn.elf" > "FIrelock _M_turn.lst"
	@	@
FIrelock\ _M_turn.siz: FIrelock\ _M_turn.elf
	@	riscv-none-embed-size --format=berkeley "FIrelock _M_turn.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) "FIrelock _M_turn.elf"
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
