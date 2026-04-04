# Compiler settings
CC = gcc
CFLAGS = -g -pedantic -Wall -Wextra  #-I./include

# Directories
SRC_DIR = .
TEST_DIR = tests

# Executable names
APP_BIN = run
TEST_VECTOR_BIN = test_v
TEST_GENQUEUE_BIN = test_q
TEST_STACK_BIN = test_s

# Default target: builds both the app and the test runner
all: $(APP_BIN) $(TEST_VECTOR_BIN) $(TEST_STACK_BIN) $(TEST_GENQUEUE_BIN)

# Target 1: Build the main application
$(APP_BIN): $(SRC_DIR)/main.c $(SRC_DIR)/vector.c $(SRC_DIR)/genstack.c $(SRC_DIR)/genqueue.c $(SRC_DIR)/class_recursia.c $(SRC_DIR)/hanoi.c
	$(CC) $(CFLAGS) -o $(APP_BIN) $(SRC_DIR)/main.c $(SRC_DIR)/vector.c $(SRC_DIR)/genstack.c $(SRC_DIR)/genqueue.c $(SRC_DIR)/class_recursia.c $(SRC_DIR)/hanoi.c

# Target 2: Build the vector test runner
$(TEST_VECTOR_BIN): $(TEST_DIR)/test_vector.c $(SRC_DIR)/vector.c
	$(CC) $(CFLAGS) $(TEST_DIR)/test_vector.c $(SRC_DIR)/vector.c -o $(TEST_VECTOR_BIN)

# Target 3: Build the stack test runner
$(TEST_STACK_BIN): $(TEST_DIR)/test_stack.c $(SRC_DIR)/genstack.c $(SRC_DIR)/vector.c
	$(CC) $(CFLAGS) $(TEST_DIR)/test_stack.c $(SRC_DIR)/genstack.c $(SRC_DIR)/vector.c -o $(TEST_STACK_BIN)

# Target 4: Build the genqueue test runner
$(TEST_GENQUEUE_BIN): $(TEST_DIR)/test_genqueue.c $(SRC_DIR)/genqueue.c $(SRC_DIR)/vector.c
	$(CC) $(CFLAGS) $(TEST_DIR)/test_genqueue.c $(SRC_DIR)/genqueue.c $(SRC_DIR)/vector.c -o $(TEST_GENQUEUE_BIN)

# Target 5: Clean up compiled files
clean:
	rm -f $(APP_BIN) $(TEST_VECTOR_BIN) $(TEST_STACK_BIN) $(TEST_GENQUEUE_BIN)