#include "fdf.h"
#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void	map_error(t_matriz *ptr, int i, char *line)
{
	int	j;

	j = 0;
	free(line);
	while (j < i)
		free(ptr->mapa[j++]);
	free(ptr->mapa);
	return ;
}

void	populate(t_ponto *linem, char **color_hex, char **num, int x)
{
	int	i;
	int	k;

	i = 0;
	while (num[i] != NULL && i < x)
	{
		k = -1;
		linem[i].altura = ft_atoi(num[i]);
		color_hex = ft_split(num[i], ',');
		if (color_hex != NULL && color_hex[1] != NULL)
			linem[i].cor = convert_base(color_hex[1]);
		else
			linem[i].cor = convert_base("0xAAAAAA");
		free(num[i]);
		while (color_hex[++k] != NULL)
			free(color_hex[k]);
		free (color_hex);
		i++;
	}
	free (num[i]);
	free(num);
}

t_ponto	*mapa_line(char	*line, int x)
{
	char	**num;
	char	**color_hex;
	t_ponto	*linem;
	int		i;

	i = 0;
	color_hex = NULL;
	num = ft_split(line, ' ');
	if (num == NULL)
		return (NULL);
	linem = malloc(sizeof(t_ponto) * x);
	if (linem == NULL)
	{
		free (num);
		return (NULL);
	}
	populate(linem, color_hex, num, x);
	return (linem);
}

void	creat_matriz(t_matriz *ptr, int fd)
{
	char	*line;
	int		i;

	ptr->mapa = (t_ponto **)malloc(sizeof(t_ponto *) * ptr->y);
	if (ptr->mapa == NULL)
		return ;
	line = get_next_line(fd);
	i = 0;
	while (line != NULL)
	{
		if (i < ptr->y)
		{
			ptr->mapa[i] = mapa_line(line, ptr->x);
			if (ptr->mapa[i] == NULL)
				map_error(ptr, i, line);
		}
		free (line);
		line = get_next_line(fd);
		i++;
	}
}
