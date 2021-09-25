TARGET = analyst
GCC = gcc
OPT_C = -c
OPT_O = -o

# assembly files
SRCS=$(wildcard *.c)

# object files
OBJS=$(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) $(OPT_O) $@

%.o: %.c
	$(GCC) $(OPT_C) $<

clean:
	rm -f $(OBJS)

test_asm:
	./analyst ../targets/asm/pelo

test_c:
	./analyst ../targets/c/pelo

.PHONY: all clean