#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>		/* getaddrinfo */

#include "libft.h"		/* bzero */
#include "ft_ping.h"	/* version, usage */
#include <arpa/inet.h>	/* inet_pton */
#include <stdio.h>		/* printf */
#include <stdlib.h>		/* malloc */

void	ft_ping_DNS_resoltion(char *addr, t_destination *dest)
{
	int				ret;
	struct addrinfo	*res;
	struct addrinfo	hints;

	ft_bzero(&hints, sizeof(struct addrinfo));
	hints.ai_flags = AI_CANONNAME;
	hints.ai_family = AF_INET;	/* not neccesary, but should be here */
	if ((ret = getaddrinfo(addr, 0, &hints, &res)))
		ft_ping_problem(addr, (char *)gai_strerror(ret));
	dest->ptr_record = malloc(10000);
	if ((ret = getnameinfo(res->ai_addr, res->ai_addrlen, dest->ptr_record,
				10000, 0, 0, 0)))
		ft_ping_problem(addr, " getnameinfo failed");
	dest->ip = ((struct sockaddr_in *)res->ai_addr)->sin_addr.s_addr;
	dest->canon_name = ft_strdup(res->ai_canonname);
	freeaddrinfo(res);
}

/* will only interpret the first non-flag argument, and quit if invalid */
void	ft_ping_parse_address(int ac, char **av, t_destination *dest)
{
	char		*arg;
	unsigned	addr;

	ft_bzero(dest, sizeof(t_destination));
	for (int arg_id = 0; arg_id < ac; ++arg_id)
	{
		arg = av[arg_id];
		if (arg[0] == '-')
			continue ;
		if (inet_pton(AF_INET, arg, &addr) == 1)
		{
			dest->is_ip = 1;
			dest->ip = addr;
			return ;
		}
		ft_ping_DNS_resoltion(arg, dest);
		return ;
	}
}

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
				case 'V' : ft_ping_version(); break;
				case 'h' : ft_ping_usage(); break;
				case 'v' : flags->verbose = 1; break;
				default : ft_ping_invalid(arg[i]); break;
			}
		}
	}
}
