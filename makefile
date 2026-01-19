CC = clang
CFLAGS = -Wall -Wextra -std=c99 -pedantic

DIR_BIN = bin
DIR_SRC = src

SRCS = $(wildcard $(DIR_SRC)/*.c)
EXEC = $(patsubst $(DIR_SRC)/%.c,$(DIR_BIN)/%,$(SRCS))

.PHONY: all clean

all: $(EXEC)

$(DIR_BIN)/%: $(DIR_SRC)/%.c
	@mkdir -p $(DIR_BIN)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(DIR_BIN)