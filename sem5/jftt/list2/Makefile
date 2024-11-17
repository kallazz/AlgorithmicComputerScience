FLEX = flex
CC = clang
CFLAGS = -o

SRC_DIR = src
BUILD_DIR = build

TASKS = task1 task2 task3 task4

all: $(addprefix $(BUILD_DIR)/, $(TASKS))

$(BUILD_DIR)/%: $(SRC_DIR)/%.l | $(BUILD_DIR)
	$(FLEX) -o $(BUILD_DIR)/lex.yy.c $<
	$(CC) $(CFLAGS) $@ $(BUILD_DIR)/lex.yy.c

$(BUILD_DIR)/task4: $(SRC_DIR)/task4.l | $(BUILD_DIR)
	$(FLEX) -o $(BUILD_DIR)/lex.yy.c $<
	$(CC) $(CFLAGS) $@ $(BUILD_DIR)/lex.yy.c -lm

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(BUILD_DIR)/lex.yy.c $(addprefix $(BUILD_DIR)/, $(TASKS))
