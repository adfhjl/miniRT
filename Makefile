# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: vbenneko <vbenneko@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/08/16 13:58:57 by vbenneko      #+#    #+#                  #
#    Updated: 2023/01/16 17:29:17 by vbenneko      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = gcc
NORMFLAGS = -Wall -Werror -Wextra
CFILES =						\
	src/main.c
HEADERS = minirt.h libft/libft.h

INCLUDES = $(addprefix -I, $(sort $(dir $(HEADERS)))) -I MLX42/include
OBJDIR = obj
OBJFILES = $(addprefix $(OBJDIR)/,$(CFILES:c=o))
GLFW_LIB_DIR = $(BREW_DIR)/opt/glfw/lib
LIBFT_PATH = libft/libft.a
MLX_PATH = MLX42/libmlx42.a
BREW_DIR = $(shell brew --prefix)
LIB_FLAGS = -L $(dir $(LIBFT_PATH)) -l ft -L $(dir $(MLX_PATH)) -l mlx42 -L $(GLFW_LIB_DIR) -l glfw

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
	@$(call fastprint_compilation,$(CC) $(NORMFLAGS) $(INCLUDES) -c $< -o $@)

clean:
	@$(MAKE) -C $(dir $(LIBFT_PATH)) fclean
	@$(MAKE) -C $(dir $(MLX_PATH)) fclean
	@rm -rf $(OBJDIR)
	@printf "Cleaned %s\n" "$(NAME)"

fclean: clean
	@rm -f $(NAME)
	@printf "Deleted %s\n" "$(NAME)"

re: fclean all

define fastprint_compilation
	@printf "%s\e[K\n" "$(1)"
	@$(1)
	@printf "\e[A\e[K"
endef

.PHONY: all clean fclean re
