
#ifndef PARSEUR_H
# define PARSEUR_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_config
{
	int	columns;
	int	rows;
	unsigned int	interface_enabled   : 1;
}	t_config;

int		ft_isdigit(int c);
int		ft_atoi(char *str);
int		is_numeric(char *str);
void	print_error_and_exit(void);
t_config	check_args(int argc, char **argv);

#endif