COMPILER = g++
FLEX = flex
BISON = bison

SRC_DIR = src
BUILD_DIR = build

LEX_FILE = $(SRC_DIR)/lexer.l
BISON_FILE = $(SRC_DIR)/parser.ypp
TAB_CPP = $(BUILD_DIR)/parser.tab.cpp
TAB_HPP = $(BUILD_DIR)/parser.tab.hpp
LEX_CPP = $(BUILD_DIR)/lex.yy.c
EXECUTABLE = $(BUILD_DIR)/fieldCalculator
FIELD_OPERATIONS = $(SRC_DIR)/fieldOperations.cpp

all: $(EXECUTABLE)

$(EXECUTABLE): $(TAB_CPP) $(LEX_CPP) $(FIELD_OPERATIONS) | $(BUILD_DIR)
	$(COMPILER) -I$(SRC_DIR) $(TAB_CPP) $(LEX_CPP) $(FIELD_OPERATIONS) -o $(EXECUTABLE)

$(TAB_CPP) $(TAB_HPP): $(BISON_FILE) | $(BUILD_DIR)
	$(BISON) -d -o $(TAB_CPP) $(BISON_FILE)

$(LEX_CPP): $(LEX_FILE) | $(BUILD_DIR)
	$(FLEX) -o $(LEX_CPP) $(LEX_FILE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(EXECUTABLE) $(TAB_CPP) $(TAB_HPP) $(LEX_CPP)

.PHONY: all clean