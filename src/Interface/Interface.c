#pragma region Header

/* -----| Internals |----- */
#include "_interface.h"

/* -----| Modules   |----- */
#include "Interface.h"
#include "Core.h"
#include "get_next_line.h"
#include "Utils.h"
#include "formating.h"

# include <stdio.h>

#pragma endregion Header
#pragma region Fonctions

extern t_Core	*CORE;

/** */
__attribute__((used)) int display_game(
	t_Core *const restrict Core
)
{
	char	**grid = NULL;
	int		core_order = 0;
	char	*line = NULL;

	if (_unlikely(!Core))
		return (-1);

	while (
		(core_order != core_ord_draw) &&
		(core_order != core_ord_win_player) &&
		(core_order != core_ord_win_AI) &&
		(core_order != core_ord_stop))
	{
		write(1, "Game in progress\n", 17);
		Core->get_grid(&grid);
		display_grid(grid, Core->height, Core->width);
		write(1, "\n>> ", 4);
		line = get_next_line(0);
		if (_unlikely(!line))
			return (-1);
		else
		{
			const int col = ft_atoi(line);
			core_order = Core->add_pawn(col);
		}
		free(line);
		CORE->next_turn();
	}
	return (0);
}

/** */
__attribute__((used)) int	display_grid(
	char **grid,
	const t_uint height,
	const t_uint width
)
{
	register t_uint	i = -1;
	register t_uint	j = -1;

	if (_unlikely(!grid))
		return (-1);
	else
	{
		while (++i < height)
		{
			write(1, "|", 1);
			j = -1;
			while (++j < width)
			{
				if (!grid[i][j])
					write(1, " ", 1);
				else
				{
					write(1, grid[i][j] == PLAYER_PAWN ? YELLOW : RED, 5);
					write(1, &grid[i][j], 1);
					write(1, RESET, 4);
				}
				write(1, "|", 1);
			}
			write(1, "\n", 1);
		}
		return (0);
	}
}

#pragma endregion Fonctions