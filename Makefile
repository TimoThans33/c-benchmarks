########################################################################
# ECE5504 ....
########################################################################

CC := riscv64-unknown-elf-gcc
OBJDUMP := riscv64-unknown-elf-objdump

CFLAGS := -O2 -std=gnu11 -Wall -specs=htif_nano.specs 
ADD_FLAGS := -march=rv64imafd

.PHONY: context_switch compressed
context_switch: context_switch.dump
uncompressed: context_switch.dump

.PRECIOUS: %.riscv
%.riscv: %.c trap.c
	$(CC) $(CFLAGS) -o $@ $< trap.c

%_uncompressed.riscv: context_switch.c trap.c
	$(CC) $(CFLAGS) $(ADD_FLAGS) -o context_switch_uncompressed.riscv $< trap.c

%.dump: %.riscv
	$(OBJDUMP) -d -M no-aliases $< > $@

%_uncompressed.dump: %_uncompressed.riscv
	$(OBJDUMP) -d -M no-aliases context_switch_uncompressed.riscv > context_switch_uncompressed.dump

.PHONY: clean
clean:
	rm -f -- *.riscv *.o *.dump

.SUFFIXES: # Disable built-in suffix rules
