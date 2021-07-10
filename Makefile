TARGET_EXEC := qkl


BUILD_DIR := ./build
SRC_DIRS := ./src

CC := gcc-11

SRCS:= src/main.c src/qkl_decode.c
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS = include
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS := $(INC_FLAGS)  -MMD -MP
CFLAGS := -save-temps=obj -std=c11 -fdiagnostics-color=always


# The final build step.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)


# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

