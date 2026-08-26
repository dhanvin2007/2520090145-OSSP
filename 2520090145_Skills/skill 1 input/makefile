CC      := gcc
CFLAGS  := -Wall -Wextra -g
SRC_DIR := src
BIN_DIR := bin

TARGETS := fork_demo exec_demo process_tree zombie_demo orphan_demo
BINARIES := $(addprefix $(BIN_DIR)/,$(TARGETS))

.PHONY: all clean run-fork run-exec run-tree run-zombie run-orphan

all: $(BINARIES)

$(BIN_DIR)/%: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $<

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

run-fork: $(BIN_DIR)/fork_demo
	./$(BIN_DIR)/fork_demo

run-exec: $(BIN_DIR)/exec_demo
	./$(BIN_DIR)/exec_demo

run-tree: $(BIN_DIR)/process_tree
	./$(BIN_DIR)/process_tree

run-zombie: $(BIN_DIR)/zombie_demo
	./$(BIN_DIR)/zombie_demo

run-orphan: $(BIN_DIR)/orphan_demo
	./$(BIN_DIR)/orphan_demo

clean:
	rm -rf $(BIN_DIR)
