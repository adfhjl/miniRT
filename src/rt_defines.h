/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_defines.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/17 15:05:55 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/17 15:05:55 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_DEFINES_H
# define RT_DEFINES_H

# define WINDOW_TITLE "miniRT"
# define SYSTEM_ERROR_STATUS -1

# define UNSCALED_WINDOW_WIDTH 500
# define UNSCALED_WINDOW_HEIGHT 500

# define BACKGROUND_R 128
# define BACKGROUND_G 128
# define BACKGROUND_B 128

# define UNRENDERED_R 42
# define UNRENDERED_G 42
# define UNRENDERED_B 42

# define EPSILON 1.0e-4f
# define LIGHT_BRIGHTNESS_FACTOR 100.0f

# define MOVEMENT_SPEED 7.0f
# define MOVEMENT_SPEED_SCROLL_FACTOR 1.2f
# define MAX_MOVEMENT_SPEED 50.0f
# define MIN_MOVEMENT_SPEED 0.5f

# define ROTATION_SPEED 0.003f

# define RAYS_PER_FRAME 450000000
# define GENERATED_NOISE_PER_FRAME 100

# define DEBUG_DRAWING_DEPTH 1

# define DEBUG_DRAW_ON_BY_DEFAULT 1
# define DEFAULT_DRAW_MODE DRAW_MODE_VORONOI

// TODO: Try using
// # define SMALLEST_UPDATE_RADIUS_TO_USE_VORONOI 3

# define PIXEL_SCALE 1

// TODO: As an optimization, make this dynamically happen so that it happens
// frequently at the start and infrequently at the end.
# define NOISE_PER_UPDATE_RADIUS_RECALCULATION 10

#endif
