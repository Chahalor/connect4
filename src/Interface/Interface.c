#pragma region Header

/* -----| Internals |----- */
//...

/* -----| Modules   |----- */
#include "Interface.h"

#pragma endregion Header
#pragma region Fonctions

extern t_Core	*CORE;
extern t_AI		*AI;

/**
 * @brief	Function to display the end of the game.
 * 
 * @param order	The order of the Core about the endgame.
 * @param grid	The grid to display.
 * 
 * @return int	0 if the function runs successfully.
*/
__attribute__((always_inline, used)) static inline int end_game(
	const int order,
	char **grid
)
{
	display_grid(grid, CORE->height, CORE->width);
	switch (order)
	{
		case core_ord_draw:
			write(1, "Game is a draw\n", 15);
			break;
		case core_ord_win_player:
			write(1, GREEN, 5);
			write(1, "Player wins\n", 12);
			write(1, RESET, 4);
			break;
		case core_ord_win_AI:
			write(1, RED, 5);
			write(1, "AI wins\n", 8);
			write(1, RESET, 4);
			break;
		case core_ord_stop:
			write(1, "Game stopped\n", 13);
			break;
		default:
			break;
	}
	return (0);
}

/**
 * @brief	Let the player play his turn.
 * 
 * @param void
 * 
 * @return int	The order of the Core about the turn.
 * @retval core_ord_player if the player played his turn.
 * @retval core_ord_wrong_place if the player played in a wrong place.
 * @retval core_ord_draw if the game is a draw.
 * @retval core_ord_win_player if the player wins.
 * @retval core_ord_win_AI if the AI wins.
 * @retval core_ord_stop if the game is stopped.
 * 
 * @note The function allocates memory for the line variable.
 *  It is the caller's responsibility to free it.
*/
__attribute__((always_inline, used)) static inline int	player_turn(void)
{
	char	*line = NULL;
	int		col = 0;
	int		order = 0;

	while (1)
	{
		write(1, "\n>> ", 4);
		line = gnl(0);
		if (!line)
			continue ;
		else if (!is_numeric(line))
		{
			ft_fprintf(2, RED ERROR RESET "Invalid input: \"%s\"\n", line);
			free(line);
		}
		else
		{
			col = ft_atoi(line);
			free(line);
			order = CORE->add_pawn(col);
			if (order != core_ord_wrong_place)
				break ;
			else
				ft_fprintf(2, RED ERROR RESET "Invalid column: \"%d\"\n", col);

		}
	}
	return (order);
}

/**
 * @brief	Display the game And run the game loop.
 * 
 * @param Core	The Core of the game.
 * 
 * @return int	0 if the function runs successfully.
 * @retval -1 if the function fails.
*/
__attribute__((used)) int display_game(
	t_Core *const restrict Core
)
{
	char	**grid = NULL;
	int		order = 0;

	if (_unlikely(!Core))
		return (-1);

	Core->get_grid(&grid);
	while (order < core_ord_start)
	{
		order = Core->next_turn();
		switch (order)
		{
			case core_ord_player:
				display_grid(grid, Core->height, Core->width);
				order = player_turn();
				break;
			default:
				continue ;
		}
	}
	return (end_game(order, grid));
}

/**
 * @brief	Display the grid of the game.
 * 
 * @param grid	The grid to display.
 * @param height	The height of the grid.
 * @param width	The width of the grid.
 * 
 * @return int	0 if the function runs successfully.
 * @retval -1 if the function fails.
*/
__attribute__((used)) int	display_grid(
	char **grid,
	const t_uint height,
	const t_uint width
)
{
	register t_uint	i = -1;
	register t_uint	j = -1;
	register t_uint k = 1;
	register t_uint num_digits = 1;
	register t_uint temp_width = width - 1;
	register t_uint digit_pos = num_digits;
	register t_uint divisor = 1;
	char digit = '0';

	if (_unlikely(!grid))
		return (-1);
	else
	{
		while (temp_width >= 10) {
			temp_width /= 10;
			num_digits++;
		}
		write(1, "\n", 1);
		for (digit_pos = num_digits; digit_pos > 0; digit_pos--) {
			write(1, " ", 1);
			for (j = 0; j < width; j++) {
				write(1, GREEN, 5);
				divisor = 1;
				for (k = 1; k < digit_pos; k++)
					divisor *= 10;
				digit = '0' + ((j / divisor) % 10);
				write(1, &digit, 1);
				write(1, RESET, 4);
				write(1, " ", 1);
			}
			write(1, "\n", 1);
		}
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
