#include <stdio.h>
#include <stdlib.h>
#include "minilibx-linux/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>

typedef struct s_window
{
	void *ptr;
	void *win;
}	t_window;

int button_press(int keysym, t_window *mlx)
{
	if(keysym == XK_Escape)
	{
		mlx_destroy_window(mlx->ptr, mlx->win);
		mlx_destroy_display(mlx->ptr);
		free(mlx->ptr);
		exit(0);
	}
	return (0);
}

int event_close(t_window *mlx)
{
	mlx_destroy_window(mlx->ptr, mlx->win);
	mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
	exit(0);
}

int main()
{
	t_window mlx;

	mlx.ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.ptr,900,600, "My window");

	mlx_key_hook(mlx.win, button_press, &mlx);
	mlx_hook(mlx.win, 17, 0, event_close, &mlx);
	mlx_loop(mlx.ptr);
}
