// Big Header

#pragma region Header

/* -----| Systems   |----- */
#include <stdio.h>
#include <time.h>

/* -----| Internals |----- */
# include "Core.h"
# include "_core.h"

/* -----| Modules   |----- */
#include "AI.h"

#pragma endregion Header
#pragma region Globals

extern t_Core	*CORE;
extern t_AI		*AI;

#pragma endregion Globals
#pragma region Fonctions

/**
 * @brief	Initialize the Core.
 * 
 * @param width		The width of the grid.
 * @param height	The height of the grid.
 * @param display	The display mode.
 * 
 * @return _t_Core*	The Core pointer.
 * @retval NULL if the function fails.
 * 
 * @note It also initializes the random number generator.
*/
__attribute__((always_inline, used)) static inline _t_Core	*_Init(
	const t_uint width,
	const t_uint height,
	const t_uint display
)
{
	_t_Core			*_core = NULL;
	register t_uint	i =-1;
	register t_uint	j = -1;

	srand(time(NULL));

	_core = (_t_Core *)malloc(
		  sizeof(_t_Core)
		+ sizeof(char **) * (height + 1)
		+ sizeof(char) * (width * height + 1)
	);
	if (_unlikely(!_core))
		return (NULL);
	_core->grid = (char **)(_core + 1);
	while (++i < height)
	{
		_core->grid[i] = (char *)(_core->grid + height) + i * width;
		while (++j < width)
			_core->grid[i][j] = 0;
		j = -1;
	}
	_core->width = width;
	_core->height = height;
	_core->nb_case_left = width * height;
	_core->display = display;
	_core->turn = (rand() & 1);
	return (_core);
}

/**
 * @brief	Destroy the Core by freeing the memory allocated for it.
 * 
 * @param Core	The Core pointer.
 * 
 * @return int	0 if the function runs successfully.
 * @retval -1 if the function fails.
*/
__attribute__((always_inline, used)) static inline int	_Destroy(
	_t_Core *Core
)
{
	if (_unlikely(!Core))
		return (-1);
	free(Core);
	return (0);
}

/**
 * @brief	Count the number of pawns in a direction.
 *
 * @param _Core	The Core pointer.
 * @param point	The point to start counting from.
 * @param dx	The x direction.
 * @param dy	The y direction.
 * @param pawn	The pawn to count.
 * 
 * @return int	The number of pawns in the direction.
*/
__attribute__((always_inline, used)) static inline int	count_direction(
	const _t_Core *const restrict _Core,
	t_point point,
	const int dx,
	const int dy,
	const char pawn
)
{
	register int	count = 0;

	while (
		   point.x > 1
		&& point.x < _Core->width
		&& point.y >= 1
		&& point.y < _Core->height
		&& _Core->grid[point.y][point.x] == pawn)
	{
		++count;
		point.x += dx;
		point.y += dy;
	}
	return (count);
}

/**
 * @brief	Check if the game is won.
 * 
 * @param x	The x coordinate of the pawn.
 * @param y	The y coordinate of the pawn.
 * @param _Core	The Core pointer.
 * 
 * @return int	1 if the game is won, 0 otherwise.
*/
__attribute__((always_inline, used)) static inline int	_is_win(
	const int x,
	const int y,
	const _t_Core *_Core
)
{
	static const int	directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};
	const char			pawn = _Core->grid[y][x];
	register int		i = -1;
	int					dx;
	int					dy;
	int					count;

	while (++i < 4)
	{
		dx = directions[i][0];
		dy = directions[i][1];
		count = 1;
		count += count_direction(_Core, (t_point){x + dx, y + dy}, dx, dy, pawn);
		count += count_direction(_Core, (t_point){x - dx, y - dy}, -dx, -dy, pawn);
		if (count > 3)
			return (1);
	}
	return (0);
}

/**
 * @brief	Add a pawn to the grid.
 * 
 * @param Core	The Core pointer.
 * @param col	The column to add the pawn to.
 * 
 * @return int	The order of the game.
 * @retval core_ord_stop if the game should stop.
 * @retval core_ord_wrong_place if the column is invalid.
 * @retval core_ord_draw if the game is a draw.
 * @retval core_ord_win_AI if the AI won the game.
 * @retval core_ord_win_player if the player won the game.
 * @retval core_ord_display if the game should be displayed.
*/
__attribute__((always_inline, used)) static inline int	_core_add_pown(
	_t_Core *const restrict Core,
	register const t_uint col
)
{
	register t_uint	x = Core->height - 1;

	if (_unlikely(!Core))
		return (core_ord_stop);
	else if (col >= Core->width)
		return (core_ord_wrong_place);
	else if (_unlikely(Core->nb_case_left == 0))
		return (core_ord_draw);
	else
	{
		while (x > 0 && Core->grid[x][col])
			--x;
		if (_unlikely(x == 0 && Core->grid[x][col]))
			return (core_ord_wrong_place);
		else if (!Core->turn)
			AI->last_move = (t_point){.x = x, .y = col};
		Core->grid[x][col] = Core->turn ? AI_PAWN : PLAYER_PAWN;
		if (_unlikely(_is_win(col, x, Core)))
			return (Core->turn ? core_ord_win_AI : core_ord_win_player);
		Core->turn = !Core->turn;
		--Core->nb_case_left;
		return (core_ord_display);
	}
}

/**
 * @brief	Core function dispatcher.
 * 
 * @param access	The access level.
 * @param data	The data to pass to the Core.
 * @param response	The response from the Core.
 * 
 * @return int	0 if the function runs successfully.
 * @retval -1 if the function fails.
 */
__attribute__((hot, visibility("hidden"))) int	_Core(
	const int access,
	void *data,
	void *response
)
{
	static _t_Core	*Core = NULL;

	switch (access)
	{
		case core_req_add_pawn:
			return (_core_add_pown(Core, *(t_uint *)data));
		case core_req_next_turn:
		{
			if (_unlikely(!Core))
				return (-1);
			else
				return (Core->turn ? AI->play() : core_ord_player);
		}
		case core_req_get_grid:
			if (_unlikely(!response))
				return (-1);
			*(char ***)response = Core->grid;
			return (-!(Core->grid != NULL));
		case core_req_init:
		{
			const t_args	*args = (t_args *)data;
			Core = _Init(args->columns, args->rows, args->interface_enabled);
			return (-!(Core != NULL));
		}
		case core_req_destroy:
			return (_Destroy(Core));
		default:
			return (-1);
	}
}

#pragma endregion Fonctions