#include "Parser.h"

static inline int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static inline int	is_numeric(const char *const restrict str)
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

static inline t_config	print_usage(void)
{
	ft_fprintf(2, BLUE USAGE RESET "./connect4 <columns> <rows> [interface]\n");
	return ((t_config){.error = 1});
}

static inline t_config err_invalide_str(
	const char *const restrict str
)
{
	ft_fprintf(2, RED ERROR RESET "Invalid number\n" PADD "\"%s\"\n", str);
	return ((t_config){.error = 1});
}

static inline t_config err_invalide_size(
	const char *const restrict str,
	const int min
)
{
	ft_fprintf(2, RED ERROR RESET "Invalid size\n" PADD "\"%s\" (min %d)\n", str, min);
	return ((t_config){.error = 1});
}

t_config	check_args(int argc, char **argv)
{
	t_config	config;
	int	cols;
	int	rows;

	if (argc != 3 && argc != 4)
		return (print_error_and_exit());
	else if (!is_numeric(argv[1]))
		return (err_invalide_str(argv[1]));
	else if (!is_numeric(argv[2]))
		return (err_invalide_str(argv[2]));
	else if (argc == 4 && !is_numeric(argv[3]))
		return (err_invalide_str(argv[3]));
	cols = ft_atoi(argv[1]);
	rows = ft_atoi(argv[2]);
	if (cols < 7)
		return (err_invalide_size(argv[1], 7));
	else if (rows < 6)
		return (err_invalide_size(argv[2], 6));
	else if (argc == 4 && (argv[3][0] != '0' && argv[3][0] != '1'))
		return (err_invalide_str(argv[3]));
	config.columns = cols;
	config.rows = rows;
	config.interface_enabled = 0;
	if (argc == 4)
	{
		if (!(argv[3][0] == '0' || argv[3][0] == '1') || argv[3][1] != '\0')
			return (print_error_and_exit());
		config.interface_enabled = (argv[3][0] == '1');
	}
	return (config);
}
