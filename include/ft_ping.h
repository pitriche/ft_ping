#ifndef FT_PING
# define FT_PING

# define ICMP_PACKET_SIZE	64

typedef unsigned char	t_u8;
typedef unsigned short	t_u16;
typedef unsigned int	t_u32;
typedef unsigned long	t_u64;

/* ########################################################################## */
/* ######################### IPV4 - ICMP STRUCTURES ######################### */
/* ########################################################################## */

/* ipv4 header */
typedef struct	s_ipv4_header
{
	/* 0-4 bytes */
	t_u8	version_ihl;	/* first 4 bit: version	| last 4: IHL (5) */
	t_u8	dscp_ecn;		/* first 6 bit: DSCP	| last 2: ECN */
	t_u16	packet_length;
	/* 4-8 bytes */
	t_u16	identification;
	t_u16	flag_offset;	/* first 3 bit: flags	| last 13: frag offset */
	/* 8-12 bytes */
	t_u8	ttl;
	t_u8	protocol;		/* 1 for ICMP */
	t_u16	header_checksum;
	/* 12-16 bytes */
	t_u32	source_ip;
	/* 16-20 bytes */
	t_u32	dest_ip;
}				t_ipv4_header;

/* icmp header, for echo request and reply */
typedef struct	s_icmp_header
{
	/* 0-4 bytes */
	t_u8	type;		/* 0 for echo reply, 8 for echo request */
	t_u8	code;		/* 0 for echo request and reply */
	t_u16	checksum;	/* from icmp header, with 0 in this field */
	/* 4-8 bytes */
	t_u16	pid;		/* ping pid */
	t_u16	sequence;	/* number of packets sent */
}				t_icmp_header;

/* 64 byte ICMP packet */
typedef struct	s_icmp_packet
{
	t_icmp_header	icmp;
	char			payload[ICMP_PACKET_SIZE - sizeof(t_icmp_header)];
}				t_icmp_packet;

/* 84 byte ipv4 ICMP packet */
typedef struct	s_ipv4_icmp_packet
{
	t_ipv4_header	ipv4;
	t_icmp_header	icmp;
	char			payload[ICMP_PACKET_SIZE - sizeof(t_icmp_header)];
}				t_ipv4_icmp_packet;

/* ########################################################################## */
/* ########################### FT_PING STRUCTURES ########################### */
/* ########################################################################## */

/* to allow easy expansion (will never happen) */
typedef struct	s_flags
{
	unsigned	verbose:1;
}				t_flags;

typedef struct	s_destination
{
	char		*canon_name;	/* canon name of ip, only if is_ip is false */
	char		*ptr_record;	/* rDNS of ip, only if is_ip is false */
	t_u32		ip;				/* system aligned (not swapped) ip address */
	unsigned	is_ip:1;		/* display target as IP */
}				t_destination;

typedef struct	s_stat
{
	t_u64	begin;			/* program start timestamp */
	t_u64	last;			/* last timestamp */
	t_u64	delta;			/* current delta */

	t_u64	min_delta;
	t_u64	max_delta;
	t_u64	sum_delta;

	t_u64	*all_delta;
	t_u32	ad_size;

	t_u16	packet_sent;	/* only 16 bits because of sequence field */
	t_u16	packet_recvd;	/* packet received */
}				t_stat;

typedef struct	s_ping
{
	t_stat			stat;
	t_flags			flags;	/* ft_ping flags */
	t_destination	dest;	/* ft_ping destination info */
	int				sock;	/* socket fd */
}				t_ping;

/* ########################################################################## */
/* ########################### FT_PING FUNCTIONS ############################ */
/* ########################################################################## */

void	ft_ping_noarg(void);
void	ft_ping_version(void);
void	ft_ping_usage(void);
void	ft_ping_invalid(char op);
void	ft_ping_problem(char *input, char *problem);

void	err_quit(char *msg);
void	ft_bitdump(t_u8 *add, unsigned size);
void	ft_hexdump(t_u8 *add, unsigned size);
void	ft_chardump(t_u8 *add, unsigned size);
t_u16	ft_checksum16(t_u16 *addr, unsigned size);
t_u16	ft_swap16(t_u16 num);
t_u32	ft_swap32(t_u32 num);
t_u64	ft_timestamp(void);
float	ft_sqrt(float scalar);

/* debug */
void	ft_ipv4_header_print(t_ipv4_header *head);
void	ft_icmp_header_print(t_icmp_header *head);

void	ft_ipv4_print(t_u32 addr);
void	ft_ping_header_print(t_destination *dest);
void	ft_ping_packet_print(t_ipv4_icmp_packet *pack, t_destination *dest);
void	ft_ping_tailer_print(int sig);

void	ft_ping_parse_flags(int ac, char **av, t_flags *flags);
void	ft_ping_parse_address(int ac, char **av, t_destination *dest);

void	ft_ping(int ac, char **av);

extern t_ping	all;

#endif