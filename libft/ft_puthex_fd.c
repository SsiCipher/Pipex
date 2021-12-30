/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:15:27 by marvin            #+#    #+#             */
/*   Updated: 2021/12/25 22:15:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puthex_fd(unsigned int n, int fd, int is_prefixed)
{
	char	*base;

	base = "0123456789ABCDEF";
	if (is_prefixed)
		write(fd, "0x", 2);
	if (n >= 16)
		ft_puthex_fd(n / 16, fd, FALSE);
	write(fd, &base[n % 16], 1);
}
