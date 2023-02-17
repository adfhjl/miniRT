/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shuffle.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 18:20:13 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/16 18:20:13 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>

// Source: https://stackoverflow.com/a/11946674/13279557
static unsigned int	rt_rand(void)
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
		index = rt_rand() % length;
		length--;
		temp = arr[index];
		arr[index] = arr[length];
		arr[length] = temp;
	}
}
