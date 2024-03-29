/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsenses <hsenses@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:03:01 by hsenses           #+#    #+#             */
/*   Updated: 2023/05/26 15:03:02 by hsenses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	int	i;

	i = 0;
	if (nb * nb <= 2147483647)
	{
		while (i * i < nb)
		{
			i++;
			if (i * i > nb)
				return (i - 1);
		}
	}
	return (i);
}
