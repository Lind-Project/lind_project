#
# Try to ease the burden of building lind (repy, nacl, and toolchain)
#
# Created by Joey Pabalinas <joeypabalinas@gmail.com>

BUILD_DIR := ./lind
BUILD_SCRIPT := ./build.sh

all:
	@echo
	@echo Please change directory into $(BUILD_DIR) before running $(BUILD_SCRIPT)
	@cd $(BUILD_DIR) && \
		$(BUILD_SCRIPT) -h
