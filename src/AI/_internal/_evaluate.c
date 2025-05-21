// Big Header

#pragma region Header

/* -----| Internals |----- */
# include "_ai.h"

/* -----| Modules   |----- */
#include "Utils.h"

#pragma endregion Header
#pragma region Fonctions

extern t_Core	*CORE;

__attribute__((unused)) static inline t_uint _get_next_row(
	char **grid,
	const int col
)
{
	register t_uint	row = -1;

	while (++row < CORE->height)
		if (grid[row][col] == 0)
			return (row);
	return (-1);
}

/** */
__attribute__((always_inline, used)) inline int	_play(
	_t_ai *_ai
)
{
	return (_ai->best_move);
}

/** */
__attribute__((always_inline, used)) static inline int _playable_column(
	char **grid,
	const int col
)
{
	return (!grid[0][col]);
}

/** */
__attribute__((always_inline, used)) static inline int	count_direction_win(
	char **grid,
	t_point point,
	const int dx,
	const int dy,
	const char pawn
)
{
	register int	count = 0;

	while (
		   point.x >= 0
		&& point.x < CORE->width
		&& point.y >= 0
		&& point.y < CORE->height
		&& grid[point.y][point.x] == pawn)
	{
		++count;
		point.x += dx;
		point.y += dy;
	}
	return (count);
}

/** */
__attribute__((always_inline, used)) static inline int	_is_win(
	const int x,
	const int y,
	char **grid,
	const char pawn
)
{
	static const int	directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};
	register int		i = -1;
	int					dx;
	int					dy;
	int					count;

	while (++i < 4)
	{
		dx = directions[i][0];
		dy = directions[i][1];
		count = 1;
		count += count_direction_win(grid, (t_point){x + dx, y + dy}, dx, dy, pawn);
		count += count_direction_win(grid, (t_point){x - dx, y - dy}, -dx, -dy, pawn);
		if (count > 3)
			return (1);
	}
	return (0);
}

int	score_position(
	char **grid,
	int width,
	int height,
	int x,
	int y,
	char target
)
{
	static const int	dirs[4][2] = {
		{1, 0},  // horizontal →
		{0, 1},  // vertical ↓
		{1, 1},  // diagonale ↘
		{1, -1}  // diagonale ↗
	};
	int	score = 0;

	for (int d = 0; d < 4; ++d)
	{
		int dx = dirs[d][0];
		int dy = dirs[d][1];

		// Parcours dans les deux sens
		for (int dir = -1; dir <= 1; dir += 2)
		{
			int nx = x + dir * dx;
			int ny = y + dir * dy;
			if (nx >= 0 && nx < width && ny >= 0 && ny < height)
			if (grid[ny][nx] == target)
				score = !score ? 1 : score * 2;
		}
	}
	// ft_printf(">> AI score for position (%d, %d) with target %c: %d\n", x, y, target, score);
	return score;
}


int	choose_column(
	_t_ai *_ai,
	char **grid
)
{
	register int	i = -1;
	register int	j = -1;
	int				max = 0;
	int				max_index = 0;
	int offensive_score = 0;
	int defensive_score = 0;

	while (++i < _ai->width)
	{
		j = _get_next_row(grid, i);
		while (++j < _ai->height)
		{
			if (_playable_column(grid, i))
			{
				offensive_score = score_position(grid, _ai->width, _ai->height, i, j, AI_PAWN);				// the offensive score
				defensive_score = score_position(grid, _ai->width, _ai->height, i, j, PLAYER_PAWN) * 0.2f;	// the defensive score
				_ai->grid[j][i] = offensive_score > defensive_score ? offensive_score : defensive_score; //offensive_score + defensive_score;	// maybe replace with the greater score
				if (_ai->grid[j][i] == 100000)
					return (i);
				else if (_is_win(i, j, grid, PLAYER_PAWN))
					return (i);
				else if (_ai->grid[j][i] > max)
				{
					max = _ai->grid[j][i];
					max_index = i;
				}
			}
		}
	}
	max_index = randint(0, _ai->width - 1);
	return (max_index);
}

/** */
__attribute__((always_inline, used)) inline int	_evaluate(
	_t_ai *_ai
)
{
	char			**grid = NULL;

	ft_printf(">> AI is evaluating the grid...\n");
	if (_unlikely(!_ai))
		return (-1);
	else if (!grid)
		CORE->get_grid(&grid);

	_ai->best_move = choose_column(
		_ai,
		grid
	);
	// ft_printf(">> AI chose column %d\n", _ai->best_move);

	return (0);
}

#pragma endregion Fonctions