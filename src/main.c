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

int	main(int argc, char const *argv[])
{
	const t_config	args = check_args(argc, (char **)argv);
	t_Core 		*core = NULL;
	char 		**grid = NULL;

	if (_unlikely(args.error))
		return (-1);
	core = Core_init(&args);
	if (_unlikely(!core))
	{
		write(2, "Error: Core_init failed\n", 24);
		return (-1);
	}

	core->get_grid(&grid);
	if (_unlikely(!grid))
	{
		write(2, "Error: get_grid failed\n", 23);
		core->destroy(&core);
		return (-1);
	}
	else
		display_grid((const char *const restrict *)grid, core);

	core->destroy(&core);
	return 0;
}
