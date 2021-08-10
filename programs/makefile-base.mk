.DELETE_ON_ERROR:


# need
# 		TARGET_EXEC
#		QKL_DIR

# optional
# 		CPPFLAGS
# 		CFLAGS
# 		CXXFLAGS
#		LDFLAGS
# 		INC_DIRS
#		SRC_DIRS
#		SRC_INC_DIRS




BUILD_DIR := ./build


SRC_INC_DIRS := ./ $(SRC_INC_DIRS) $(QKL_DIR)

SRC_DIRS += $(foreach dir, $(SRC_INC_DIRS), $(dir)/src)
INC_DIRS += $(foreach dir, $(SRC_INC_DIRS), $(dir)/include)


C_SRCS += $(foreach dir,$(SRC_DIRS), $(shell find $(dir) -name "*.c" ))
CXX_SRCS += $(foreach dir,$(SRC_DIRS), $(shell find $(dir) -name "*.cpp" ))

OBJS := $(C_SRCS:%=$(BUILD_DIR)/%.o)
OBJS += $(CXX_SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# putting include before $(QKL_DIR)/include means our versions of
# qkl/usr/*.h will be used in place of the default ones
# from the library
# INC_DIRS += include
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS := $(INC_FLAGS)  -MMD -MP $(CPPFLAGS)
CFLAGS := -save-temps=obj -fdiagnostics-color=always -g -Wall -Wextra $(CFLAGS)
CXXFLAGS := -save-temps=obj -fdiagnostics-color=always -g -Wall -Wextra -std=gnu++14 $(CXXFLAGS)


# The final build step.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
ifndef TARGET_EXEC
	@echo "TARGET_EXEC undefined"
	@false
endif
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)


# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
ifndef QKL_DIR
	@echo "QKL_DIR undefined"
	@false
endif
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
	@echo $(C_SRCS)
	@echo $(CXX_SRCS)
	@echo $(OBJS)
	@echo $(QKL_DIR)

-include $(DEPS)
