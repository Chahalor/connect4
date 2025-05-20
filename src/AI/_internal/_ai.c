// Big Header

#pragma region Header

/* -----| Internals |----- */
# include "_ai.h"

/* -----| Modules   |----- */
	//...

#pragma endregion Header
#pragma region Fonctions

/** */
__attribute__((always_inline, used)) static inline _t_ai	*_init(
	const t_uint width,
	const t_uint height
)
{
	_t_ai			*ai = NULL;
	register int	i = -1;
	register int	j = -1;

	if (_unlikely(!width || !height))
		return (NULL);
	else
	{
		ai = (_t_ai *)malloc(
			  sizeof(_t_ai)
			+ (sizeof(int *) * height
			+ (sizeof(int) * width * height))
		);
		if (_unlikely(!ai))
			return (NULL);
		else
		{
			while (++i < height)
			{
				ai->grid[i] = (int *)(ai + 1) + (width * i);
				j = -1;
				while (++j < width)
					ai->grid[i][j] = 0;
			}
			ai->width = width;
			ai->height = height;
		}
		return (ai);
	}
}

/** */
__attribute__((always_inline, used)) static inline int _destroy(
	_t_ai **ai
)
{
	if (_unlikely(!ai || !*ai))
		return (-1);
	else
	{
		free(*ai);
		*ai = NULL;
		return (0);
	}
}

/** */
__attribute__((visibility("hidden"), used)) int	_AI(
	int access,
	void *data
)
{
	static _t_ai	*_ai = NULL;

	switch (access)
	{
		case ai_req_evaluate:
			return (_evaluate(_ai));
		case ai_req_play:
			return (_Play(_ai));
		case ai_req_destroy:
			return (_destroy(&_ai));
		case ai_req_init:
			const t_point	*point = (t_point *)data;
			_ai = _init(point->x, point->y);
			return (_ai ? 0 : -1);
		default:
			return (-1);
	}
}

#pragma endregion Fonctions