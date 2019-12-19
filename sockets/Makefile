COMMOM_SRC_DIR = ../common
COMMOM_OBJ_DIR = ../common/obj
INCLUDE_DIR = ../common

BIN_DIR = ./bin
OBJ_DIR = ./obj

COMMON_SRC_FILES = $(wildcard $(COMMOM_SRC_DIR)/*.c)
COMMOM_OBJS = $(patsubst $(COMMOM_SRC_DIR)/%.c, $(COMMOM_OBJ_DIR)/%.o, $(COMMON_SRC_FILES))
BIN_OBJS = $(OBJ_DIR)/us_xfr_sv.o $(OBJ_DIR)/us_xfr_cl.o $(OBJ_DIR)/ud_ucase_sv.o $(OBJ_DIR)/ud_ucase_cl.o \
			$(OBJ_DIR)/i6d_ucase_cl.o $(OBJ_DIR)/i6d_ucase_sv.o $(OBJ_DIR)/is_seqnum_sv.o $(OBJ_DIR)/is_seqnum_cl.o \
			$(OBJ_DIR)/id_echo_sv.o $(OBJ_DIR)/id_echo_cl.o $(OBJ_DIR)/is_echo_sv.o $(OBJ_DIR)/is_echo_cl.o $(OBJ_DIR)/is_echo_cl_shutdown.o

SRC_FILES = $(wildcard ./*.c)
OBJ_FILES = $(patsubst ./%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
OBJS_AUX  = $(filter-out $(BIN_OBJS), $(OBJ_FILES))

all: $(BIN_DIR)/us_xfr_sv $(BIN_DIR)/us_xfr_cl $(BIN_DIR)/ud_ucase_sv $(BIN_DIR)/ud_ucase_cl \
		$(BIN_DIR)/i6d_ucase_cl $(BIN_DIR)/i6d_ucase_sv $(BIN_DIR)/is_seqnum_sv $(BIN_DIR)/is_seqnum_cl \
		$(BIN_DIR)/id_echo_sv $(BIN_DIR)/id_echo_cl $(BIN_DIR)/is_echo_sv $(BIN_DIR)/is_echo_cl $(BIN_DIR)/is_echo_cl_shutdown

CC = gcc
CFLAGS = -g -Wall -I$(INCLUDE_DIR)
LIBRARY =

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
	@echo "Clean sockets done"
