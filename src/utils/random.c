/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   random.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 18:20:13 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/16 18:20:13 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>

// Returns a random unsigned int from 0 up to and including INT32_MAX.
// Source: https://stackoverflow.com/a/11946674/13279557
static unsigned int	rt_random(void)
{
	static unsigned int	seed = 1;

	seed = (seed * 1103515245U + 12345U) & 0x7fffffffU;
	return (seed);
}

void	rt_shuffle(uint32_t *arr, size_t length)
{
	uint32_t	index;
	uint32_t	temp;

	while (length > 1)
	{
		index = rt_random() % length;
		length--;
		temp = arr[index];
		arr[index] = arr[length];
		arr[length] = temp;
	}
}

float	rt_random_float_01(void)
{
	return ((float)rt_random() / INT32_MAX);
}
