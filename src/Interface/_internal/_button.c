#pragma region Header

/* -----| Internals |----- */
#include "_interface.h"

/* -----| Modules   |----- */
#include "Interface.h"
#include "Core.h"

#pragma endregion Header
#pragma region Fonctions

/** */
__attribute__((visibility("hidden"), used)) int	_is_pressed(
	const t_button *const restrict btn,
	const int x,
	const int y
)
{
	if (_unlikely(!btn))
		return (0);
	else
	{
		mvprintw(20, 0, "Click at x=%d y=%d | Button bounds: x[%d,%d] y[%d,%d]", 
			x, y, btn->x1, btn->x2, btn->y1, btn->y2);
		refresh();
		return (
			x >= btn->x1 && x <= btn->x2 &&
			y >= btn->y1 && y <= btn->y2
		);

	}
}

/** */
__attribute__((visibility("hidden"), used)) int	_button_draw(
	const t_button *const restrict btn
)
{
	register int	i = -1;
	register int	j = -1;

	if (_unlikely(!btn))
		return (-1);
	else
	{
		mvprintw(btn->y1, btn->x1, "%s", btn->label);
		while (++i < btn->y2 - btn->y1)
		{
			j = -1;
			while (++j < btn->x2 - btn->x1)
				mvaddch(btn->y1 + i, btn->x1 + j, ' ');
		}
		return (0);
	}
}

/** */
__attribute__((used)) int	_button_destroy(
	t_button **btn
)
{
	if (_unlikely(!btn || !*btn))
		return (-1);
	free(*btn);
	*btn = NULL;
	return (0);
}

__attribute__((used)) t_button *button_create(
	const int x,
	const int y,
	const int width,
	const int height,
	const char *label,
	int (*callback)(void *)
)
{
	t_button *btn;

	if (_unlikely(!label || !callback))
		return (NULL);
	btn = malloc(sizeof(t_button));
	if (_unlikely(!btn))
		return (NULL);
	*btn = (t_button){
		.x1 = x,
		.y1 = y,
		.x2 = x + width - 1,
		.y2 = y + height - 1,
		.label = (char *)label,
		.callback = callback,
		.is_pressed = _is_pressed,
		.draw = _button_draw,
		.destroy = _button_destroy
	};
	return btn;
}


#pragma endregion Fonctions