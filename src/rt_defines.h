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

# define WINDOW_WIDTH 300
# define WINDOW_HEIGHT 300

# define BACKGROUND_R 128
# define BACKGROUND_G 128
# define BACKGROUND_B 128

# define UNRENDERED_R 42
# define UNRENDERED_G 42
# define UNRENDERED_B 42

# define EPSILON 1e-4
# define LIGHT_BRIGHTNESS_FACTOR 100.f

# define MOVEMENT_SPEED 5.0f
# define MOVEMENT_SPEED_SCROLL_FACTOR 1.2f
# define MAX_MOVEMENT_SPEED 50.0f
# define MIN_MOVEMENT_SPEED 0.5f

# define ROTATION_SPEED 0.1f

# define RAYS_PER_FRAME 45000
# define GENERATED_NOISE_PER_FRAME 100

# define DEBUG_DRAWING_DEPTH 1
# define DEBUG_DRAWING_ON_BY_DEFAULT 1

// TODO: As an optimization, make this dynamically happen so that it happens
// frequently at the start and infrequently at the end.
# define NOISE_PER_UPDATE_RADIUS_RECALCULATION 10

#endif
