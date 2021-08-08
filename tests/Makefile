.DELETE_ON_ERROR:

TARGET_EXEC := tests

BUILD_DIR_ROOT := ./build
# account for ..
BUILD_DIR := $(BUILD_DIR_ROOT)/$(TARGET_EXEC)

CC := gcc-11
CXX := g++-11



WARNINGS := -Wall -Wextra 	-Wno-unused-value \
							-Wno-unused-function \
							-Wno-implicit-fallthrough \
							-Wno-unused-parameter

SRCS := $(shell find ../src -name "*.c" )
SRCS += $(shell find src -name "*.c" )

CXX_SRCS += $(shell find src -name "*.cpp" )


OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
OBJS += $(CXX_SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS = include ../include
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS := $(INC_FLAGS)  -MMD -MP -DQKL_INCLUDE_TESTS
CFLAGS := -save-temps=obj  -fdiagnostics-color=always -g $(WARNINGS)
CXXFLAGS := -save-temps=obj  -fdiagnostics-color=always -g $(WARNINGS)
LDFLAGS := -pthread -g


# The final build step.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)


# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC)  $(CPPFLAGS) $(CFLAGS) -c $< -o $@



# Build step for C++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@




.PHONY: clean rebuild run
clean:
	-rm -r $(BUILD_DIR_ROOT)


rebuild: clean $(BUILD_DIR)/$(TARGET_EXEC)


run: $(BUILD_DIR)/$(TARGET_EXEC)
	./$(BUILD_DIR)/$(TARGET_EXEC)



print:
	@echo $(SRCS)
	@echo $(CXX_SRCS)
	@echo $(OBJS)


-include $(DEPS)