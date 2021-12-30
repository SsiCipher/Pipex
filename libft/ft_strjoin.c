/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:13:58 by yanab             #+#    #+#             */
/*   Updated: 2021/11/14 14:13:58 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		s1_len;
	int		s2_len;
	char	*joined_str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	joined_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!joined_str)
		return (NULL);
	i = -1;
	while (s1[++i])
		joined_str[i] = s1[i];
	i = -1;
	while (s2[++i])
		joined_str[s1_len + i] = s2[i];
	joined_str[s1_len + i] = '\0';
	return (joined_str);
}
