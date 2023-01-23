# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: vbenneko <vbenneko@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/08/16 13:58:57 by vbenneko      #+#    #+#                  #
#    Updated: 2023/01/19 16:09:46 by vbenneko      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = gcc

# TODO: Remove extra flags before the eval
NORMFLAGS = -Wall -Werror -Wextra -Wpedantic -Wfatal-errors -Wconversion

ifdef DEBUG
NORMFLAGS += -g3
endif
ifdef SAN
NORMFLAGS += -fsanitize=address
endif

CFILES =\
	src/utils/print_error.c\
	src/main.c

HEADERS =\
	src/utils/rt_utils.h\
	src/minirt.h

INCLUDES = -I src -I libft -I MLX42/include
OBJDIR = obj
OBJFILES = $(addprefix $(OBJDIR)/,$(CFILES:c=o))
LIBFT_PATH = libft/libft.a
MLX_PATH = MLX42/libmlx42.a
BREW_DIR = $(shell brew --prefix)
LIB_FLAGS = -L $(dir $(LIBFT_PATH)) -l ft -L $(dir $(MLX_PATH)) -l mlx42 -l glfw3 -framework Cocoa -framework OpenGL -framework IOKit

all: $(NAME)

$(NAME): $(MLX_PATH) $(LIBFT_PATH) $(OBJFILES)
	@$(CC) $(NORMFLAGS) $(OBJFILES) $(LIB_FLAGS) -o $(NAME)
	@printf "Compiled %s\n" "$(NAME)"

$(MLX_PATH):
	@git submodule update --init --recursive
	@$(MAKE) -C $(dir $(MLX_PATH))

$(LIBFT_PATH):
	@git submodule update --init --recursive
	@$(MAKE) -C $(dir $(LIBFT_PATH))

$(OBJDIR)/%.o : %.c $(HEADERS) $(MLX_PATH) $(LIBFT_PATH)
	@mkdir -p $(@D)
	@$(call tidy_compilation,$(CC) $(NORMFLAGS) $(INCLUDES) -c $< -o $@)

clean:
	@$(MAKE) -C $(dir $(LIBFT_PATH)) fclean
	@$(MAKE) -C $(dir $(MLX_PATH)) fclean
	@rm -rf $(OBJDIR)
	@printf "Cleaned %s\n" "$(NAME)"

fclean: clean
	@rm -f $(NAME)
	@printf "Deleted %s\n" "$(NAME)"

re: fclean all

define tidy_compilation
	@printf "%s\e[K\n" "$(1)"
	@$(1)
	@printf "\e[A\e[K"
endef

.PHONY: all clean fclean re
