#include <stdio.h>
#include <mlx.h>

int main(void)
{
	printf("test\n");
	void *mlx = mlx_init();
	void *mlx_win = mlx_new_window(mlx, 50, 50, "test");
	mlx_loop(mlx);
	return (0);
}