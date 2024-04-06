NAME				=	philo

FILES				=	test.c \
						utils.c \
						parsing.c \
						init.c \

SRC_DIR				=	src
SRC					=	$(addprefix $(SRC_DIR)/, $(SRC))

OBJ_DIR				=	obj
OBJ					=	$(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror
INCLUDES			=	-I includes
DEBUGGER			=	-g3



all					:	$(NAME)


$(NAME)				:	$(OBJ_DIR) $(OBJ)
						@echo "\n"
						@echo "$(GREEN)Compiling philo...$(COLOR_END)"
						$(CC) $(CFLAGS) $(INCLUDES) $(DEBUGGER) $(OBJ) -o $(NAME)
						@echo "$(LGREEN)philo compiled !$(RED) Let them die. $(COLOR_END)\n"

$(OBJ_DIR)			:
						mkdir -p $@

$(OBJ_DIR)/%.o		:	$(SRC_DIR)/%.c
						$(CC) $(CFLAGS) $(INCLUDES) $(DEBUGGER) -c $< -o $@
						@printf "$(YELLOW)%s created $(FACE_ESCUZME) $(COLOR_END)\n" $@

clean				:
						rm -rf $(OBJ_DIR)

fclean				:	clean
						rm -rf $(NAME)

re					:	fclean all

.PHONY				:	all clean fclean re

LGREEN				=	\033[1;32m
GREEN				=	\033[32m

LBLUE				=	\033[1;34m
BLUE				=	\033[34m

RED					=	\033[31m

LYELLOW				=	\033[1;33m
YELLOW				=	\033[33m

COLOR_END			=	\033[0m

FACE_ESCUZME		=	🤓
BYE					=	🙋