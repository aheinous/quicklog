
TARGET_EXEC := unittests
QKL_DIR := $(shell realpath ../..)

CFLAGS :=   -O2
CXXFLAGS := -O2
LDFLAGS := -pthread -g
CPPFLAGS := -DQKL_INCLUDE_TESTS

# SRC_DIRS := $(QKL_DIR)/configs/basic_desktop
SRC_INC_DIRS = $(QKL_DIR)/platforms/pthreads

-include ../makefile-base.mk
