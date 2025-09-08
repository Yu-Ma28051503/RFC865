############################################################
# RFC865 QOTD Project (C++) Makefile
# Targets: tcp_server tcp_client udp_server udp_client
# Common source: common.cpp / header: common.hpp
############################################################

# Compiler & tools
CXX      := c++

# Warnings & language standard
CXXSTD   := -std=c++20
WARNINGS := -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wold-style-cast -Wnon-virtual-dtor \
            -Woverloaded-virtual -Wcast-align -Wnull-dereference -Wdouble-promotion -Wformat=2 \
            -Wundef -Wpointer-arith -Wswitch-enum -Wzero-as-null-pointer-constant

# Optimization / debugging
OPT_RELEASE := -O2
OPT_DEBUG   := -O0 -g3 -fsanitize=address,undefined -fno-omit-frame-pointer

# Dependency generation
DEPFLAGS := -MMD -MP

INCLUDES := -I.
DEFINES  :=

BASE_CXXFLAGS := $(CXXSTD) $(WARNINGS) $(INCLUDES) $(DEFINES) $(DEPFLAGS)

# Build type (default release)
BUILD ?= release

ifeq ($(BUILD),release)
	CXXFLAGS := $(BASE_CXXFLAGS) $(OPT_RELEASE)
	LDFLAGS  :=
else ifeq ($(BUILD),debug)
	CXXFLAGS := $(BASE_CXXFLAGS) $(OPT_DEBUG)
	LDFLAGS  := -fsanitize=address,undefined
else
	$(error BUILD は release か debug を指定してください (例: make BUILD=debug))
endif

# Sources
SRCS_COMMON := common.cpp
SRCS_TCP    := tcp_server.cpp tcp_client.cpp
SRCS_UDP    := udp_server.cpp udp_client.cpp
SRCS_ALL    := $(SRCS_COMMON) $(SRCS_TCP) $(SRCS_UDP)

# Programs
PROGS := tcp_server tcp_client udp_server udp_client

# Build directory
BUILD_DIR := build/$(BUILD)

# Objects
OBJS := $(addprefix $(BUILD_DIR)/,$(SRCS_ALL:.cpp=.o))
COMMON_OBJ := $(BUILD_DIR)/common.o

.PHONY: all release debug clean distclean help

all: $(PROGS)

release:
	$(MAKE) BUILD=release all

debug:
	$(MAKE) BUILD=debug all

# Link rules
tcp_server: $(COMMON_OBJ) $(BUILD_DIR)/tcp_server.o | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

tcp_client: $(COMMON_OBJ) $(BUILD_DIR)/tcp_client.o | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

udp_server: $(COMMON_OBJ) $(BUILD_DIR)/udp_server.o | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

udp_client: $(COMMON_OBJ) $(BUILD_DIR)/udp_client.o | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compile rule
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

clean:
	rm -rf build *.dSYM
	rm -f $(PROGS)

distclean: clean

help:
	@echo 'Usage:'
	@echo '  make [BUILD=release|debug]   # Build all programs (default: release)'
	@echo '  make debug                   # Debug build (ASan/UBSan)'
	@echo '  make clean / distclean'
	@echo '  (実行ヘルパーターゲットは要望により未提供)'

# Dependencies
-include $(OBJS:.o=.d)

############################################################
# End of Makefile
############################################################
