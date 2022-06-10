#ifndef FT_PING
# define FT_PING

/* to allow easy expansion (will never happen) */
typedef struct	s_flags
{
	unsigned	verbose:1;
}				t_flags;

typedef struct	s_ipv4_header
{
	/* 0-4 bytes */
	unsigned char	version_ihl;	/* first 4 bit: version	| last 4: IHL (5) */
	unsigned char	dscp_ecn;		/* first 6 bit: DSCP	| last 4: ECN */
	unsigned short	packet_length;
	/* 4-8 bytes */
	unsigned short	identification;
	unsigned short	flag_offset;	/* first 3 bit: flags	| last 13: frag offset */
	/* 8-12 bytes */
	unsigned char	ttl;
	unsigned char	protocol;		/* 1 for ICMP */
	unsigned short	header_checksum;
	/* 12-16 bytes */
	unsigned int	source_ip;
	/* 16-20 bytes */
	unsigned int	dest_ip;
}				t_ipv4_header;

typedef struct	s_icmp_header
{
	/* 0-4 bytes */
	unsigned char	type;		/* 0 for echo reply, 8 for echo request */
	unsigned char	code;		/* 0 for echo request and reply */
	unsigned short	checksum;	/* from icmp header, with 0 in this field */
	/* 4-8 bytes */
	unsigned int	unused;
}				t_icmp_header;

typedef struct	s_icmp_packet
{
	t_ipv4_header	ipv4;
	t_icmp_header	icmp;
	char			payload[32];
}				t_icmp_packet;


/* ########################################################################## */

typedef struct	s_ping
{
	t_flags	flags;	/* ping flags */
	int		sock;	/* socket fd */
}				t_ping;

extern t_ping	all;

/* ########################################################################## */

void	ft_ping_noarg(void);
void	ft_ping_version(void);
void	ft_ping_usage(void);
void	ft_ping_invalid(char op);

void	err_quit(char *msg);
void	ft_bitdump(unsigned char *add, unsigned size);
void	ft_hexdump(unsigned char *add, unsigned size);
void	ft_chardump(unsigned char *add, unsigned size);


void	ft_ping_parse_flags(int ac, char **av, t_flags *flags);

void	ft_ping(int ac, char **av);

#endif