#include "Parseur.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(char *str)
{
	int i = 0;
	int res = 0;

	while (str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

int	is_numeric(char *str)
{
	int i = 0;

	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	print_error_and_exit(void)
{
	write(1, "Invalid input : <number_of_collones> <number_of_lines> [interface]\n", 68);
	exit(1);
}

void	check_args(int argc, char **argv)
{
	if (argc != 3 && argc != 4)
		print_error_and_exit();
	if (!is_numeric(argv[1]) || !is_numeric(argv[2]))
		print_error_and_exit();
	int cols = ft_atoi(argv[1]);
	int rows = ft_atoi(argv[2]);
	if (cols < 4 || rows < 4)
		print_error_and_exit();
	if (argc == 4)
	{
		if (!(argv[3][0] == '0' || argv[3][0] == '1') || argv[3][1] != '\0')
			print_error_and_exit();
	}
}
