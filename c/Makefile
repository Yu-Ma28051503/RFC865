############################################################
# RFC865 QOTD Project Makefile
# 対象: tcp_server tcp_client udp_server udp_client
# 共通ヘッダ: common.h / 共通実装: common.c
############################################################

# 使用コンパイラ
CC := cc

# 共通警告 & 規格
WARNINGS := -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wcast-align -Wstrict-prototypes -Wmissing-prototypes -Wformat=2 \
            -Wundef -Wpointer-arith -Winit-self -Wmissing-include-dirs -Wswitch-enum -Wwrite-strings

# 最適化 (デフォルトは Release)
OPT_RELEASE := -O2
OPT_DEBUG   := -O0 -g3 -fsanitize=address,undefined -fno-omit-frame-pointer

# 依存関係自動生成フラグ
DEPFLAGS := -MMD -MP

# 共通CFLAGS
CSTD     := -std=c11
INCLUDES := -I.
DEFINES  :=
BASE_CFLAGS := $(CSTD) $(WARNINGS) $(INCLUDES) $(DEFINES) $(DEPFLAGS)

# 指定が無ければ BUILD=release
BUILD ?= release

ifeq ($(BUILD),release)
	CFLAGS := $(BASE_CFLAGS) $(OPT_RELEASE)
	LDFLAGS :=
else ifeq ($(BUILD),debug)
	CFLAGS := $(BASE_CFLAGS) $(OPT_DEBUG)
	LDFLAGS := -fsanitize=address,undefined
else
	$(error BUILD は release か debug を指定してください (例: make BUILD=debug))
endif

# ソース
SRCS_COMMON := common.c
SRCS_TCP    := tcp_server.c tcp_client.c
SRCS_UDP    := udp_server.c udp_client.c
SRCS_ALL    := $(SRCS_COMMON) $(SRCS_TCP) $(SRCS_UDP)

# 実行ファイル
PROGS := tcp_server tcp_client udp_server udp_client

# ビルドディレクトリ
BUILD_DIR := build/$(BUILD)

# オブジェクト (build/ 以下へ)
OBJS := $(addprefix $(BUILD_DIR)/,$(SRCS_ALL:.c=.o))

# common.o をリンクする個別ターゲットの依存
COMMON_OBJ := $(BUILD_DIR)/common.o

.PHONY: all release debug clean distclean run-tcp-server run-tcp-client run-udp-server run-udp-client help

all: $(PROGS)

release:
	$(MAKE) BUILD=release all

debug:
	$(MAKE) BUILD=debug   all

# 個別リンク規則
tcp_server: $(COMMON_OBJ) $(BUILD_DIR)/tcp_server.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

tcp_client: $(COMMON_OBJ) $(BUILD_DIR)/tcp_client.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

udp_server: $(COMMON_OBJ) $(BUILD_DIR)/udp_server.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

udp_client: $(COMMON_OBJ) $(BUILD_DIR)/udp_client.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# パターンルール: .c -> .o (build ディレクトリ内)
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ビルドディレクトリ作成
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

clean:
	rm -rf build/debug build/release *.dSYM
	rm -f $(PROGS)

distclean: clean

help:
	@echo 'Usage:'
	@echo '  make [BUILD=release|debug]            # 全ターゲットビルド (デフォルト: release)'
	@echo '  make debug                            # デバッグビルド (ASan/UBSan 有効)'
	@echo '  make clean / distclean'

# 依存関係ファイル取り込み (.d)
-include $(OBJS:.o=.d)

############################################################
# End of Makefile
############################################################
