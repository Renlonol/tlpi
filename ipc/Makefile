COMMOM_SRC_DIR = ../common
COMMOM_OBJ_DIR = ../common/obj
INCLUDE_DIR = ../common

BIN_DIR = ./bin
OBJ_DIR = ./obj

COMMON_SRC_FILES = $(wildcard $(COMMOM_SRC_DIR)/*.c)
COMMOM_OBJS = $(patsubst $(COMMOM_SRC_DIR)/%.c, $(COMMOM_OBJ_DIR)/%.o, $(COMMON_SRC_FILES))
BIN_OBJS = $(OBJ_DIR)/simple_pipe.o $(OBJ_DIR)/pipe_sync.o $(OBJ_DIR)/pipe_ls_wc.o \
			$(OBJ_DIR)/fifo_seqnum_server.o $(OBJ_DIR)/fifo_seqnum_client.o \
			$(OBJ_DIR)/mmcat.o $(OBJ_DIR)/t_mmap.o $(OBJ_DIR)/anon_mmap.o $(OBJ_DIR)/pmsg_create.o \
			$(OBJ_DIR)/pmsg_getattr.o $(OBJ_DIR)/pmsg_unlink.o $(OBJ_DIR)/pmsg_send.o $(OBJ_DIR)/pmsg_receive.o \
			$(OBJ_DIR)/pshm_create.o $(OBJ_DIR)/pshm_write.o $(OBJ_DIR)/pshm_read.o $(OBJ_DIR)/pshm_unlink.o

SRC_FILES = $(wildcard ./*.c)
OBJ_FILES = $(patsubst ./%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
OBJS_AUX  = $(filter-out $(BIN_OBJS), $(OBJ_FILES))

all: $(BIN_DIR)/simple_pipe $(BIN_DIR)/pipe_sync $(BIN_DIR)/pipe_ls_wc \
		$(BIN_DIR)/fifo_seqnum_client $(BIN_DIR)/fifo_seqnum_server \
		$(BIN_DIR)/mmcat $(BIN_DIR)/t_mmap $(BIN_DIR)/anon_mmap $(BIN_DIR)/pmsg_create \
		$(BIN_DIR)/pmsg_getattr $(BIN_DIR)/pmsg_unlink $(BIN_DIR)/pmsg_send $(BIN_DIR)/pmsg_receive \
		$(BIN_DIR)/pshm_create $(BIN_DIR)/pshm_write $(BIN_DIR)/pshm_read $(BIN_DIR)/pshm_unlink

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
	@echo "Clean ipc done"
