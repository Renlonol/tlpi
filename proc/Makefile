COMMOM_SRC_DIR = ../common
COMMOM_OBJ_DIR = ../common/obj
INCLUDE_DIR = ../common

BIN_DIR = ./bin
OBJ_DIR = ./obj

COMMON_SRC_FILES = $(wildcard $(COMMOM_SRC_DIR)/*.c)
COMMOM_OBJS = $(patsubst $(COMMOM_SRC_DIR)/%.c, $(COMMOM_OBJ_DIR)/%.o, $(COMMON_SRC_FILES))
BIN_OBJS = $(OBJ_DIR)/display_env.o $(OBJ_DIR)/modify_env.o $(OBJ_DIR)/longjmp.o $(OBJ_DIR)/fork_sig_sync.o \
			$(OBJ_DIR)/exit_handlers.o $(OBJ_DIR)/fork_stdio_buf.o $(OBJ_DIR)/multi_wait.o $(OBJ_DIR)/child_status.o \
			$(OBJ_DIR)/multi_sigchld.o

SRC_FILES = $(wildcard ./*.c)
OBJ_FILES = $(patsubst ./%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
OBJS_AUX  = $(filter-out $(BIN_OBJS), $(OBJ_FILES))

all: $(BIN_DIR)/display_env $(BIN_DIR)/modify_env $(BIN_DIR)/longjmp $(BIN_DIR)/fork_sig_sync \
		$(BIN_DIR)/exit_handlers $(BIN_DIR)/fork_stdio_buf $(BIN_DIR)/multi_wait $(BIN_DIR)/child_status \
		$(BIN_DIR)/multi_sigchld

CC = gcc
CFLAGS = -g -Wall -I$(INCLUDE_DIR)
LIBRARY =

LIBS += $(LIBRARY:%=-l%)

$(BIN_DIR)/%: $(COMMOM_OBJS) $(OBJ_DIR)/%.o $(OBJS_AUX) | $(BIN_DIR) $(OBJ_DIR)
	@$(CC) $^ -o $@

.PRECIOUS: $(COMMOM_OBJ_DIR)/%.o
$(COMMOM_OBJ_DIR)/%.o : $(COMMOM_SRC_DIR)/%.c | $(COMMOM_OBJ_DIR)
	@echo "  cc $<"
	@$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(OBJ_DIR)/%.o
$(OBJ_DIR)/%.o : %.c
	@echo "  cc $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR) $(COMMOM_OBJ_DIR):
	@mkdir -p $@

.PHONY : clean
clean:
	@rm -fr $(BIN_DIR) $(OBJ_DIR)
	@rm -fr $(COMMOM_OBJ_DIR)
	@echo "Clean proc done"
