/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_dis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:29:08 by houamrha          #+#    #+#             */
/*   Updated: 2024/09/17 20:43:06 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	calc_h_dis(t_map map, t_ray ray)
{
	double	dx;
	double	dy;
	double	dis;

	if (!ray.found_x_inter)
		return (INT_MAX);
	dx = fabs(ray.h_x_inter - map.player->pos.x);
	dy = fabs(ray.h_y_inter - map.player->pos.y);
	dis = sqrt(dx * dx + dy * dy);
	return (dis);
}

double	calc_v_dis(t_map map, t_ray ray)
{
	double	dx;
	double	dy;
	double	dis;

	if (!ray.found_y_inter)
		return (INT_MAX);
	dx = fabs(ray.v_x_inter - map.player->pos.x);
	dy = fabs(ray.v_y_inter - map.player->pos.y);
	dis = sqrt(dx * dx + dy * dy);
	return (dis);
}
