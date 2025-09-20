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
	rm -f $(OBJS) \
		src/builtin/builtin_lookup.o \
		src/builtin/builtin_child_impl.o \
		src/builtin/builtin_parent_impl.o
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) \
		tests/env_smoke \
		tests/exec_env_demo \
		tests/env_all \
		tests/builtin_smoke
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# ===== Tests =====

# env test binaries reuse core objects
ENV_TEST_OBJS := $(OBJS)

tests/env_smoke: tests/env_smoke.c $(ENV_TEST_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -L$(LIBFT_DIR) -lft -o $@

tests/exec_env_demo: tests/exec_env_demo.c $(ENV_TEST_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -L$(LIBFT_DIR) -lft -o $@

tests/env_all: tests/env_all.c $(ENV_TEST_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -L$(LIBFT_DIR) -lft -o $@

# builtin_smoke test (adds builtin objs)
BUILTIN_SRCS := \
	src/builtin/builtin_lookup.c \
	src/builtin/builtin_child_impl.c \
	src/builtin/builtin_parent_impl.c
BUILTIN_OBJS := $(BUILTIN_SRCS:.c=.o)

tests/builtin_smoke: tests/builtin_smoke.c $(BUILTIN_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -L$(LIBFT_DIR) -lft -o $@

tests: tests/env_smoke tests/exec_env_demo tests/env_all tests/builtin_smoke

.PHONY: all clean fclean re tests

