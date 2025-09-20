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
SRC_MAIN := src/main.c
SRC_ENV := \
	src/env/env_utils.c \
	src/env/env_list.c \
	src/env/env_from_environ.c \
	src/env/env_to_array.c

SRCS := $(SRC_MAIN) $(SRC_ENV)
OBJS := $(SRCS:.c=.o)

# Default
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -L$(LIBFT_DIR) -lft -o $@

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
tests/builtin_smoke: tests/builtin_smoke.c $(BUILTIN_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -L$(LIBFT_DIR) -lft -o $@
endif

# aggregate tests
TEST_TARGETS := tests/env_smoke tests/exec_env_demo tests/env_all
ifneq ($(BUILTIN_OBJS),)
TEST_TARGETS += tests/builtin_smoke
endif

tests: $(TEST_TARGETS)

.PHONY: all clean fclean re tests

