// Big Header

#pragma region Header

/* -----| Internals |----- */
# include "_ai.h"

/* -----| Modules   |----- */
#include "Utils.h"

#pragma endregion Header
#pragma region Fonctions

extern t_Core	*CORE;

/**
 * @brief	Get the next available row of the grid.
 * 
 * @param grid	The game grid.
 * @param col	The column to check.
 * 
 * @return t_uint	The next available row, or -1 if none found.
 */
__attribute__((hot)) static inline t_uint _get_next_row(
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

/**
 * @brief	Send to the AI the best move.
 * 
 * @param _ai	The AI internal struct.
 * 
 * @return The best move column.
 * 
 * @note we never say the best move is the best for the AI
*/
__attribute__((always_inline, used)) inline int	_play(
	_t_ai *_ai
)
{
	return (_ai->best_move);
}

/**
 * @brief	Check if the column is playable.
 * 
 * @param grid	The game grid.
 * @param col	The column to check.
 * 
 * @return int	1 if the column is playable, 0 otherwise.
*/
__attribute__((always_inline, used)) static inline int _playable_column(
	char **grid,
	const int col
)
{
	return (!grid[0][col]);
}

/**
 * @brief	Count the number of pawns in a direction.
 * 
 * @param grid	The game grid.
 * @param point	The starting point.
 * @param dx	The direction vector in the x-axis.
 * @param dy	The direction vector in the y-axis.
 * @param pawn	The pawn type to count.
 * 
 * @return int	The number of pawns found.
*/
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
		   point.x > 1
		&& point.x < CORE->width
		&& point.y > 1
		&& point.y < CORE->height
		&& grid[point.y][point.x] == pawn)
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
 * 
 * @return int	1 if the game is won, 0 otherwise.
*/
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

/**
 * @brief	Score the position for a given coordinate.
 * 
 * @param grid	The game grid.
 * @param width	The width of the grid.
 * @param height	The height of the grid.
 * @param x	The x coordinate of the pawn.
 * @param y	The y coordinate of the pawn.
 * @param target	The pawn type to score.
 * 
 * @return int	The score for the position.
 * 
 * @note The score is calculated based on the number of pawns in the
 *  *  horizontal, vertical and diagonal directions.
 */
__attribute__((always_inline, used)) static inline int	score_position(
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
	int					score = 0;
	int					d = 0;
	int					dx = 0;
	int					dy = 0;
	int					dir = 0;

	while (d < 4)
	{
		dx = dirs[d][0];
		dy = dirs[d][1];
		dir = -1;

		while (dir <= 1)
		{
			if (dir != 0)
			{
				int nx = x + dir * dx;
				int ny = y + dir * dy;
				if (nx >= 0 && nx < width && ny >= 0 && ny < height)
				if (grid[ny][nx] == target)
					score = !score ? 1 : score * 2;
			}
			dir += 2;
		}
		++d;
	}
	return score;
}

/**
 * @brief	Choose the best column to play.
 * 
 * @param _ai	The AI internal struct.
 * @param grid	The game grid.
 * 
 * @return int	The best column to play.
 * 
 * @note The function iterates through each column and row of the grid,
 * *  checking if the column is playable. If it is, it calculates the
 * *  offensive and defensive scores for that position. The column with
 * *  the highest score is chosen.
 * @note If no column is found, a random column is chosen.
 */
__attribute__((always_inline, used)) static inline int	choose_column(
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

	if (!max)
		max_index = randint(0, _ai->width - 1);
	return (max_index);
}

/**
 *  @brief	Evaluate the grid and choose the best move.
 * 
 * @param _ai	The AI internal struct.
 * 
 * @return int	0 if the function runs successfully.
 * @retval -1 if the function fails.
*/
__attribute__((always_inline, used)) inline int	_evaluate(
	_t_ai *_ai
)
{
	static char	**grid = NULL;

	ft_printf(">> AI is evaluating the grid...\n");

	if (_unlikely(!_ai))
		return (-1);
	else if (!grid)
		CORE->get_grid(&grid);
	_ai->best_move = choose_column(_ai, grid);
	return (0);
}

#pragma endregion Fonctions