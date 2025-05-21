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

__attribute__((always_inline, used)) inline int	ft_atoi(
	const char *const restrict str
)
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

static inline int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}

inline int	is_numeric(
	const char *const restrict str
)
{
	register int	i = 0;

	if (__glibc_unlikely(!str[i]))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

__attribute__((always_inline, used))
//	(-hidden-)
extern inline void	_neutral(\
	void *restrict const area,
	const unsigned int size
)	// v.1. >>> tag: def->neutral
{
	volatile unsigned long long		*restrict	area_64b;
	volatile unsigned char	*restrict			area_8b;
	const unsigned int							len_64b = (size >> 3);
	register unsigned int						i;

	area_64b = (volatile unsigned long long *)area;
	i = 0;
	while (i++ != len_64b)
		*(area_64b++) = 0;
	i <<= 3;
	area_8b = (volatile unsigned char *)area + i;
	while (!((size - i++) >> 31))
		*(area_8b++) = 0;
}

#pragma endregion Fonctions