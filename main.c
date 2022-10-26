#include <unistd.h>		/* getuid */
#include "ft_ping.h"	/* ft_ping */

int	main(int ac, char **av)
{
	if (getuid() != 0)
		err_quit("ft_ping neccesitate root privileges to run ! Use:\nsudo ./ft_"
			"ping <args>");
	if (ac <= 1)
		ft_ping_noarg();
	else
		ft_ping(ac - 1, av + 1);
	return (0);
}