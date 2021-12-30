/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 12:17:41 by marvin            #+#    #+#             */
/*   Updated: 2021/12/19 12:17:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_swap(int *arr, int from, int to)
{
	int	tmp;

	tmp = arr[to];
	arr[to] = arr[from];
	arr[from] = tmp;
}

void	ft_bsort(int len, int *arr)
{
	int	i;
	int	j;

	i = 0;
	while (i < len)
	{
		j = i;
		while (i < j)
		{
			if (arr[i] > arr[j])
				ft_swap(arr, j, i);
		}
	}
}
