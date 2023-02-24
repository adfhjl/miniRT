/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_defines.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/17 15:05:55 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/23 18:01:36 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_DEFINES_H
# define RT_DEFINES_H

# define WINDOW_TITLE "miniRT"
# define SYSTEM_ERROR_STATUS -1

# define UNSCALED_WINDOW_WIDTH 500
# define UNSCALED_WINDOW_HEIGHT 500

# define BACKGROUND_R 0
# define BACKGROUND_G 0
# define BACKGROUND_B 0
// # define BACKGROUND_R 20
// # define BACKGROUND_G 20
// # define BACKGROUND_B 20

# define UNRENDERED_R 10
# define UNRENDERED_G 10
# define UNRENDERED_B 10

# define EPSILON 1.0e-4f
# define LIGHT_BRIGHTNESS_FACTOR 500.0f

# define MOVEMENT_SPEED 7.0f
# define MOVEMENT_SPEED_SCROLL_FACTOR 1.2f
# define MAX_MOVEMENT_SPEED 50.0f
# define MIN_MOVEMENT_SPEED 0.5f

# define ROTATION_SPEED 0.003f

# define RAYS_PER_FRAME 45000
# define GENERATED_NOISE_PER_FRAME 100

# define DEBUG_DRAWING_DEPTH 1

# define DEBUG_DRAW_ON_BY_DEFAULT 1
# define DEFAULT_DRAW_MODE DRAW_MODE_NORMAL

# define PIXEL_SCALE 2

# define MAX_UPDATE_RADIUS 10

// TODO: As an optimization, make this dynamically happen so that it happens
// frequently at the start and infrequently at the end.
# define NOISE_PER_UPDATE_RADIUS_RECALCULATION 10

// TODO: Set this to 0 before the eval, since only diffuse lighting is allowed.
// TODO: It can still be diffuse with a value higher than 0
// if "REFLECTION_NOISINESS" is added to add some randomness to the reflection.
# define MAX_BOUNCES_PER_RAY 10

// 0.0 means that reflection doesn't occur, so the render is diffuse.
// 0.9 means that reflected rays recursively contribute 90% of the RGB,
// so that the object's own RGB only contributes 10% of the RGB.
# define REFLECTION_RATIO 0.5f

#endif
