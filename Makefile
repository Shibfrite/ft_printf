CC := gcc
CFLAGS := -Wall -Wextra -Werror

NAME := libftprintf.a

PRINTF_DIR := ft_printf/
HEAD := $(PRINTF_DIR)/ft_printf.h
SRCS := ft_printf.c process_number.c process_string.c handle_format.c ft_padding.c ft_padding_supp.c

SRCS := $(addprefix $(PRINTF_DIR), $(SRCS))
OBJS := $(SRCS:.c=.o)


LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

RM := rm -f
AR := ar -rc

all: $(NAME)
	@echo "ft_printf: compiled all"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c $(HEAD)
	@$(CC) $(CFLAGS) -I$(PRINTF_DIR) -I$(LIBFT_DIR) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	@cp $(LIBFT) $(NAME)
	@$(AR) $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "ft_printf: compiled library"

bonus: $(NAME)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@echo "ft_printf: removed bonus objects"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@echo "ft_printf: removed all"

shit:	all clean

re: fclean all

.PHONY: all clean fclean shit re bonus
