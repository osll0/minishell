CC      := cc
CFLAGS  := -Wall -Wextra -Werror -I../include -I../libft
LIBFT   := ../libft.a

BUILTIN_SRCS := \
  ../src/builtin/builtin_lookup.c \
  ../src/builtin/builtin_child_impl.c \
  ../src/builtin/builtin_parent_impl.c

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
	$(MAKE) -C ..

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re

