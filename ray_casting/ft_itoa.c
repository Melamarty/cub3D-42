/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:29:20 by houamrha          #+#    #+#             */
/*   Updated: 2024/09/16 14:13:40 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	int_len(int n)
{
	int	i;
	int	nb;

	i = 0;
	if (n < 0)
		nb = -n;
	else
		nb = n;
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	if (n < 0)
		i += 1;
	return (i);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				j;
	int				i;

	if (n == 0)
		return (ft_strdup("0"));
	i = int_len(n);
	j = i;
	str = my_malloc((i + 1) * sizeof(char), 0);
	if (!str)
		return (0);
	if (n < 0)
		str[0] = '-';
	if (n < 0)
		n = -n;
	while (n > 0)
	{
		str[i - 1] = (n % 10) + 48;
		n /= 10;
		i--;
	}
	str[j] = '\0';
	return (str);
}
