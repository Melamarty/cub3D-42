/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:33:57 by mel-amar          #+#    #+#             */
/*   Updated: 2024/09/15 19:39:59 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	set_checked(t_list *list)
{
	list->checked = 1;
	return (1);
}

char	*get_texture(char *line)
{
	char	**spl;

	spl = ft_split(line, ' ');
	if (!spl)
	{
		ft_putstr("external error", 2);
		exit (1);
	}
	return (spl[1]);
}

int	spl_len(char **spl)
{
	int	i;

	i = -1;
	while (spl[++i])
		;
	return (i);
}

int	is_digits(char *str)
{
	int	i;

	i = 0;
	if (empty_line(str))
		return (0);
	while (str[++i])
		if ((str[i] > '9' || str[i] < '0') && (str[i] != ' '))
			return (0);
	return (1);
}
