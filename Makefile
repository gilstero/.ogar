CC      := clang
CFLAGS  := -Wall -Wextra -Werror -O2 -g
LDFLAGS := -lz

TARGET  := ogar
SRCS    := ogar.c ogar_utils.c
OBJS    := $(SRCS:.c=.o)
DEPS    := ogar.h

.PHONY: all clean run test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile .c -> .o, rebuild if header changes
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)