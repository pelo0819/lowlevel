# name output elf file
ELF = pelo

# nasm command
NASM = nasm

# option
OPT_NASM = -f elf64

# link command
LINK = ld

# assembly files
SRCS=$(wildcard *.asm)

# object files
OBJS=$(SRCS:.asm=.o)

all: $(ELF)

$(ELF): $(OBJS)
	$(LINK) $(OBJS) -o $@

%.o: %.asm
	$(NASM) $(OPT_NASM) -o $@ $<

clean:
	rm -f $(OBJS)

.PHONY: all clean