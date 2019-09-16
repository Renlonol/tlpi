start: help

all: fileio proc memalloc time syslim sysinfo files signals
all_clean: fileio_clean proc_clean memalloc_clean time_clean \
           syslim_clean sysinfo_clean files_clean signals_clean

.PHONY: fileio
fileio:
	@make -C fileio
	@echo "== Build $@ done"

.PHONY: fileio_clean
fileio_clean:
	@make -C fileio clean

.PHONY: proc
proc:
	@make -C proc
	@echo "== Build $@ done"

.PHONY: proc_clean
proc_clean:
	@make -C proc clean

.PHONY: memalloc
memalloc:
	@make -C memalloc
	@echo "== Build $@ done"

.PHONY: memalloc_clean
memalloc_clean:
	@make -C memalloc clean

.PHONY: time
time:
	@make -C time
	@echo "== Build $@ done"

.PHONY: time_clean
time_clean:
	@make -C time clean

.PHONY: syslim
syslim:
	@make -C syslim
	@echo "== Build $@ done"

.PHONY: syslim_clean
syslim_clean:
	@make -C syslim clean

.PHONY: sysinfo
sysinfo:
	@make -C sysinfo
	@echo "== Build $@ done"

.PHONY: sysinfo_clean
sysinfo_clean:
	@make -C sysinfo clean

.PHONY: files
files:
	@make -C files
	@echo "== Build $@ done"

.PHONY: files_clean
files_clean:
	@make -C files clean

.PHONY: signals
signals:
	@make -C signals
	@echo "== Build $@ done"

.PHONY: signals_clean
signals_clean:
	@make -C signals clean

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
	@echo "  syslim | syslim_clean                     Build and clean stuffs for syslim"
	@echo "  sysinfo | sysinfo_clean                   Build and clean stuffs for sysinfo"
	@echo "  files | files_clean                       Build and clean stuffs for files"
	@echo "  signals | signals_clean                   Build and clean stuffs for signals"
	@echo "============================================================================================================"
