
# CC = gcc
# ifeq ($(shell uname),linux)
# SOURCE_FLAGS = -D_POSIX_SOURCE -D_BSD_SOURCE
# endif

#CFLAGS = -Os -Wall -Wextra -Werror \
#	 $(SOURCE_FLAGS) -g \
#	 -std=gnu99
# -D NDEBUG

CFLAGS += -Iinclude -Isrc -Wall
LDFLAGS = -lpthread

%.o: %.c $(DEPS)
	$(CC) -static -fpic -c -o $@ $< $(CFLAGS)

OBJ = parser.o src/header_field.o src/header_field_list.o src/request_header.o

libh3: $(OBJ)
	gcc -shared -o libh3.a $^ $(CFLAGS)

all: libh3
	# gcc -o test test.c libh3.a $(CFLAGS)

clean:
	rm -rf $(OBJ)
