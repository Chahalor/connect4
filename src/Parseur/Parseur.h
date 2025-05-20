#ifndef PARSEUR_H
# define PARSEUR_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_args
{
    int	cols;
    int	rows;
    int	display;
}	t_args;

int		ft_isdigit(int c);
int		ft_atoi(char *str);
int		is_numeric(char *str);
void	print_error_and_exit(void);
void	check_args(int argc, char **argv);

#endif