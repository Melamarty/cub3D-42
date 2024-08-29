#include "../parsing.h"

void ft_putstr(char *str, int fd)
{
    write(fd, str, ft_strlen (str));
}

int	ft_strncmp(char *str1, char *str2, int n)
{
	int i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i] && i < n)
		i++;
	if (i == ft_strlen(str2))
        return (0);
    return (1);
}


int	ft_strcmp(char *str1, char *str2)
{
	int i;

	i = 0;
	while ((str1[i] || str2[i]))
    {
        if ((unsigned char) str1[i] != (unsigned char) str2[i])
            return ((unsigned char) str1[i] - (unsigned char) str2[i]);
        i++;
    }
    return (0);
}
