# Compiler & flags
CC := gcc
CFLAGS := -Wall -Wextra -Iinclude

# Dossiers
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# Fichiers sources
SOURCES := $(wildcard $(SRC_DIR)/*.c)
UTILS := $(SRC_DIR)/utils.c
OTHERS := $(filter-out $(UTILS), $(SOURCES))
BINARIES := $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%, $(OTHERS))

# Fichiers objets
OBJ_UTILS := $(OBJ_DIR)/utils.o
OBJ_OTHERS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(OTHERS))

# Règle principale
all: $(BINARIES) clean-object

# Compilation des .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Compilation de utils.o (unique)
$(OBJ_UTILS): $(UTILS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Link final : chaque binaire avec utils
$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(OBJ_UTILS)
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "compiled $@"

# Nettoyage
clean:
	@rm -rf $(BIN_DIR) $(OBJ_DIR)

clean-object:
	@rm -rf $(OBJ_DIR)

.PHONY: clean all

