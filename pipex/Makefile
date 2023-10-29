NAME_PROJECT = pipex
BONUS = pipexbonus

SRCS = src/pipex.c src/utils.c
SRCS_B = src_bonus/pipex_bonus.c src_bonus/utils_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)

FLAGS = -Wall -Wextra -Werror -Iinc/
LIBFT = libft/libft.a

all: $(NAME_PROJECT) $(BONUS)

.PHONY: all clean fclean re

$(NAME_PROJECT): $(OBJS)
	@make -C libft/
	@cc $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME_PROJECT)
	@echo  "$(CYAN)Build ($(NAME_PROJECT)): $(GREEN)[Success]$(RESET)"

bonus: $(OBJS_B)
	@make -C libft/
	@cc $(FLAGS) $(OBJS_B) $(LIBFT) -o $(BONUS)
	@echo  "$(CYAN)Build ($(BONUS)): $(GREEN)[Success]$(RESET)"
%.o: %.c
	@cc -c $< -o $@

clean:
	@rm -f $(OBJS) $(OBJS_B)
	@make fclean -C libft/
	@echo "$(YELLOW)Cleaned object files$(RESET)"

fclean: clean
	@rm -f $(NAME_PROJECT) $(BONUS)
	@echo  "$(YELLOW)Cleaned $(CYAN)$(NAME_PROJECT) & $(BONUS): $(RED)[Success]$(RESET)"

re: fclean all

GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
RED	= \033[1;31m
RESET = \033[0m