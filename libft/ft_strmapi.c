/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:14:26 by yanab             #+#    #+#             */
/*   Updated: 2021/11/14 14:14:26 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		str_len;
	char	*mapped_str;

	if (s == NULL)
		return (NULL);
	str_len = ft_strlen(s);
	mapped_str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (!mapped_str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		mapped_str[i] = f(i, s[i]);
		i++;
	}
	mapped_str[i] = '\0';
	return (mapped_str);
}
