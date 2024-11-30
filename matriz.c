#include "fdf.h"
#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int	count_x(char	*str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			count++;
		while (str[i] != ' ' && str[i] != '\0')
			i++;
		if (str[i] != '\0')
			i++;
	}
	return (count);
}

int	count_y(int	fd)
{
	char	*line;
	int	i;
	
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{	
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (i);
}

void	free_matriz(t_matriz	*ptr)
{
	int	i;

	i = -1;
	if (ptr == NULL)
		return ;
	if (ptr->mapa)
	{
		while (++i < ptr->y)
		{
			if (ptr->mapa[i] != NULL)
				free(ptr->mapa[i]);
		}
		free(ptr->mapa);
	}
	free(ptr);
}

int	*mapa_line(char	*line, int x)
{
	char	**num;
	int	*linem;
	int	i;
	
	i = 0;
	num = ft_split(line, ' ');
	if (num == NULL)
	    return (NULL);
	linem = malloc(sizeof(int) * x);
	if (linem == NULL)
	    return (NULL);
	while  (num[i] != NULL)
	{
		linem[i] = ft_atoi(num[i]);
		free(num[i]);
		i++;
	}
	free(num);
	return (linem);
}

void	creat_matriz(t_matriz *ptr, int fd)
{
	char	*line;
	int	i;
	int    j;
	
	ptr->mapa = (int **)malloc(sizeof(int *) * ptr->y);
	if (ptr->mapa == NULL)
		return ;
	line = get_next_line(fd);
	i = 0;
	j = 0;
	while (line != NULL)
	{
		if (i < ptr->y)
		{
			ptr->mapa[i] = mapa_line(line, ptr->x);
			if (ptr->mapa[i] == NULL)
			{
				free(line);
				while (j < i)
					free(ptr->mapa[j++]);
				free(ptr->mapa);
				return ;
			}
		}
		free (line);
		line = get_next_line(fd);
		i++;
	}
}