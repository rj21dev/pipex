NAME		= pipex
SRCS_DIR	= srcs/
OBJS_DIR	= objs/
INCS_DIR	= includes
SRCS_F		= main.c
SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_F))
OBJS_F		= $(patsubst %.c, %.o, $(SRCS_F))
DEPS_F		= $(patsubst %.c, %.d, $(SRCS_F))
OBJS		= $(addprefix $(OBJS_DIR), $(OBJS_F))
DEPS		= $(addprefix $(OBJS_DIR), $(DEPS_F))

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -MMD
LFLAGS		= -Llibft -lft
LIB			= libft.a
LIB_DIR		= libft/

all: $(NAME)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
		$(CC) $(CFLAGS) -I$(INCS_DIR) -c $< -o $@

$(OBJS_DIR) :
		mkdir -p $@

$(NAME):  $(OBJS_DIR) $(OBJS) $(LIB_DIR)$(LIB) Makefile
		$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $@

$(LIB_DIR)$(LIB) : ;
		make -C $(LIB_DIR)

clean :
	rm -rf $(OBJS_DIR)
	make clean -C $(LIB_DIR)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(LIB_DIR)

re: fclean all

.PHONY:
		all clean fclean re

-include $(DEPS) $(DEPS_B)
