start: help

all: fileio proc memalloc time syslim
all_clean: fileio_clean proc_clean memalloc_clean time_clean \
           syslim_clean

.PHONY: fileio
fileio:
	@make -C fileio

.PHONY: fileio_clean
fileio_clean:
	@make -C fileio clean

.PHONY: proc
proc:
	@make -C proc

.PHONY: proc_clean
proc_clean:
	@make -C proc clean

.PHONY: memalloc
memalloc:
	@make -C memalloc

.PHONY: memalloc_clean
memalloc_clean:
	@make -C memalloc clean

.PHONY: time
time:
	@make -C time

.PHONY: time_clean
time_clean:
	@make -C time clean

.PHONY: syslim
syslim:
	@make -C syslim

.PHONY: syslim_clean
syslim_clean:
	@make -C syslim clean


.PHONY: help
 help:
	@echo "================================= tlpi lean makefile ======================================================="
	@echo " Usage:"
	@echo "  make [help] | [<target>]"
	@echo "  help                                      Help from this Makefile contains only help for generic targets"
	@echo "  all | all_clean                           Build and clean all stuffs bins"
	@echo "  fileio | fileio_clean                     Build and clean stuffs for fileio"
	@echo "  proc | proc_clean                         Build and clean stuffs for proc"
	@echo "  memalloc | memalloc_clean                 Build and clean stuffs for memalloc"
	@echo "  time | time_clean                         Build and clean stuffs for time"
	@echo "  syslim | syslim_clean                     Build and clean stuffs for time"
	@echo "============================================================================================================"
