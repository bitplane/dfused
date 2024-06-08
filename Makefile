CC = gcc
CFLAGS = -Wall -I./src/include
LDFLAGS =

SRCS = $(wildcard src/dfused/*.c src/libdfused/*.c)
OBJS = $(SRCS:.c=.o)

TARGET = dfused

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

test:
	# Add test execution commands here
	echo "Running tests..."