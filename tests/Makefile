CC      := cc
CFLAGS  := -Wall -Wextra -Werror -I../include -I../libft
LIBFT_DIR := ../libft
LIBFT   := $(LIBFT_DIR)/libft.a

BUILTIN_SRCS := \
  ../src/builtin/builtin_lookup.c \
  ../src/builtin/builtin_child.c \
  ../src/builtin/builtin_parent.c \
  ../src/builtin/builtin_echo.c \
  ../src/builtin/builtin_pwd.c \
  ../src/builtin/builtin_env.c

TEST_SRCS := builtin_smoke.c

SRCS := $(BUILTIN_SRCS) $(TEST_SRCS)
OBJS := $(SRCS:.c=.o)

TARGET := builtin_smoke

all: $(TARGET)

$(TARGET): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re

