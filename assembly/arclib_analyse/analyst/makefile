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

test:
	./analyst ../targets/archive/gnuar.a

test2:
	./analyst ../targets/archive/archive.a -e


.PHONY: all clean