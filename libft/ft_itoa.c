/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:11:27 by yanab             #+#    #+#             */
/*   Updated: 2021/11/16 00:08:17 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	int	len;

	len = 0;
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static char	*convert_int(int n, int padding)
{
	int		i;
	int		n_length;
	char	*nstr;

	n_length = ft_numlen(n);
	i = n_length - 1;
	nstr = (char *)malloc(sizeof(char) * (n_length + 1 + padding));
	if (!nstr)
		return (NULL);
	if (padding == 1)
		nstr[0] = '-';
	while (n > 0)
	{
		nstr[i + padding] = n % 10 + '0';
		i--;
		n /= 10;
	}
	nstr[n_length + padding] = '\0';
	return (nstr);
}

char	*ft_itoa(int n)
{
	char	*nstr;

	if (n == 0)
		return (ft_strdup("0"));
	else if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n < 0)
		nstr = convert_int(-n, 1);
	else
		nstr = convert_int(n, 0);
	return (nstr);
}
