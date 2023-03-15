/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_non_bonus_defines.h                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/10 14:17:28 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/10 14:17:28 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_NON_BONUS_DEFINES_H
# define RT_NON_BONUS_DEFINES_H

// Float between 0 and infinity.
// Lights are spheres (to have soft shadows), which means they need a diameter.
// TODO: Set to 1.0f before eval
# define LIGHT_DIAMETER 1000.0f

// OBJECT MATERIALS ////////////////////////////////////////////////////////////

// Floats between 0 and 1.
// What percentage of the light that hits this object
// is going to be reflected specularly, instead of diffusely.
# define PLANE_SPECULAR_CHANCE 0.0f
# define SPHERE_SPECULAR_CHANCE 0.1f
# define CYLINDER_SPECULAR_CHANCE 0.0f
# define LIGHT_SPECULAR_CHANCE 0.0f

// Floats between 0 and 1.
// How rough the surface is, which controls how blurry the reflection is.
// A value of 0 is a very sharp clean mirror-like reflection,
// and a value of 1 is so blurry it looks just like diffuse.
# define PLANE_SPECULAR_ROUGHNESS 0.0f
# define SPHERE_SPECULAR_ROUGHNESS 0.1f
# define CYLINDER_SPECULAR_ROUGHNESS 0.0f
# define LIGHT_SPECULAR_ROUGHNESS 0.0f

// Floats between TODO: ?? and TODO: ??.
# define PLANE_INDEX_OF_REFRACTION 1.0f
# define SPHERE_INDEX_OF_REFRACTION 1.1f
# define CYLINDER_INDEX_OF_REFRACTION 1.0f
# define LIGHT_INDEX_OF_REFRACTION 1.0f

// Floats between 0 and 1.
# define PLANE_REFRACTION_CHANCE 0.0f
# define SPHERE_REFRACTION_CHANCE 0.5f
# define CYLINDER_REFRACTION_CHANCE 0.0f
# define LIGHT_REFRACTION_CHANCE 0.0f

// Floats between 0 and 1.
# define PLANE_REFRACTION_ROUGHNESS 0.0f
# define SPHERE_REFRACTION_ROUGHNESS 0.1f
# define CYLINDER_REFRACTION_ROUGHNESS 0.0f
# define LIGHT_REFRACTION_ROUGHNESS 0.0f

#endif
