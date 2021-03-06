start: help

all: fileio proc memalloc time syslim sysinfo files signals timers \
		threads ipc sockets altio
clean-all: fileio_clean proc_clean memalloc_clean time_clean \
           syslim_clean sysinfo_clean files_clean signals_clean \
		   timers_clean threads_clean ipc_clean sockets_clean \
		   altio_clean

.PHONY: fileio
fileio:
	@make -C fileio -j
	@echo "== Build $@ done"

.PHONY: fileio_clean
fileio_clean:
	@make -C fileio clean

.PHONY: proc
proc:
	@make -C proc -j
	@echo "== Build $@ done"

.PHONY: proc_clean
proc_clean:
	@make -C proc clean

.PHONY: memalloc
memalloc:
	@make -C memalloc -j
	@echo "== Build $@ done"

.PHONY: memalloc_clean
memalloc_clean:
	@make -C memalloc clean

.PHONY: time
time:
	@make -C time -j
	@echo "== Build $@ done"

.PHONY: time_clean
time_clean:
	@make -C time clean

.PHONY: syslim
syslim:
	@make -C syslim -j
	@echo "== Build $@ done"

.PHONY: syslim_clean
syslim_clean:
	@make -C syslim clean

.PHONY: sysinfo
sysinfo:
	@make -C sysinfo -j
	@echo "== Build $@ done"

.PHONY: sysinfo_clean
sysinfo_clean:
	@make -C sysinfo clean

.PHONY: files
files:
	@make -C files -j
	@echo "== Build $@ done"

.PHONY: files_clean
files_clean:
	@make -C files clean

.PHONY: signals
signals:
	@make -C signals -j
	@echo "== Build $@ done"

.PHONY: signals_clean
signals_clean:
	@make -C signals clean

.PHONY: timers
timers:
	@make -C timers -j
	@echo "== Build $@ done"

.PHONY: timers_clean
timers_clean:
	@make -C timers clean

.PHONY: threads
threads:
	@make -C threads -j
	@echo "== Build $@ done"

.PHONY: threads_clean
threads_clean:
	@make -C threads clean

.PHONY: ipc
ipc:
	@make -C ipc -j
	@echo "== Build $@ done"

.PHONY: ipc_clean
ipc_clean:
	@make -C ipc clean

.PHONY: sockets
sockets:
	@make -C sockets -j
	@echo "== Build $@ done"

.PHONY: sockets_clean
sockets_clean:
	@make -C sockets clean

.PHONY: altio
altio:
	@make -C altio -j
	@echo "== Build $@ done"

.PHONY: altio_clean
altio_clean:
	@make -C altio clean

.PHONY: help
 help:
	@echo "================================= tlpi lean makefile ======================================================="
	@echo " Usage:"
	@echo "  make [help] | [<target>]"
	@echo "  help                                      Help from this Makefile contains only help for generic targets"
	@echo "  all      | clean-all                      Build and clean all stuffs bins"
	@echo "  fileio   | fileio_clean                   Build and clean stuffs for fileio"
	@echo "  proc     | proc_clean                     Build and clean stuffs for proc"
	@echo "  memalloc | memalloc_clean                 Build and clean stuffs for memalloc"
	@echo "  time     | time_clean                     Build and clean stuffs for time"
	@echo "  syslim   | syslim_clean                   Build and clean stuffs for syslim"
	@echo "  sysinfo  | sysinfo_clean                  Build and clean stuffs for sysinfo"
	@echo "  files    | files_clean                    Build and clean stuffs for files"
	@echo "  signals  | signals_clean                  Build and clean stuffs for signals"
	@echo "  timers   | timers_clean                   Build and clean stuffs for timers"
	@echo "  threads  | threads_clean                  Build and clean stuffs for threads"
	@echo "  ipc      | ipc_clean                      Build and clean stuffs for ipc"
	@echo "  sockets  | sockets_clean                  Build and clean stuffs for sockets"
	@echo "  altio    | altio_clean                    Build and clean stuffs for altio"
	@echo "============================================================================================================"
