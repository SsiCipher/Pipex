/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbin_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:16:40 by marvin            #+#    #+#             */
/*   Updated: 2021/12/25 22:16:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putbin_fd(unsigned int n, int fd, int is_prefixed)
{
	char	*base;

	base = "01";
	if (is_prefixed)
		write(fd, "0b", 2);
	if (n >= 2)
		ft_putbin_fd(n / 2, fd, FALSE);
	write(fd, &base[n % 2], 1);
}
