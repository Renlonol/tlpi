all: help

.PHONY: fileio
fileio:
	make -C fileio

.PHONY: fileio_clean
fileio_clean:
	make -C fileio clean




.PHONY: help
 help:
	@echo "================================= tlpi lean makefile ========================================"
	@echo " Usage:"
	@echo "  make [help] | [<target>]"
	@echo "  help                       Help from this Makefile contains only help for generic targets"
	@echo "  fileio                     all bins for fileio"
	@echo "============================================================================================="