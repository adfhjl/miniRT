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

// Float from 0 to infinity.
// A really small value used to nudge the ray up to make sure floating-point
// shenanigans didn't cause the ray to accidentally end up on the wrong side.
# define SURFACE_NORMAL_NUDGE 0.01f

// Integer between 1 and infinity.
// How many rays are shot per frame.
// Turn this down if your FPS is low, and turn it up if you reach 60 FPS.
# define RAYS_PER_FRAME 20000

// # define GENERATED_NOISE_PER_FRAME 100

# define DEBUG_DRAWING_DEPTH 1

# define DEBUG_DRAW_ON_BY_DEFAULT 1
# define DEFAULT_DRAW_MODE DRAW_MODE_NORMAL

# define PIXEL_SCALE 2

// # define MAX_UPDATE_RADIUS 20

// TODO: As an optimization, make this dynamically happen so that it happens
// frequently at the start and infrequently at the end.
// # define NOISE_PER_UPDATE_RADIUS_RECALCULATION 10

// TODO: Set this to 0 before the eval, since only diffuse lighting is allowed.
// TODO: It can still be diffuse with a value higher than 0
// if "REFLECTION_NOISINESS" is added to add some randomness to the reflection.
# define MAX_BOUNCES_PER_RAY 8

// 0.0 means that reflection doesn't occur, so the render is diffuse.
// 0.9 means that reflected rays recursively contribute 90% of the RGB,
// so that the object's own RGB only contributes 10% of the RGB.
// # define REFLECTION_CONTRIBUTION 0.5f

// TODO: Set to 1.0f before eval
# define LIGHT_DIAMETER 1000.0f

// TODO: Add three defines for plane, sphere, and cylinder emission RGBs

// TODO: Set to 0 before eval
# define MULTIPLE_LIGHTS_ALLOWED 1

// Float between 0 and infinity.
// A value of 0 means no anti-aliasing occurs.
// A value of 1 means that the first ray shot from the camera into the scene
// can be randomly moved up to one pixel up/down/left/right.
# define ANTI_ALIAS_RADIUS 0.5f

// Float between 0 and infinity.
// The higher this number, the brighter the scene.
# define EXPOSURE 0.5f

# define X_LINE_FREQUENCY 2.0f
# define Y_LINE_FREQUENCY 0.0f
# define Z_LINE_FREQUENCY 0.0f
# define DRAW_LINES 1

// MOVEMENT ////////////////////////////////////////////////////////////////////

# define MOVEMENT_SPEED 7.0f
# define MOVEMENT_SPEED_SCROLL 1.2f
# define MAX_MOVEMENT_SPEED 50.0f
# define MIN_MOVEMENT_SPEED 0.5f
# define ROTATION_SPEED 0.003f

// OBJECT MATERIALS ////////////////////////////////////////////////////////////

// Floats between 0 and infinity.
// A value of 0 means the object type isn't emissive.
// A value of 10 means the object emits 10x its RGB value.
# define PLANE_EMISSIVE_FACTOR 0.0f
# define SPHERE_EMISSIVE_FACTOR 0.0f
# define CYLINDER_EMISSIVE_FACTOR 0.0f
# define LIGHT_EMISSIVE_FACTOR 20.0f

// Floats between 0 and 1.
// What percentage of the light that hits this object
// is going to be reflected specularly, instead of diffusely.
# define PLANE_SPECULAR_CHANCE 0.0f
# define SPHERE_SPECULAR_CHANCE 0.02f
# define CYLINDER_SPECULAR_CHANCE 0.0f

// Floats between 0 and 1.
// How rough the surface is, which controls how blurry the reflection is.
// A value of 0 is a very sharp clean mirror-like reflection,
// and a value of 1 is so blurry it looks just like diffuse.
# define PLANE_SPECULAR_ROUGHNESS 0.0f
# define SPHERE_SPECULAR_ROUGHNESS 0.01f
# define CYLINDER_SPECULAR_ROUGHNESS 0.0f

// Floats between 0 and 1.
# define PLANE_INDEX_OF_REFRACTION 0.0f
# define SPHERE_INDEX_OF_REFRACTION 1.1f
# define CYLINDER_INDEX_OF_REFRACTION 0.0f

// Floats between 0 and 1.
# define PLANE_REFRACTION_CHANCE 0.0f
# define SPHERE_REFRACTION_CHANCE 0.9f
# define CYLINDER_REFRACTION_CHANCE 0.0f

// Floats between 0 and 1.
# define PLANE_REFRACTION_ROUGHNESS 0.0f
# define SPHERE_REFRACTION_ROUGHNESS 0.1f
# define CYLINDER_REFRACTION_ROUGHNESS 0.0f

// RGB /////////////////////////////////////////////////////////////////////////
// Floats between 0 and 1.

# define BACKGROUND_R 0.4f
# define BACKGROUND_G 0.5f
# define BACKGROUND_B 0.7f

# define UNRENDERED_R 0.05f
# define UNRENDERED_G 0.05f
# define UNRENDERED_B 0.05f

# define LIGHT_R 0.0f
# define LIGHT_G 0.0f
# define LIGHT_B 0.0f

#endif
