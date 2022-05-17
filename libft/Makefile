NAME	= libft.a

SRCS_F	= ft_atoi.c ft_atol.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
			ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
			ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_abs.c \
			ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_split_free.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_error.c get_next_line.c \
			ft_itoa.c ft_strjoin.c ft_substr.c ft_strmapi.c ft_strtrim.c ft_split.c ft_striteri.c \
			ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstprint.c \
			ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_ultoa.c ft_isspace.c ft_realloc.c
			
SRCS_DIR	= srcs/
OBJS_DIR	= objs/
OBJS_F		= $(patsubst %.c, %.o, $(SRCS_F))
DEPS_F		= $(patsubst %.c, %.d, $(SRCS_F))
SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_F))
OBJS		= $(addprefix $(OBJS_DIR), $(OBJS_F))
DEPS		= $(addprefix $(OBJS_DIR), $(DEPS_F))
CC			= gcc
FLAGS		= -Wall -Wextra -Werror -MMD
LINK		= ar -rcs
RM			= rm -f

all: $(OBJS_DIR) $(NAME)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c Makefile
		$(CC) $(FLAGS) -c $< -o $@

$(OBJS_DIR) :
		mkdir -p $@

$(NAME): $(OBJS) Makefile
		$(LINK) $(NAME) $(OBJS)

clean:
		$(RM)r $(OBJS_DIR)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY:
		all clean fclean re

-include $(DEPS)
