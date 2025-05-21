// Big Header

#pragma region Header

/* -----| Systems   |----- */
# include <limits.h>

/* -----| Internals |----- */
#include "Utils.h"

/* -----| Modules   |----- */
	//...

#pragma endregion Header
#pragma region Fonctions

/** */
__attribute__((always_inline, used)) inline int	randint(
	const int min,
	const int max
)
{
	return (rand() % (max - min + 1) + min);
}

__attribute__((always_inline, used)) inline int	ft_atoi(char *str)
{
	register int i = 0;
	register int res = 0;

	while (str[i] && '0' <= str[i] && str[i] <= '9')
	{
		if (res > (INT_MAX - (str[i] - '0')) / 10)
			return (-1);
		res = res * 10 + (str[i] - '0');
		++i;
	}
	return (res);
}

#pragma endregion Fonctions