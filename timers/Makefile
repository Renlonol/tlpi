COMMOM_SRC_DIR = ../common
COMMOM_OBJ_DIR = ../common/obj
INCLUDE_DIR = ../common

BIN_DIR = ./bin
OBJ_DIR = ./obj

COMMON_SRC_FILES = $(wildcard $(COMMOM_SRC_DIR)/*.c)
COMMOM_OBJS = $(patsubst $(COMMOM_SRC_DIR)/%.c, $(COMMOM_OBJ_DIR)/%.o, $(COMMON_SRC_FILES))
BIN_OBJS = $(OBJ_DIR)/real_timer.o $(OBJ_DIR)/timed_read.o $(OBJ_DIR)/t_nanosleep.o $(OBJ_DIR)/ptmr_sigev_signal.o

SRC_FILES = $(wildcard ./*.c)
OBJ_FILES = $(patsubst ./%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
OBJS_AUX  = $(filter-out $(BIN_OBJS), $(OBJ_FILES))

all: $(BIN_DIR)/real_timer $(BIN_DIR)/timed_read $(BIN_DIR)/t_nanosleep $(BIN_DIR)/ptmr_sigev_signal

CC = gcc
CFLAGS = -g -Wall -I$(INCLUDE_DIR)
LIBRARY = rt

LIBS += $(LIBRARY:%=-l%)

$(BIN_DIR)/%: $(COMMOM_OBJS) $(OBJ_DIR)/%.o $(OBJS_AUX) | $(BIN_DIR) $(OBJ_DIR)
	@$(CC) $^ -o $@ $(LIBS)

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
	@echo "Clean timers done"
