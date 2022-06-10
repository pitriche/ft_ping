#include "libft.h"

void	ft_ping_noarg(void)			/* on stderr */
{
	ft_putstr_fd("ping: usage error: Destination address required\n", 2);
}

void	ft_ping_version(void)		/* on stdout !! */
{
	ft_putstr("ft_ping from pitriche s20220906\n");
}

void	ft_ping_usage(void)			/* on stderr */
{
	ft_putstr_fd("\nUsage\n  ./ft_ping [options] <destination>\n\n"
		"Options\n"
		"  <destination>      dns name or ip address\n"
		"  -h                 print help and exit\n"
		"  -v                 verbose output\n"
		"  -V                 print version and exit\n", 2);
}

void	ft_ping_invalid(char op)	/* on stderr */
{
	ft_putstr_fd("ft_ping: invalid option -- '", 2);
	ft_putchar_fd(op, 2);
	ft_putstr_fd("'\n", 2);
	ft_ping_usage();
}
