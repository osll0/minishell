# Project
NAME := minishell

# Toolchain
CC := cc
CFLAGS := -Wall -Wextra -Werror -g
INCLUDES := -Iinclude -Ilibft

# Libft
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

# Sources
SRC_MAIN := \
	src/main.c

SRC_ENV := \
	src/env/env_utils.c \
	src/env/env_list.c \
	src/env/env_from_environ.c \
	src/env/env_to_array.c

SRC_LEXER := \
	src/lexer/lexer.c \
	src/lexer/token_utils.c

SRC_PARSER := \
	src/parser/parser.c \
	src/parser/parser_utils.c

SRC_CORE := \
	src/core/loop.c \
	src/core/loop_helpers.c \
	src/core/signal.c \
	src/core/prompt.c \
	src/core/prompt_helpers.c \
	src/core/setup_redirections.c \
	src/core/signal_here.c

SRC_EXEC := \
	src/exec/child_exec.c \
	src/exec/exec_errors.c \
	src/exec/exec_helpers.c \
	src/exec/exec_parent_redir.c \
	src/exec/executor_pipe.c \
	src/exec/executor_single.c \
	src/exec/executor_stage.c \
	src/exec/executor.c \
	src/exec/redir.c \
	src/exec/resolve_entry.c \
	src/exec/resolve_path.c \
	src/exec/split_path.c

SRC_FD := \
	src/fd/fd_dup_close.c \
	src/fd/fd_open.c \
	src/fd/fd_pipe.c \
	src/fd/fd_pipes_array.c

SRC_BUILTIN := \
	src/builtin/builtin_cd.c \
	src/builtin/builtin_child.c \
	src/builtin/builtin_echo.c \
	src/builtin/builtin_env.c \
	src/builtin/builtin_exit.c \
	src/builtin/builtin_export.c \
	src/builtin/builtin_lookup.c \
	src/builtin/builtin_options.c \
	src/builtin/builtin_parent.c \
	src/builtin/builtin_pwd.c \
	src/builtin/builtin_unset.c \
	src/builtin/builtin_utils.c \

SRC_EXPAND := \
	src/expand/expand.c \
	src/expand/expand_word.c \
	src/expand/expand_redir.c

SRC_HEREDOC := \
	src/heredoc/heredoc.c \
	src/heredoc/heredoc_utils.c

SRCS := $(SRC_MAIN) $(SRC_ENV) $(SRC_LEXER) $(SRC_CORE) $(SRC_PARSER) $(SRC_EXEC) $(SRC_FD) $(SRC_BUILTIN) $(SRC_EXPAND) $(SRC_HEREDOC)
OBJS := $(SRCS:.c=.o)

# Default
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $@

# Compile rule
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Clean
clean:
	rm -f $(OBJS) $(BUILTIN_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) tests/env_smoke tests/exec_env_demo tests/env_all tests/builtin_smoke
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# ===== Tests =====

# env test binaries reuse core objects (main.o 제외)
ENV_TEST_OBJS := $(filter-out $(SRC_MAIN:.c=.o),$(OBJS))

tests/env_smoke: tests/env_smoke.c $(ENV_TEST_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -L$(LIBFT_DIR) -lft -o $@

tests/exec_env_demo: tests/exec_env_demo.c $(ENV_TEST_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -L$(LIBFT_DIR) -lft -o $@

tests/env_all: tests/env_all.c $(ENV_TEST_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -L$(LIBFT_DIR) -lft -o $@

# builtin_smoke test (optional, 존재하는 파일만)
BUILTIN_SRCS := $(wildcard src/builtin/builtin_*.c)
BUILTIN_OBJS := $(BUILTIN_SRCS:.c=.o)

ifneq ($(BUILTIN_OBJS),)
tests/builtin_smoke: tests/builtin_smoke.c $(ENV_TEST_OBJS) $(BUILTIN_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -L$(LIBFT_DIR) -lft -o $@
endif

# aggregate tests
TEST_TARGETS := tests/env_smoke tests/exec_env_demo tests/env_all
ifneq ($(BUILTIN_OBJS),)
TEST_TARGETS += tests/builtin_smoke
endif

tests: $(TEST_TARGETS)

.PHONY: all clean fclean re tests

