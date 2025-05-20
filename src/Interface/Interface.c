#pragma region Header

/* -----| Internals |----- */
#include "_interface.h"

/* -----| Modules   |----- */
#include "Interface.h"
#include "Core.h"

#pragma endregion Header
#pragma region Fonctions

/** */
__attribute__((used)) int	display_grid(
	const char *const restrict *const restrict grid,
	t_Core *const restrict Core
)
{
	register t_uint	i = -1;
	register t_uint	j = -1;

	if (_unlikely(!grid || !Core))
		return (-1);
	else
	{
		while (++i < Core->height)
		{
			write(1, "|", 1);
			j = -1;
			while (++j < Core->width)
			{
				if (!grid[i][j])
					write(1, " ", 1);
				else
					write(1, &grid[i][j], 1);
				write(1, "|", 1);
			}
			write(1, "\n", 1);
		}
		return (0);
	}
}

#pragma endregion Fonctions