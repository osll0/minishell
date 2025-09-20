# 프로젝트 이름
NAME = minishell

# 컴파일러 & 옵션
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# 라이브러리
LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

# 인클루드 경로
INCLUDES = -Iinclude -I$(LIBFT_DIR)

SRC_MAIN = src/main.c

# 소스 목록 (현재 디렉토리 트리에 맞춤)
SRC_ENV = \
	src/env/env_utils.c \
	src/env/env_list.c \
	src/env/env_from_environ.c \
	src/env/env_to_array.c

SRCS = $(SRC_ENV) $(SRC_ENV)
OBJS = $(SRCS:.c=.o)

# 공통 .c -> .o 규칙 (헤더 경로 포함)
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 기본 빌드
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

# libft 빌드
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# 테스트용 실행파일
tests/env_smoke: tests/env_smoke.c $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -L$(LIBFT_DIR) -lft -o $@

tests/exec_env_demo: tests/exec_env_demo.c $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -L$(LIBFT_DIR) -lft -o $@

tests/env_all: tests/env_all.c $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -L$(LIBFT_DIR) -lft -o $@

tests: tests/env_smoke tests/exec_env_demo tests/env_all

.PHONY: all clean fclean re tests

