CC=arm-none-eabi
MCPU=-mcpu=arm1176jzf-s
CFLAGS=-nostdlib -ffreestanding -O2 -Wall -Wextra
LDFLAGS=-nostdlib -lgcc

CPU=cpu
DEV=dev
LIB=lib
INC=inc
CORE=core
TEST=test
OBJ=obj

LINKER=$(DEV)/memory.ld
ELF=$(OBJ)/kernel.elf
OBJDUMP=kernel.txt
TARGET=kernel.img

SRC_CPU		:= $(wildcard $(CPU)/*.S)
SRC_DEV		:= $(wildcard $(DEV)/*.c)
SRC_LIB		:= $(wildcard $(LIB)/*.c)
SRC_INC 	:= $(wildcard $(INC)/*.h)
SRC_CORE	:= $(wildcard $(CORE)/*.c)
SRC_TEST	:= $(wildcard $(TEST)/*.c)

OBJ_CPU		:= $(SRC_CPU:$(CPU)/%.S=$(OBJ)/%.o)
OBJ_DEV		:= $(SRC_DEV:$(DEV)/%.c=$(OBJ)/%.o)
OBJ_CORE	:= $(SRC_CORE:$(CORE)/%.c=$(OBJ)/%.o)
OBJ_LIB		:= $(SRC_LIB:$(LIB)/%.c=$(OBJ)/%.o)
OBJ_TEST	:= $(SRC_TEST:$(TEST)/%.c=$(OBJ)/%.o)



$(TARGET): $(OBJ) $(ELF) $(SRC_INC)
	@echo " Create\t" $(TARGET)
	@$(CC)-objcopy $(ELF) -O binary $(TARGET)
	#@$(CC)-objdump -S $(ELF) > $(OBJDUMP)

$(ELF): $(LINKER) $(OBJ_CPU) $(OBJ_DEV) $(OBJ_CORE) \
		$(OBJ_LIB) $(OBJ_TEST)
	@echo " Linking"
	@$(CC)-gcc -T $(LINKER) $(OBJ_CPU) $(OBJ_DEV) \
			 $(OBJ_CORE) $(OBJ_LIB) $(OBJ_TEST) \
			 -o $@ $(LDFLAGS)


$(OBJ_CPU): $(OBJ)/%.o : $(CPU)/%.S $(SRC_INC)
	@echo " Compile\t" $<
	@$(CC)-gcc $(MCPU) $(CFLAGS) -c $< -o $@

$(OBJ_DEV): $(OBJ)/%.o : $(DEV)/%.c $(SRC_INC)
	@echo " Compile\t" $<
	@$(CC)-gcc $(MCPU) $(CFLAGS) -c -I$(INC) $< -o $@

$(OBJ_LIB): $(OBJ)/%.o : $(LIB)/%.c $(SRC_INC)
	@echo " Compile\t" $<
	@$(CC)-gcc $(MCPU) $(CFLAGS) -c -I$(INC) $< -o $@

$(OBJ_CORE): $(OBJ)/%.o : $(CORE)/%.c $(SRC_INC)
	@echo " Compile\t" $<
	@$(CC)-gcc $(MCPU) $(CFLAGS) -c -I$(INC) $< -o $@

$(OBJ_TEST): $(OBJ)/%.o : $(TEST)/%.c $(SRC_INC)
	@echo " Compile\t" $<
	@$(CC)-gcc $(MCPU) $(CFLAGS) -c -I$(INC) $< -o $@

$(OBJ):
	@mkdir $@

clean:
	@echo "Clean"
	@-rm -rf $(OBJ)
	@-rm -f $(TARGET)
	@-rm -f $(OBJDUMP)
	