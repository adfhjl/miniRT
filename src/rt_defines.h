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

// Integer from 1 to infinity.
// This is the resolution of the scene that actually gets rendered.
// If UNSCALED_WINDOW_WIDTH is 100 and the PIXEL_SCALE is 5, then the MLX
// window will be 500 pixels wide.
# define UNSCALED_WINDOW_WIDTH 640
# define UNSCALED_WINDOW_HEIGHT 360
# define PIXEL_SCALE 2

// Float from 0 to infinity.
// A really small value used to nudge the ray up to make sure floating-point
// shenanigans didn't cause the ray to accidentally end up on the wrong side.
# define SURFACE_NORMAL_NUDGE 0.01f

// Integer between 1 and infinity.
// How many rays are shot per frame.
// Turn this down if your FPS is low, and turn it up if you reach 60 FPS.
# define RAYS_PER_FRAME 30000

# define DEBUG_DRAWING_MLX_DEPTH 1

# define DEBUG_DRAW_ON_BY_DEFAULT 0

# define DEFAULT_DRAW_MODE DRAW_MODE_NOISE

// # define MAX_UPDATE_RADIUS 20

# define MAX_BOUNCES_PER_RAY 8

// Float between 0 and infinity.
// A value of 0 means no anti-aliasing occurs.
// A value of 1 means that the first ray shot from the camera into the scene
// can be randomly moved up to one pixel up/down/left/right.
# define ANTI_ALIAS_RADIUS 0.5f

// Float between 0 and infinity.
// The higher this number, the brighter the scene.
# define EXPOSURE 0.5f

// Float between 0 and infinity.
// This define exists to make lamps brighter than the rt scene format allows.
# define LIGHT_EMISSIVE_FACTOR 20.0f

// MOVEMENT ////////////////////////////////////////////////////////////////////

# define MOVEMENT_SPEED 5.0f
# define ROTATION_SPEED 0.002f

// # define MOVEMENT_SPEED 15.0f
// # define ROTATION_SPEED 0.004f

// RGB /////////////////////////////////////////////////////////////////////////
// Floats between 0 and 1.

# define BACKGROUND_R 0.4f
# define BACKGROUND_G 0.5f
# define BACKGROUND_B 0.7f

# define UNRENDERED_R 0.05f
# define UNRENDERED_G 0.05f
# define UNRENDERED_B 0.05f

#endif
