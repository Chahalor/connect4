#pragma region Header

/* -----| Internals |----- */
#include "_interface.h"
# include <fcntl.h>
# include <stdlib.h>

/* -----| Modules   |----- */
#include "Interface.h"
#include "Core.h"

#pragma endregion Header
#pragma region Fonctions

/** */
__attribute__((always_inline, used)) inline WINDOW	*init_interface(void)
{
	WINDOW	*win = initscr();

	if (_unlikely(!win))
	{
		write(2, "Error: Failed to initialize ncurses\n", 36);
		return (0);
	}
	else
	{
		cbreak();
		noecho();
		keypad(win, TRUE);
		mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
		if (_likely(has_colors()))
			start_color();
		return (win);
	}
}

/** */
__attribute__((cold, used)) int	interface_main_menu(
	t_Core *const restrict Core
)
{
	if (_unlikely(!Core))
		return (-1);
	_t_button	*btn_new_game = button_create(10, 5, 30, 7, "New Game", interface_game);
	_t_button	*btn_exit = button_create(20, 10, 10, 10, "Exit", interface_endgame);
	int			ch = 0;
	MEVENT		event;

	if (_unlikely(!btn_new_game || !btn_exit))
	{
		write(2, "Error: button_create failed\n", 28);
		return (-1);
	}
	erase();
	box(stdscr, 0, 0);
	printw("Main Menu\n");
	btn_new_game->draw(btn_new_game);
	btn_exit->draw(btn_exit);
	while (1)
	{
		refresh();
		ch = getch();
		if (ch == 'q' || ch == 'Q' || ch == 'e' || ch == 'E' || ch == 27)
			break ;
		else if (ch == KEY_MOUSE)
		{
			if (getmouse(&event) == OK)
			{
				if (btn_new_game->is_pressed(btn_new_game, event.x, event.y))
				{
					btn_new_game->callback((void *)Core);
					clear();
					printw("Main Menu\n");
					btn_new_game->draw(btn_new_game);
					btn_exit->draw(btn_exit);
				}
				else if (btn_exit->is_pressed(btn_exit, event.x, event.y))
					break ;
			}
		}
	}
	btn_new_game->destroy(&btn_new_game);
	btn_exit->destroy(&btn_exit);
	return (0);
}

/** */
__attribute__((cold, used)) int	interface_game(
	void *data
)
{
	const t_Core	*const restrict Core = (t_Core *)data;
	char			**grid = NULL;
	register t_uint	i = -1;
	register t_uint	j = -1;
	int				ch = 0;


	if (_unlikely(!Core))
		return (-1);
	Core->get_grid(&grid);
	if (_unlikely(!grid))
		return (-2);

	while (1)
	{
		erase();
		wprintw(stdscr, HEADER);
		box(stdscr, 0, 0);
		printw("Game in progress\n");

		i = -1;
		while (++i < Core->height)
		{
			j = -1;
			while (++j < Core->width)
				mvprintw(BOARD_PADD + i + 1, 2 + j * 3, "|%c", grid[i][j] ? grid[i][j] : ' ');
		}
		refresh();
		ch = getch();
		if (ch == 'q' || ch == 'Q')
			break ;
		else if (ch == KEY_MOUSE)
		{
			MEVENT	event;
			if (_likely(getmouse(&event) == OK))
			{
				mvprintw(0, 0, "Mouse event: (%d, %d)  ", event.x, event.y);
				if (event.bstate & BUTTON1_PRESSED)
					Core->add_pawn(event.y / 3);
			}
		}
	}

	return (0);
}

__attribute__((cold, used)) int	interface_endgame(
	void *data
)
{
	const t_Core	*const restrict Core = (t_Core *)data;

	if (_unlikely(!Core))
		return (-1);
	clear();
	// box(stdscr, 0, 0);
	printw("End Game\n");
	refresh();
	while (1)
	{
		int ch = getch();
		if (ch == 'q' || ch == 'Q')
			break ;
	}
	return (0);
}

#pragma endregion Fonctions