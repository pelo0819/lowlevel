TARGET = analyst
GCC = g++
OPT_C = -c
OPT_O = -o

# assembly files
SRCS=$(wildcard *.cpp)

# object files
OBJS=$(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) $(OPT_O) $@

%.o: %.cpp
	$(GCC) $(OPT_C) $<

clean:
	rm -f $(OBJS)

test_asm:
	./analyst ../targets/asm/pelo

test_c:
	./analyst ../targets/c/pelo

test_co:
	./analyst ../targets/c/sample.o

.PHONY: all clean