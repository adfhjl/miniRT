# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: vbenneko <vbenneko@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/08/16 13:58:57 by vbenneko      #+#    #+#                  #
#    Updated: 2023/02/14 14:10:27 by vbenneko      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

################################################################################

NAME := miniRT
CC := gcc

# TODO: Remove extra flags before the eval
CFLAGS := -Wall -Werror -Wextra -Wpedantic -Wfatal-errors -Wconversion
CFLAGS += -Wno-overlength-strings # Needed to include MLX42's font.h
CFLAGS += -Wno-missing-braces # Needed for brace initializing t_vector

################################################################################

ifdef O3
CFLAGS += -Ofast
endif
ifdef DEBUG
CFLAGS += -g3
endif
ifdef SAN
CFLAGS += -fsanitize=address
endif

################################################################################

CFILES :=\
	src/collisions/cylinder.c\
	src/collisions/plane.c\
	src/collisions/sphere.c\
	src/debug/assert_normal.c\
	src/debug/draw_debug.c\
	src/draw/blue_noise.c\
	src/draw/draw.c\
	src/draw/put_pixel.c\
	src/draw/reset_canvas_info.c\
	src/draw/shoot_rays.c\
	src/draw/voronoi.c\
	src/init/parse/objects/check_separating_whitespace.c\
	src/init/parse/objects/parse_ambient.c\
	src/init/parse/objects/parse_camera.c\
	src/init/parse/objects/parse_cylinder_basics.c\
	src/init/parse/objects/parse_light_basics.c\
	src/init/parse/objects/parse_plane_basics.c\
	src/init/parse/objects/parse_sphere_basics.c\
	src/init/parse/parse_argv.c\
	src/init/parse/parse_float.c\
	src/init/parse/parse_normal.c\
	src/init/parse/parse_object.c\
	src/init/parse/parse_range_float.c\
	src/init/parse/parse_rgb.c\
	src/init/parse/parse_vector.c\
	src/init/parse/skip_separator_comma.c\
	src/init/parse/skip_whitespace.c\
	src/init/init.c\
	src/input_hooks/input_hooks.c\
	src/rays/get_ray_point.c\
	src/rays/get_ray_rgb.c\
	src/rgb/aces_film.c\
	src/rgb/add.c\
	src/rgb/clamp.c\
	src/rgb/color_conversion.c\
	src/rgb/divide.c\
	src/rgb/exp_rgb.c\
	src/rgb/multiply.c\
	src/utils/get_ray.c\
	src/utils/lerp.c\
	src/utils/max.c\
	src/utils/mix.c\
	src/utils/print_error.c\
	src/utils/random.c\
	src/utils/solve_quadratic.c\
	src/vectors/add.c\
	src/vectors/cross.c\
	src/vectors/dot.c\
	src/vectors/mag.c\
	src/vectors/normalized.c\
	src/vectors/reflect.c\
	src/vectors/refract.c\
	src/vectors/rotate_around_axis.c\
	src/vectors/scale.c\
	src/vectors/sub.c\
	src/main.c

ifdef BONUS
CFILES +=\
	src/collisions/get_line_rgb_bonus.c\
	src/debug/print_scene_bonus.c\
	src/init/parse/objects/parse_cylinder_bonus.c\
	src/init/parse/objects/parse_light_bonus.c\
	src/init/parse/objects/parse_material_bonus.c\
	src/init/parse/objects/parse_plane_bonus.c\
	src/init/parse/objects/parse_sphere_bonus.c\
	src/init/parse/check_capitalized_object_counts_bonus.c
else
CFILES +=\
	src/collisions/get_line_rgb.c\
	src/debug/print_scene.c\
	src/init/parse/objects/parse_cylinder.c\
	src/init/parse/objects/parse_light.c\
	src/init/parse/objects/parse_plane.c\
	src/init/parse/objects/parse_sphere.c\
	src/init/parse/check_capitalized_object_counts.c
endif

################################################################################

INCLUDES := -I src -I libft -I . -I MLX42/include
OBJDIR := obj
OBJFILES := $(addprefix $(OBJDIR)/,$(CFILES:c=o))
LIBFT_PATH := libft/libft.a
MLX_PATH := MLX42/build/libmlx42.a
LIB_FLAGS := -L $(dir $(LIBFT_PATH)) -l ft -L $(dir $(MLX_PATH)) -l mlx42 -l glfw3 -framework Cocoa -framework OpenGL -framework IOKit

################################################################################

.PHONY: all
all: $(NAME)

################################################################################

$(NAME): $(MLX_PATH) $(LIBFT_PATH) $(OBJFILES)
	@$(CC) $(CFLAGS) $(OBJFILES) $(LIB_FLAGS) -o $(NAME)
	@printf "Compiled %s\n" "$(NAME)"

################################################################################

$(MLX_PATH):
	@git submodule update --init --recursive
	@cmake -S $(dir $(MLX_PATH))/.. -B $(dir $(MLX_PATH))
	@cmake --build $(dir $(MLX_PATH)) -j

$(LIBFT_PATH):
	@git submodule update --init --recursive
	@$(MAKE) -C $(dir $(LIBFT_PATH)) -j

################################################################################

# Source and explanation: https://stackoverflow.com/a/52036564/13279557

DEPENDS := $(patsubst %.o,%.d,$(OBJFILES))

-include $(DEPENDS)

$(OBJDIR)/%.o : %.c $(MLX_PATH) $(LIBFT_PATH) Makefile
	@mkdir -p $(@D)
	@$(call tidy_compilation,$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@)

define tidy_compilation
	@printf "%s\e[K\n" "$(1)"
	@$(1)
	@printf "\e[A\e[K"
endef

################################################################################

.PHONY: clean
clean:
	@$(MAKE) -C $(dir $(LIBFT_PATH)) fclean
	@if [ -d $(dir $(MLX_PATH)) ]; then cmake --build $(dir $(MLX_PATH)) --target clean; fi
	@$(RM) -rf $(OBJDIR)
	@printf "Cleaned %s\n" "$(NAME)"

.PHONY: fclean
fclean: clean
	@$(RM) -f $(NAME)
	@printf "Deleted %s\n" "$(NAME)"

.PHONY: re
re: fclean all

.PHONY: bonus
bonus:
	@$(MAKE) all BONUS=1

################################################################################
