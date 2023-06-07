# Copyright © 2023 Camilo Suárez Sandí

# Project

PROJECT_NAME = Proyecto Integrador
PROJECT_ID = proyecto_integrador

# Options

ARGS = configuration.json
DEFINITIONS = 
DEPENDENCIES = openssl libssl-dev sqlite3 libsqlite3-dev libjsoncpp-dev libgtest-dev
LIBRARIES = crypto sqlite3 jsoncpp gtest gtest_main

LINT = --filter=-build/include_subdir --quiet

# Language

CC = gcc
CXX = g++

CC_VERSION = -std=gnu17
CXX_VERSION = -std=gnu++20

# Flags

FLAGS = -Wall -Wextra -Wno-write-strings

# Directories

SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build
BIN_DIR = bin

# Files

C_SRC_FILES = $(shell find $(SRC_DIR) -type f -name '*.c')
CPP_SRC_FILES = $(shell find $(SRC_DIR) -type f -name '*.cpp')

C_TEST_SRC_FILES = $(shell find $(TEST_DIR) -type f -name '*.c')
CPP_TEST_SRC_FILES = $(shell find $(TEST_DIR) -type f -name '*.cpp')

C_OBJECT_FILES = $(C_SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
CPP_OBJECT_FILES = $(CPP_SRC_FILES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

C_TEST_OBJECT_FILES = \
	$(C_TEST_SRC_FILES:$(TEST_DIR)/%.c=$(BUILD_DIR)/%.o)
CPP_TEST_OBJECT_FILES = \
	$(CPP_TEST_SRC_FILES:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/%.o)

EXE_FILES = $(C_OBJECT_FILES) $(CPP_OBJECT_FILES)
TEST_EXE_FILES = $(EXE_FILES) $(C_TEST_OBJECT_FILES) $(CPP_TEST_OBJECT_FILES)

EXE = $(BIN_DIR)/$(PROJECT_ID)
TEST_EXE = $(BIN_DIR)/$(TEST_DIR)/$(PROJECT_ID)

LINT_FILES = $(C_SRC_FILES) $(CPP_SRC_FILES) \
	$(C_HEADER_SRC_FILES) $(CPP_HEADER_SRC_FILES) \
	$(C_TEST_SRC_FILES) $(CPP_TEST_SRC_FILES) \
	$(C_HEADER_TEST_SRC_FILES) $(CPP_HEADER_TEST_SRC_FILES)

# Targets

.PHONY: all build run test clean install lint check help

all: build

build: $(EXE)

$(EXE): $(EXE_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $^ -o $@ $(addprefix -l, $(LIBRARIES))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CC_VERSION) $(FLAGS) -c $< -o $@ $(addprefix -D, $(DEFINITIONS))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXX_VERSION) $(FLAGS) -c $< -o $@ $(addprefix -D, $(DEFINITIONS))

run: build
	$(EXE) $(ARGS)

test: DEFINITIONS += TEST
test: $(TEST_EXE)
	$(TEST_EXE) $(ARGS)

$(TEST_EXE): $(TEST_EXE_FILES)
	@mkdir -p $(BIN_DIR)/$(TEST_DIR)
	$(CXX) $^ -o $@ $(addprefix -l, $(LIBRARIES))

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CC_VERSION) $(FLAGS) -I$(SRC_DIR) -c $< -o $@ \
	$(addprefix -D, $(DEFINITIONS))

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXX_VERSION) $(FLAGS) -I$(SRC_DIR) -c $< -o $@ \
	$(addprefix -D, $(DEFINITIONS))

clean:
	rm -fr $(BUILD_DIR) $(BIN_DIR)

install:
	sudo apt install python3
	sudo apt install python3-pip
	pip3 install cpplint
	sudo apt install $(DEPENDENCIES)

lint:
	python3 -m cpplint $(LINT) $(LINT_FILES)

check: test lint

asan: FLAGS += -fsanitize=address
asan: build

tsan: FLAGS += -fsanitize=thread
tsan: build

help:
	@echo "Usage: make [target] [variables]"
	@echo ""
	@echo "Targets:"
	@echo "  build		Build the project."
	@echo "  run		Run the binary."
	@echo "  test		Build and run the tests."
	@echo "  clean		Remove the binary files."
	@echo "  install	Install the dependencies."
	@echo "  lint		Run the linter."
	@echo "  check		Run the tests and the linter."
	@echo "  help		Print this help message."
