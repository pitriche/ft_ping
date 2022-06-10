#include "libft.h"		/* bzero */
#include "ft_ping.h"	/* version, usage */
#include <stdlib.h>		/* exit */

void	ft_ping_parse_flags(int ac, char **av, t_flags *flags)
{
	char	*arg;

	ft_bzero(flags, sizeof(t_flags));
	for (int arg_id = 0; arg_id < ac; ++arg_id)
	{
		arg = av[arg_id];
		if (arg[0] != '-')
			continue ;
		for (int i = 1; arg[i]; ++i)
		{
			switch (arg[i])
			{
				case 'V':
					ft_ping_version();
					exit(1);
				case 'h':
					ft_ping_usage();
					exit(1);
				case 'v':
					flags->verbose = 1;
					break ;
				default:
					ft_ping_invalid(arg[i]);
					exit(1);
			}
		}
	}
}
