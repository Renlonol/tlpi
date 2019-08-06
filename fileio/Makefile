COMMOM_SRC_DIR = ../common
INCLUDE_DIR = ../common

COMMON_SRC_FILES = $(wildcard $(COMMOM_SRC_DIR)/*.c)
COMMOM_OBJS = $(patsubst %.c, %.o, $(COMMON_SRC_FILES))

ALL_TARGETS = copy


CC = gcc
CFLAGS = -g -Wall -I$(INCLUDE_DIR)

copy: $(COMMOM_OBJS) copy.o
	@$(CC) $^ -o $@
	@echo "==build $@ done"

$(COMMOM_SRC_DIR)/%.o : $(COMMOM_SRC_DIR)/%.c
	@echo "  cc $<"
	@$(CC) $(CFLAGS) -c $< -o $@

%.o : %.c
	@echo "  cc $<"
	@$(CC) $(CFLAGS) -c $< -o $@


.PHONY : clean
clean:
	@rm -f $(ALL_TARGETS)
	@rm -f $(COMMOM_SRC_DIR)/*.o
	@rm -f ./*.o
	@echo "clean fileio done"



