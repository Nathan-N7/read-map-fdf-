#include "fdf.h"
#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void	print(t_matriz *ptr)
{
	int    i;
	int    k;

	i = 0;
	k = 0;
	while (i < ptr->y)
	{
		while (k < ptr->x)
		{
			printf("%d ", ptr->mapa[i][k]);
			k++;
		}
		printf("\n");
		k = 0;
		i++;
	}
}
int	main()
{
	int	fd;
	char	*line;
	t_matriz	*ptr;

    fd = open("test_maps/julia.fdf", O_RDONLY);
	if (fd < 0)
	    return (-1);
	ptr  = malloc(sizeof(t_matriz));
	if (ptr == NULL)
		return (-1);
	line = get_next_line(fd);
	ptr->x = count_x(line);
	ptr->y = count_y(fd);
	close(fd);
	fd = open("test_maps/julia.fdf", O_RDONLY);
	if (fd < 0)
	{
		free(ptr);
	    return (-1);
	}
	creat_matriz(ptr, fd);
	print(ptr);
	free_matriz(ptr);
	free(line);
	close(fd);
}