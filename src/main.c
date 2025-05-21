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

	if (_unlikely(args.error))
		return (1);
	else if (_unlikely(!Core_init(&args) || !AI_create(args.columns, args.rows)))
	{
		write(2, "Error: Init failed\n", 24);
		return (2);
	}

	display_game(CORE);

	CORE->destroy();
	return 0;
}
