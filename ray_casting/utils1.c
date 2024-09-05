#include "../parsing/parsing.h"

t_ray *last_ray(t_ray *rays)
{
	while (rays->next)
		rays = rays->next;
	return (rays);
}

void	add_back_ray(t_ray **rays, t_ray *new_ray)
{
	if (!*rays)
		*rays = new_ray;
	else
		last_ray(*rays)->next = new_ray;
}

unsigned int create_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    return (r << 24) | (g << 16) | (b << 8) | a;
}

double normAngle(double angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
	{
        angle += (2 * M_PI);
    }
    return (angle);
}
