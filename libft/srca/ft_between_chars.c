/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_between_chars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsenses <hsenses@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:58:17 by hsenses           #+#    #+#             */
/*   Updated: 2023/05/26 14:58:18 by hsenses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_between_chars(char *s, char *set, char char1, char char2)
{
	int	match;
	int	i;

	match = 0;
	i = 0;
	while (s[i])
	{
		match = (match + ((!match && s[i] == char1) || \
			(match && s[i] == char2))) % 2;
		if (match && ft_strchr(set, s[i]))
			return (1);
		i++;
	}
	return (0);
}
