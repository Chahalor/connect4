// Big Header

#pragma region Header

/* -----| Systems   |----- */
#include <stdio.h>

/* -----| Modules   |----- */
#include "Core.h"
#include "Parser.h"
#include "AI.h"
#include "Interface.h"

#pragma endregion Header
#pragma region Fonctions

extern t_Core	*CORE;

int	main(int argc, char const *argv[])
{
	const t_config	args = check_args(argc, (char **)argv);
	WINDOW			*win = NULL;

	if (_unlikely(args.error))
		return (1);
	;
	if (_unlikely(!Core_init(&args) || !AI_create(args.columns, args.rows)))
	{
		write(2, "Error: Init failed\n", 24);
		return (2);
	}
	else if (args.interface_enabled)
	{
		win = init_interface();
		if (_unlikely(!win))
		{
			CORE->destroy();
			endwin();
			return (3);
		}
	}

	display_game(CORE);

	CORE->destroy();
	endwin();
	delwin(win);
	return 0;
}
