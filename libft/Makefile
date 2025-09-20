NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_LIBFT = ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint ft_strlen ft_memset ft_bzero ft_memcpy\
		ft_memmove ft_strlcpy ft_strlcat ft_toupper ft_tolower ft_strchr ft_strrchr ft_strncmp\
		ft_memchr ft_memcmp ft_strnstr ft_atoi ft_calloc ft_strdup ft_substr ft_strjoin ft_strtrim\
		ft_itoa ft_split ft_strmapi ft_striteri ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd\
		ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back ft_lstdelone\
        ft_lstclear ft_lstiter ft_lstmap ft_split_free ft_strndup

SRCS_LIBFT = $(addsuffix .c, $(SRC_LIBFT))
OBJS_LIBFT = $(SRCS_LIBFT:.c=.o)

SRC_PRINTF = ft_printf handle_format handle_char handle_string handle_pointer handle_int handle_unsigned\
			 handle_hex parse_format init_format normalize_flags utils_len utils_print
SRCS_PRINTF = $(addsuffix .c, $(SRC_PRINTF))
OBJS_PRINTF = $(SRCS_PRINTF:.c=.o)

SRC_GNL = get_next_line get_next_line_utils
SRCS_GNL = $(addsuffix .c, $(SRC_GNL))
OBJS_GNL = $(SRCS_GNL:.c=.o)

SRC_ADDITIONAL = ft_isspace ft_atol ft_atod ft_strcmp ft_isnum
SRCS_ADDITIONAL = $(addsuffix .c, $(SRC_ADDITIONAL))
OBJS_ADDITIONAL = $(SRCS_ADDITIONAL:.c=.o)

OBJS = $(OBJS_LIBFT) $(OBJS_GNL) $(OBJS_PRINTF) $(OBJS_ADDITIONAL)

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
