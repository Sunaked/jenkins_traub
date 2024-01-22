# ==============
# === COLORS ===
# =============

# Define variables for colors
Red:=$(shell tput setaf 1)     # Red
Green:=$(shell tput setaf 2)   # Green
Yellow:=$(shell tput setaf 3)  # Yellow
Blue:=$(shell tput setaf 4)    # Blue
Purple:=$(shell tput setaf 5)  # Purple
Cyan:=$(shell tput setaf 6)    # Cyan
White:=$(shell tput setaf 7)   # White
NC:=$(shell tput sgr0)         # No color

# =================
# === VARIABLES ===
# =================

# Create Current Working Directory (CWD) and path to log files (LOGPATH)
CWD := $(shell pwd)
ifeq ($(origin LOGPATH), undefined)
    LOGPATH := $(CWD)/log
endif

export CWD
export LOGPATH

# ====================================
# === To Build and Execute Project ===
# ====================================
all: build_run

build_run:
	@printf "${Purple}\nBuilding project ...${NC}\n"
	@mkdir -p build && cd build && cmake .. && make && echo "\n\n" && ./jenkins_traub

# Execute the tests
test:
	@printf "${Purple}\nRunning tests...${NC}\n"
	$(MAKE) -C tests/

# Execute the benchmarks
bench:
	@printf "${Purple}\nRunning benchmarks...${NC}\n"
	$(MAKE) -C bench/

# Clean the build directory
clean:
	@echo "Cleaning up..."
	@cd build && make clean
	$(MAKE) -C tests/ clean
	$(MAKE) -C benchmark/ clean

.PHONY: all clean build_run bench test

