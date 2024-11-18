CC = clang
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS =

SRCS = server.c client.c common.c
OBJS = $(SRCS:%.c=build/%.o)
DEPS = common.h

all: build_dir server client

build_dir:
	mkdir -p build

server: build/server.o build/common.o
	$(CC) $(LDFLAGS) -o build/server build/server.o build/common.o

client: build/client.o build/common.o
	$(CC) $(LDFLAGS) -o build/client build/client.o build/common.o

build/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build

.PHONY: all clean build_dir
