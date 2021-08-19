##
# Sudoku Generator
# Thanks to Chase Lambert (https://makefiletutorial.com/#makefile-cookbook)
##

BUILD_DIR := ./build
LIB_DIR := ./build/lib
INC_DIRS := ./include
SRC_DIRS := ./src

SERVER_TARGET_EXEC := openSudoku-server
CLIENT_TARGET_EXEC := openSudoku-client

COMMON_LIB := libcommon.so

TARGETS := $(BUILD_DIR)/$(SERVER_TARGET_EXEC) $(BUILD_DIR)/$(CLIENT_TARGET_EXEC)

# Find all the C and C++ files we want to compile
SRCS := $(shell find $(SRC_DIRS) \( -name "*.cpp" -or -name "*.c" \) ! \( -path '*/server/*' -or -path '*/client/*' \))

SERVER_SRCS := $(shell find $(SRC_DIRS)/server -name *.cpp -or -name *.c)
CLIENT_SRCS := $(shell find $(SRC_DIRS)/client -name *.cpp -or -name *.c)

# String substitution for every C/C++ file.
# As an example, hello.cpp turns into ./build/hello.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

SERVER_OBJS := $(SERVER_SRCS:%=$(BUILD_DIR)/%.o)
CLIENT_OBJS := $(CLIENT_SRCS:%=$(BUILD_DIR)/%.o)

ALL_OBJS := $(SUDOKU_OBJS) $(SERVER_OBJS) $(CLIENT_OBJS)

# String substitution (suffix version without %).
# As an example, ./build/hello.cpp.o turns into ./build/hello.cpp.d
DEPS := $(ALL_OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS += $(shell find $(SRC_DIRS) -type d ! \( -path '*/server' -or -path '*/client' \))
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the ouput
CPPFLAGS := $(INC_FLAGS) -MMD -MP -g
CPPFLAGS += -g
CPPFLAGS += -Wall -Wextra
CPPFLAGS += -Wpedantic -Warray-bounds -Weffc++
CPPFLAGS += -Werror -Wno-error=effc++
CPPFLAGS += -fPIC

LDFLAGS := -pthread
LDFLAGS += -lboost_thread -lboost_system
LDFLAGS += -L$(LIB_DIR) -lcommon

all: $(TARGETS)

$(BUILD_DIR)/$(SERVER_TARGET_EXEC): $(LIB_DIR)/$(COMMON_LIB) $(SERVER_OBJS)
$(BUILD_DIR)/$(CLIENT_TARGET_EXEC): $(LIB_DIR)/$(COMMON_LIB) $(CLIENT_OBJS)

# The final build step
$(TARGETS):
	$(CXX) $^ -o $@ $(LDFLAGS)

# Link step for common library
$(LIB_DIR)/$(COMMON_LIB): $(OBJS)
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $^ -o $@ -shared

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Build step for C++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up
-include $(DEPS)

