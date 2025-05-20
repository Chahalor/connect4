// Big Header

#pragma region Header

/* -----| Systems   |----- */
	//...

/* -----| Internals |----- */
# include "Core.h"
# include "_core.h"

/* -----| Modules   |----- */
	//...

#pragma endregion Header
#pragma region Fonctions

/** */
__attribute__((always_inline, used)) static inline _t_Core	*_Init(
	const t_uint width,
	const t_uint height,
	const t_uint display
)
{
	_t_Core			*Core = NULL;
	register t_uint	i =-1;
	register t_uint	j = -1;


	Core = (_t_Core *)malloc(
		  sizeof(_t_Core)
		+ sizeof(char **) * height
		+ sizeof(char) * width * height
	);
	if (_unlikely(!Core))
		return (NULL);
	Core->grid = (char **)(Core + 1);
	while (++i < height)
	{
		Core->grid[i] = (char *)(Core->grid + height) + i * width;
		while (++j < width)
			Core->grid[i][j] = 0;
		j = -1;
	}
	Core->width = width;
	Core->height = height;
	Core->nb_case_left = width * height;
	Core->display = display;
	Core->turn = 0;
	return (Core);
}

/** */
__attribute__((always_inline, used)) static inline int	_Destroy(
	_t_Core *Core
)
{
	if (_unlikely(!Core))
		return (-1);
	free(Core);
	return (0);
}

/** */
__attribute__((always_inline, used)) static inline int	count_in_direction(
	const _t_Core *const restrict _Core,
	t_point point,
	const int dx,
	const int dy,
	const char pawn
)
{
	register int	count = 0;

	while (
		   point.x >= 0
		&& point.x < _Core->width
		&& point.y >= 0
		&& point.y < _Core->height
		&& _Core->grid[point.y][point.x] == pawn)
	{
		++count;
		point.x += dx;
		point.y += dy;
	}
	return (count);
}

/** */
__attribute__((always_inline, used)) static inline int	is_winning_move(
	const int x,
	const int y,
	const _t_Core *_Core
)
{
	static const int	directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};
	const char			pawn = _Core->grid[y][x];
	register int		i = -1;

	while (++i < 4)
	{
		int	dx = directions[i][0];
		int	dy = directions[i][1];
		int	count = 1;
		count += count_in_direction(_Core, (t_point){x + dx, y + dy}, dx, dy, pawn);
		count += count_in_direction(_Core, (t_point){x - dx, y - dy}, -dx, -dy, pawn);
		if (count > 3)
			return (1);
	}
	return (0);
}


/** */
__attribute__((always_inline, used)) static inline int	_core_add_pown(
	_t_Core *const restrict Core,
	register const t_uint col
)
{
	register t_uint	x = 0;

	if (_unlikely(!Core))
		return (core_ord_stop);
	if (_unlikely(col >= Core->width))
		return (core_ord_wrong_place);
	else if (_unlikely(Core->nb_case_left == 0))
		return (core_ord_draw);
	else
	{
		while (x < Core->height && !Core->grid[x][col])
			++x;
		if (x == Core->height)
			return (-2);
		Core->grid[x][col] = Core->turn ? AI_PAWN : PLAYER_PAWN;
		if (is_winning_move(col, x, Core))
			return (Core->turn ? core_ord_win_AI : core_ord_win_player);
		Core->turn = !Core->turn;
		--Core->nb_case_left;
		return (1);
	}
}

/** */
__attribute__((hot, visibility("hidden"))) int	_Core(
	const int access,
	void *data,
	void *response
)
{
	static _t_Core	*Core = NULL;

	switch (access)
	{
		case core_req_add_pown:
			return (_core_add_pown(Core, *(t_uint *)data));
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