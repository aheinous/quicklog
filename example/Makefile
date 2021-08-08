TARGET_EXEC := bad_tests


BUILD_DIR_ROOT := ./build
# account for ..
BUILD_DIR := $(BUILD_DIR_ROOT)/$(TARGET_EXEC)


CC := gcc-11




# SRCS:= src/main.c src/qkl/decode.c src/qkl/sem.c src/qkl/lr_buff.c \
# 		src/qkl/usr/platform.c src/qkl/client.c src/qkl/server.c \
# 		src/qkl/usr/config.c


SRCS := $(shell find ../src -name "*.c" )
SRCS += $(shell find src -name "*.c" )


OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS = include ../include
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS := $(INC_FLAGS)  -MMD -MP
CFLAGS := -save-temps=obj  -fdiagnostics-color=always -g
LDFLAGS := -pthread -g


# The final build step.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)


# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR_ROOT)



print:
	@echo $(SRCS)
	@echo $(CXX_SRCS)
	@echo $(OBJS)
