/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsenses <hsenses@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:03:33 by hsenses           #+#    #+#             */
/*   Updated: 2023/05/26 15:03:33 by hsenses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_strrncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	if (!s1 || !s2)
		return (0);
	i = ft_strlen(s1) - 1;
	j = ft_strlen(s2) - 1;
	while (--n && i && j && s1[i] == s2[j])
	{
		i--;
		j--;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}
