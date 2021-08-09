.DELETE_ON_ERROR:

TARGET_EXEC := example

BUILD_DIR := ./build

QKL_DIR := $(shell realpath ..)

SRCS := $(shell find $(QKL_DIR)/src -name "*.c" )
SRCS += $(shell find src -name "*.c" )

CXX_SRCS += $(shell find src -name "*.cpp" )

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
OBJS += $(CXX_SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# putting include before $(QKL_DIR)/include means our versions of
# qkl/usr/*.h will be used in place of the default ones
# from the library
INC_DIRS = include $(QKL_DIR)/include
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS := $(INC_FLAGS)  -MMD -MP
CFLAGS := -save-temps=obj  -fdiagnostics-color=always -g -Wall -Wextra
CXXFLAGS := -save-temps=obj  -fdiagnostics-color=always -g -Wall -Wextra
LDFLAGS := -pthread -g


# The final build step.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)


# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@


# Build step for C++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@



.PHONY: clean rebuild run
clean:
	-rm -r $(BUILD_DIR)


rebuild: clean $(BUILD_DIR)/$(TARGET_EXEC)


run: $(BUILD_DIR)/$(TARGET_EXEC)
	./$(BUILD_DIR)/$(TARGET_EXEC)



print:
	@echo $(SRCS)
	@echo $(CXX_SRCS)
	@echo $(OBJS)
	@echo $(QKL_DIR)

-include $(DEPS)
