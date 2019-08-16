start: help

all: fileio proc
all_clean: fileio_clean proc_clean

.PHONY: fileio
fileio:
	make -C fileio

.PHONY: fileio_clean
fileio_clean:
	make -C fileio clean

.PHONY: proc
proc:
	make -C proc

.PHONY: proc_clean
proc_clean:
	make -C proc clean

.PHONY: help
 help:
	@echo "================================= tlpi lean makefile ======================================================="
	@echo " Usage:"
	@echo "  make [help] | [<target>]"
	@echo "  help                                      Help from this Makefile contains only help for generic targets"
	@echo "  all | all_clean                           Build and clean all stuffs bins"
	@echo "  fileio | fileio_clean                     Build and clean stuffs for fileio"
	@echo "  proc | proc_clean                         Build and clean stuffs for proc"
	@echo "============================================================================================================"
