#include <stdio.h>

int	ft_printf(char *str, ...);

int	main(void)
{
	//printf("[%-10s]\n", "This is a pretty cool test");
	//ft_printf("[%-10s]\n", "This is a pretty cool test");
	//printf("[%-10.*s]\n", -5, NULL);
	//ft_printf("[%-10.*s]\n", -5, NULL);
	//printf("[%10.7s]\n", NULL);
	//ft_printf("[%10.7s]\n", NULL);
	//printf("[%10.*s]\n", 7, NULL);
	//ft_printf("[%10.*s]\n", 7, NULL);
	//printf("[%10.*s]\n", -3, NULL);
	//ft_printf("[%10.*s]\n", -3, NULL);
	//printf("[%010.*d]\n", -7, 1992);
	//ft_printf("[%010.*d]\n", -7, 1992);
	//printf("[%05d]\n", -1992);
	//ft_printf("[%05d]\n", -1992);
	//ft_printf("[%-010.*ld]\n", 5, 9223372036854775807);
	//printf("[%-010.*d]\n", 5, 9223372036854775807);
	//ft_printf("[%5%]\n");
	printf("[%010.0p]\n", NULL);
	ft_printf("[%010.0p]\n", NULL);
}
